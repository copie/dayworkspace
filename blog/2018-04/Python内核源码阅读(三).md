# Python 内核源码阅读(三)


## 定长对象与变长对象

在 C 语言中, 整型所占用的内存大小是固定的,无论你保存的是多少.由于 C 没有字符串类型,因此要表示一个字符串只能用字符数组表示,在 Python 中用如下的方式来表示一个字符串.

```python
[object.h]
typedef struct {
    PyObject ob_base;
    Py_ssize_t ob_size; /* Number of items in variable part */
} PyVarObject;
```

ob_size 表示的是容纳元素的个数,而不是占用内存的字节数(这符合面向对象的思想)

<table>
<tr>
    <th>int</th>
    <th>string</th>
    <th>list</th>
    <th>dict</th>
</tr>
<tr>
    <td>ob_refnt</td>
    <td>ob_refnt</td>
    <td>ob_refnt</td>
    <td>ob_refnt</td>
</tr>
<tr>
    <td>ob_type</td>
    <td>ob_type</td>
    <td>ob_type</td>
    <td>ob_type</td>
</tr><tr>
    <td>ob_digit[1]</td>
    <td>ob_size</td>
    <td>ob_size</td>
    <td>其他信息</td>
</tr><tr>
    <td>空</td>
    <td>其他信息</td>
    <td>其他信息</td>
    <td>空</td>
</tr>
</table>

## 类型对象

我们现在知道了每个 Python 对象的前几个字节是固定的,但是每个对象是不同的需要分配的空间也是不同的,到现在为止我们还没有了解到,我们要创建一个对象,需要开辟多大的内存.元信息就保存在 PyTypeObject 中.


```
typedef struct _typeobject {
    PyObject_VAR_HEAD
    const char *tp_name; /* For printing, in format "<module>.<name>" */
    Py_ssize_t tp_basicsize, tp_itemsize; /* For allocation */

    /* Methods to implement standard operations */

    destructor tp_dealloc;
    printfunc tp_print;
    getattrfunc tp_getattr;
    setattrfunc tp_setattr;
    PyAsyncMethods *tp_as_async; /* formerly known as tp_compare (Python 2)
                                    or tp_reserved (Python 3) */
    reprfunc tp_repr;
    .
    .
    .
    } PyTypeObject;
```

在 _typeObject 中定义了很多信息,主要有:

1. 类型名, tp_name, 主要是 Python 内部以及调试时使用.
2. 创建空间时分配的空间大小, tp_basesize 和 tp_itemsize.
3. 与对象相关的操作,如 tp_print, tp_add 这样的函数. 
4. 要描述本类型的其他信息

## Python 对象的分类

+ Fundamental 对象: 类型对象
+ Numeric 对象: 数值对象
+ Sequence 对象: 容纳其他对象的序列集合对象
+ Mapping 对象: 类似与C++ 中 map 映射对象
+ Internal 对象: Python 虚拟机在运行时内部使用的对象

![对象的分类](https://copie.cn/usr/uploads/2018/05/222118936.png)
