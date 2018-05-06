# Python内核源码阅读(七)

我们在[Python内核源码阅读(六)](https://copie.cn/index.php/archives/Python%E5%86%85%E6%A0%B8%E6%BA%90%E7%A0%81%E9%98%85%E8%AF%BB-%E5%85%AD.html)中学到一个 PyLongObject 有那些内置方法, x,obase 不同而分不同情况去创建一个 PyLongObject.

## PyLong_FromLong

```C
PyObject *
PyLong_FromLong(long ival)
{
    PyLongObject *v;
    unsigned long abs_ival;
    unsigned long t;  /* unsigned so >> doesn't propagate sign bit */
    int ndigits = 0;
    int sign;

    // 检查是否是小整数
    CHECK_SMALL_INT(ival);

    // 如果是负数
    if (ival < 0) {
        /* negate: can't write this as abs_ival = -ival since that
           invokes undefined behaviour when ival is LONG_MIN */
        abs_ival = 0U-(unsigned long)ival;
        // 被 0 减得绝对值
        sign = -1;
        // 符号位为-1 表示创建的数是负数
    }
    else {
        abs_ival = (unsigned long)ival;
        sign = ival == 0 ? 0 : 1;
        // 如果这个数是整数 符号位为 1, 这个数是 0 符号位 为 0 
    }

    /* Fast path for single-digit ints */
    // 如果这个数比 2^30(64位) 或者 2^15(32位) 小
    if (!(abs_ival >> PyLong_SHIFT)) {
        // 创建一个 PyLongObject 对象 ob_digit 长度为 1
        v = _PyLong_New(1);
        if (v) {
            Py_SIZE(v) = sign;
            // 一位ob_digit就可以存储
            v->ob_digit[0] = Py_SAFE_DOWNCAST(
                abs_ival, unsigned long, digit);
            // Py_SAFE_DOWNCAST(abs_ival, unsigned long, digit)
            // 其实就是 (unsigned short) abs_ival
        }
        return (PyObject*)v;
    }

#if PyLong_SHIFT==15
    /* 2 digits */
    // 这里是针对 32 位 如果 abs_ival 大于 2^15 并且 小于 2^30时
    if (!(abs_ival >> 2*PyLong_SHIFT)) {
        v = _PyLong_New(2);
        if (v) {
            Py_SIZE(v) = 2*sign;
            v->ob_digit[0] = Py_SAFE_DOWNCAST(
                abs_ival & PyLong_MASK, unsigned long, digit);
            v->ob_digit[1] = Py_SAFE_DOWNCAST(
                  abs_ival >> PyLong_SHIFT, unsigned long, digit);
        }
        return (PyObject*)v;
    }
#endif

    /* Larger numbers: loop to determine number of digits */
    // 循环计算 需要多少 digits
    t = abs_ival;
    while (t) {
        ++ndigits;
        t >>= PyLong_SHIFT;
    }
    v = _PyLong_New(ndigits);
    if (v != NULL) {
        digit *p = v->ob_digit;
        Py_SIZE(v) = ndigits*sign;
        // 设置 创建对象的 ob_size
        // #define Py_SIZE(ob)             (((PyVarObject*)(ob))->ob_size)
        t = abs_ival;
        while (t) {
            *p++ = Py_SAFE_DOWNCAST(
                t & PyLong_MASK, unsigned long, digit);
            t >>= PyLong_SHIFT;
        }
    }
    return (PyObject *)v;
}
```

这个函数看起来也挺好理解的

## 小整数对象

我们在上面说的 CHECK_SMALL_INT 让我们看一下,它的定义.

```C
static PyObject *
get_small_int(sdigit ival)
{
    PyObject *v;
    assert(-NSMALLNEGINTS <= ival && ival < NSMALLPOSINTS);
    v = (PyObject *)&small_ints[ival + NSMALLNEGINTS];
    Py_INCREF(v);
#ifdef COUNT_ALLOCS
    if (ival >= 0)
        quick_int_allocs++;
    else
        quick_neg_int_allocs++;
#endif
    return v;
}
#define CHECK_SMALL_INT(ival) \
    do if (-NSMALLNEGINTS <= ival && ival < NSMALLPOSINTS) { \
        return get_small_int((sdigit)ival); \
    } while(0)
```

 这里看起来是如果 ival 的值在[ -NSMALLNEGINTS,NSMALLPOSINTS)就会直接返回 small_ints 中对应位置 (ival + NSMALLNEGINTS) 的值

看一下下面的问题

```Python
In [1]: a = -6

In [2]: b = -6

In [3]: a is b
Out[3]: False

In [4]: a = -5

In [5]: b = -5

In [6]: a is b
Out[6]: True

In [7]: a = 256

In [8]: b = 256

In [9]: a is b
Out[9]: True

In [10]: a = 257

In [11]: b = 257

In [12]: a is b
Out[12]: False
```
这种效果的产生就是因为在Python中创建对象时,分为小整数和大整数

我们现在看一下小整数类型的范围是怎么定义的

```C
#ifndef NSMALLPOSINTS
#define NSMALLPOSINTS           257
#endif
#ifndef NSMALLNEGINTS
#define NSMALLNEGINTS           5
#endif
.
.
.
#if NSMALLNEGINTS + NSMALLPOSINTS > 0
/* Small integers are preallocated in this array so that they
   can be shared.
   The integers that are preallocated are those in the range
   -NSMALLNEGINTS (inclusive) to NSMALLPOSINTS (not inclusive).
*/
static PyLongObject small_ints[NSMALLNEGINTS + NSMALLPOSINTS];
```

从上面的代码可以看出, Python 会预先默认为[-5,257)之间的整数到 small_ints 指针数组(对象池)缓存,对象池里每一个 PyLongObject 对象能被任意共享. 小整数一般是 Python 程序中高频使用的整数对象,使用小整数对象池可以避免在一些简单的循环和计算中频繁的开辟和创建内存空间. 这样频繁的内存操作不仅降低运行效率,而且会在系统堆上造成大量的内存碎片,严重影响 Python 整体性能.

small_ints 中的 PyLongObject 对象是在 Python 初始化的时候调用 _PyLong_Init 函数创建的：

```C
int
_PyLong_Init(void)
{
#if NSMALLNEGINTS + NSMALLPOSINTS > 0
    int ival, size;
    PyLongObject *v = small_ints;

    for (ival = -NSMALLNEGINTS; ival <  NSMALLPOSINTS; ival++, v++) {
        size = (ival < 0) ? -1 : ((ival == 0) ? 0 : 1);
        if (Py_TYPE(v) == &PyLong_Type) {
            /* The element is already initialized, most likely
             * the Python interpreter was initialized before.
             */
            Py_ssize_t refcnt;
            PyObject* op = (PyObject*)v;

            refcnt = Py_REFCNT(op) < 0 ? 0 : Py_REFCNT(op);
            _Py_NewReference(op);
            /* _Py_NewReference sets the ref count to 1 but
             * the ref count might be larger. Set the refcnt
             * to the original refcnt + 1 */
            Py_REFCNT(op) = refcnt + 1;
            assert(Py_SIZE(op) == size);
            assert(v->ob_digit[0] == (digit)abs(ival));
        }
        else {
            (void)PyObject_INIT(v, &PyLong_Type);
        }
        Py_SIZE(v) = size;
        v->ob_digit[0] = (digit)abs(ival);
    }
#endif
    _PyLong_Zero = PyLong_FromLong(0);
    if (_PyLong_Zero == NULL)
        return 0;
    _PyLong_One = PyLong_FromLong(1);
    if (_PyLong_One == NULL)
        return 0;

    /* initialize int_info */
    if (Int_InfoType.tp_name == NULL) {
        if (PyStructSequence_InitType2(&Int_InfoType, &int_info_desc) < 0)
            return 0;
    }

    return 1;
}
```

这里就是一个创建那些小整数然后把它放到 small_ints 中.

