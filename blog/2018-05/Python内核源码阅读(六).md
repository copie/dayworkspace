# Python内核源码阅读(六)

我们在[Python内核源码阅读(三)](https://copie.cn/index.php/archives/Python-%E5%86%85%E6%A0%B8%E6%BA%90%E7%A0%81%E9%98%85%E8%AF%BB-%E5%9B%9B.html)中学到了,在Python3 中一个 PyLongObject 的存储方式.今天会更加深入的了解 PyLongObject.

## PyLongObject 内置方法

```C
PyTypeObject PyLong_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    "int",                                      /* tp_name */
    offsetof(PyLongObject, ob_digit),           /* tp_basicsize */
    sizeof(digit),                              /* tp_itemsize */
    long_dealloc,                               /* tp_dealloc */
    0,                                          /* tp_print */
    0,                                          /* tp_getattr */
    0,                                          /* tp_setattr */
    0,                                          /* tp_reserved */
    long_to_decimal_string,                     /* tp_repr */
    &long_as_number,                            /* tp_as_number */
    0,                                          /* tp_as_sequence */
    0,                                          /* tp_as_mapping */
    (hashfunc)long_hash,                        /* tp_hash */
    0,                                          /* tp_call */
    long_to_decimal_string,                     /* tp_str */
    PyObject_GenericGetAttr,                    /* tp_getattro */
    0,                                          /* tp_setattro */
    0,                                          /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE |
        Py_TPFLAGS_LONG_SUBCLASS,               /* tp_flags */
    long_doc,                                   /* tp_doc */
    0,                                          /* tp_traverse */
    0,                                          /* tp_clear */
    long_richcompare,                           /* tp_richcompare */
    0,                                          /* tp_weaklistoffset */
    0,                                          /* tp_iter */
    0,                                          /* tp_iternext */
    long_methods,                               /* tp_methods */
    0,                                          /* tp_members */
    long_getset,                                /* tp_getset */
    0,                                          /* tp_base */
    0,                                          /* tp_dict */
    0,                                          /* tp_descr_get */
    0,                                          /* tp_descr_set */
    0,                                          /* tp_dictoffset */
    0,                                          /* tp_init */
    0,                                          /* tp_alloc */
    long_new,                                   /* tp_new */
    PyObject_Del,                               /* tp_free */
};
```

<table>
    <tr>
        <th>int 类型的元信息</th>
        <th>说明</th>
    </tr>
    <tr>
        <td>long_dealloc</td>
        <td>对象的析构函数</td>
    </tr>
    <tr>
        <td>PyObject_Del</td>
        <td>对象释放操作</td>
    </tr>
    <tr>
        <td>long_to_decimal_string</td>
        <td>转化为PyStringObject</td>
    </tr>
    <tr>
        <td>long_hash</td>
        <td>获取hash值</td>
    </tr>
    <tr>
        <td>long_richcompare</td>
        <td>比较操作</td>
    </tr>
    <tr>
        <td>long_doc</td>
        <td>文档字符串</td>
    </tr>
    <tr>
        <td>long_as_number</td>
        <td>数值操作族</td>
    </tr>
    <tr>
        <td>long_methods</td>
        <td>成员函数集合</td>
    </tr>
</table>

## 整数对象的创建

对象的创建总是调用对应的类型对象的 tp_new, PyLongObject 的 ob_type 指针指向的是 PyLong_Type, 定义在 Objects/longobject.c 就是我们上面贴出来的代码.

```C
static PyObject *
long_new_impl(PyTypeObject *type, PyObject *x, PyObject *obase);

static PyObject *
long_new(PyTypeObject *type, PyObject *args, PyObject *kwargs)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"", "base", NULL};
    static _PyArg_Parser _parser = {"|OO:int", _keywords, 0};
    PyObject *x = NULL;
    PyObject *obase = NULL;

    if (!_PyArg_ParseTupleAndKeywordsFast(args, kwargs, &_parser,
        &x, &obase)) {
        goto exit;
    }
    return_value = long_new_impl(type, x, obase);

exit:
    return return_value;
}
```

我们这里看到实际上创建一个整数用的是 long_new_impl, 让我们看一下他

```C
static PyObject *
long_new_impl(PyTypeObject *type, PyObject *x, PyObject *obase)
/*[clinic end generated code: output=e47cfe777ab0f24c input=81c98f418af9eb6f]*/
{
    Py_ssize_t base;

    if (type != &PyLong_Type)
        return long_subtype_new(type, x, obase); /* Wimp out */
    if (x == NULL) {
        if (obase != NULL) {
            PyErr_SetString(PyExc_TypeError,
                            "int() missing string argument");
            return NULL;
        }
        return PyLong_FromLong(0L);
    }
    if (obase == NULL)
        return PyNumber_Long(x);

    base = PyNumber_AsSsize_t(obase, NULL);
    if (base == -1 && PyErr_Occurred())
        return NULL;
    if ((base != 0 && base < 2) || base > 36) {
        PyErr_SetString(PyExc_ValueError,
                        "int() base must be >= 2 and <= 36, or 0");
        return NULL;
    }

    if (PyUnicode_Check(x))
        return PyLong_FromUnicodeObject(x, (int)base);
    else if (PyByteArray_Check(x) || PyBytes_Check(x)) {
        char *string;
        if (PyByteArray_Check(x))
            string = PyByteArray_AS_STRING(x);
        else
            string = PyBytes_AS_STRING(x);
        return _PyLong_FromBytes(string, Py_SIZE(x), (int)base);
    }
    else {
        PyErr_SetString(PyExc_TypeError,
                        "int() can't convert non-string with explicit base");
        return NULL;
    }
}
```

再看一段 Python3 int 类型的文档字符串

```
int([x]) -> integer
int(x, base=10) -> integer

Convert a number or string to an integer, or return 0 if no arguments
are given.  If x is a number, return x.__int__().  For floating point
numbers, this truncates towards zero.

If x is not a number or if base is given, then x must be a string,
bytes, or bytearray instance representing an integer literal in the
given base.  The literal can be preceded by '+' or '-' and be surrounded
by whitespace.  The base defaults to 10.  Valid bases are 0 and 2-36.
Base 0 means to interpret the base from the string as an integer literal.
>>> int('0b100', base=0)
4
```

从 long_new_impl 的函数中可以看出, int 的参数 x 和 base 分别对应着 long_new_impl 的后两个参数.

为了创建 PyLongObject 对象, Python 分一下几种情况:

+ x == NULL and obase != NULL -> PyLong_FromLong(0L)
+ obase == NULL  -> PyNumber_Long(x)
+ x != NULL and obase != NULL
    + PyUnicode -> PyLong_FromUnicodeObject -> PyLong_FromString
    + PyByteArry / PyBytes -> _PyLong_FromBytes ->  PyLong_FromString

而实际上PyLong_FromUnicodeObject和_PyLong_FromBytes都是先将PyUnicode对象和PyByteArrry/PyBytes对象转化成string（c中的char *），然后再调用PyLong_FromString。