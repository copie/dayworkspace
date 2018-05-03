# Python 内核源码阅读(四)

## PyLongObject

我们知道在 Python3 中 取消了 PyIntObject 用 PyLongObject 取代,我们通过一张图来看一下 PyLongObject 的结构.

![PyLongObject](https://copie.cn/usr/uploads/2018/05/120725787.png)

在[以前的文章](https://copie.cn/index.php/archives/Python-%E5%86%85%E6%A0%B8%E6%BA%90%E7%A0%81%E9%98%85%E8%AF%BB-%E4%BA%8C----%E5%AF%B9%E8%B1%A1%E7%9A%84%E6%9C%BA%E5%88%B6%E7%9A%84%E5%9F%BA%E7%9F%B3-PyObject.html)最后我也贴过 PyLongObject 的代码这里就要正式的分析一下这个代码.
```C

[longobject.h]
/* Long (arbitrary precision) integer object interface */

typedef struct _longobject PyLongObject; /* Revealed in longintrepr.h */   


[longintrepr.h]

/* Long integer representation.
   The absolute value of a number is equal to
        SUM(for i=0 through abs(ob_size)-1) ob_digit[i] * 2**(SHIFT*i)
   Negative numbers are represented with ob_size < 0;
   zero is represented by ob_size == 0.
   In a normalized number, ob_digit[abs(ob_size)-1] (the most significant
   digit) is never zero.  Also, in all cases, for all valid i,
        0 <= ob_digit[i] <= MASK.
   The allocation function takes care of allocating extra memory
   so that ob_digit[0] ... ob_digit[abs(ob_size)-1] are actually available.

   CAUTION:  Generic code manipulating subtypes of PyVarObject has to
   aware that ints abuse  ob_size's sign bit.
*/

struct _longobject {
    PyObject_VAR_HEAD
    digit ob_digit[1];
};
```

先看 _longobject 的注释:

1. 整型绝对值的算法: SUM(for i=0 through abs(ob_size)-1) ob_digit[i] * 2**(SHIFT*i)
2. ob_size 的符号表示整数的符号
3. 0 由 ob_size == 0 表示
4. 标准的(正常的)整数 ob_digit[abs(ob_size)-1] 不为 0;
5. 对于有效的 i, ob_digit[i] 的范围在[0,MASK].

可以看到整型是借助柔性数组实现的, 柔性数组较指针来说,分配内存和释放内存更为方便,且数组本身不占用空间(指针要占用1个int型的空间),柔性数组我会在下面写到.

对于可变对象 ob_size 是 "指明所容纳元素的个数".

> 比如对于 Python 中最常用的 list ,他就是一个 PyVarObject 对象,如果某一个时刻,这个 list 中有 5 个元素, 那么 ob_size 的值就是 5.

但 Python 中整型是不可变对象.所以尽管它使用了 ob_size, 他的用途也不是当前对象的元素个数.

只看描述可能有点抽象, 我们看一个具体的例子.

编译环境:
    
    OS: Arch Linux x86_64 
    Kernel: 4.16.5-1-ARCH
    g++(GCC): 7.3.1 20180406
    Python: 3.8.0a0

在我的环境下 SHIFT 为 30 MASK为 2**30-1

我们来查看一下 1152921506754330628(这个数容易分析:]笑哭) 这个数字是这样储存的 ob_size为3, ob_digit为[4,2,1] 我们看图说话:
![PyLongObject存储示意图](https://copie.cn/usr/uploads/2018/05/639844390.png)

看起来很简单吧其实就是一个进制转换的过程: 2**30进制转10进制!

## Hack

```python
/* Convert an integer to a base 10 string.  Returns a new non-shared
   string.  (Return value is non-shared so that callers can modify the
   returned value if necessary.) */

static int
long_to_decimal_string_internal(PyObject *aa,
                                PyObject **p_output,
                                _PyUnicodeWriter *writer,
                                _PyBytesWriter *bytes_writer,
                                char **bytes_str)
{
    PyLongObject *scratch, *a;
    PyObject *str = NULL;
    Py_ssize_t size, strlen, size_a, i, j;
    digit *pout, *pin, rem, tenpow;
    int negative;
    int d;
    enum PyUnicode_Kind kind;

    a = (PyLongObject *)aa;
    printf("==== Hack Code ====\n");
    printf("PyLong_SHIFT = %d\n", PyLong_SHIFT);
    printf("PyLong_MASK = %d\n", PyLong_MASK);
    printf("ob_size     = %d\n", Py_SIZE(a));
    for (int ob_i = 0; ob_i < Py_SIZE(a); ++ob_i)
    {
        printf("ob_digit[%d] = %d\n", ob_i, a->ob_digit[ob_i]);
    }
    printf("====    End    ====\n");
    .
    .
    .
}
```

测试

```
Python 3.8.0a0 (heads/master-dirty:491bbedc20, May  3 2018, 11:24:17) 
[GCC 7.3.1 20180406] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> 1*2**(30*3)+2*2**(30*2)+3*2**(30*1)+4*2**(30*0)
==== Hack Code ====
PyLong_SHIFT = 30
PyLong_MASK = 1073741823
ob_size     = 4
ob_digit[0] = 4
ob_digit[1] = 3
ob_digit[2] = 2
ob_digit[3] = 1
====    End    ====
1237940041591223287334043652
>>> 
```

## 柔性数组

在 struct_longobject 中 有下面一个声明:

    digit ob_digit[1];

一个数组只有一个元素,然而我们在 Hack 的时候明明访问到了大于 0 的位置,这个概念就是柔性数组.这个内存空间是后来开辟的.在C99标准中，结构体的最后一个元素允许是未知大小的数组，这被称为不完整类型.至于为什么是 1 而 不是 0, 是因为不必为一些比较小的数(abs(x) <= 2**30-1)去缓存区开辟空间,虽然 PyLongObject 中比是 0 的时候多了一点空间,但是在运行的时候可以省更多时间.这就是空间与时间之间的取舍.