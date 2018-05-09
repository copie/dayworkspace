# Python内核源码阅读(十)

## 字符串对象的创建

```C
PyObject *
//从Unicode字符串创建一个 PyUnicodeObject 对象
PyUnicode_FromUnicode(const Py_UNICODE *u, Py_ssize_t size)
{
    // 建立指定长度的 PyUnicodeObject 对象
    if (u == NULL)
        return (PyObject*)_PyUnicode_New(size);

    if (size < 0) {
        PyErr_BadInternalCall();
        return NULL;
    }
    // 实际的实现 交给了 PyUnicode_FromWideChar
    return PyUnicode_FromWideChar(u, size);
}

PyObject *
PyUnicode_FromWideChar(const wchar_t *u, Py_ssize_t size)
{
    PyObject *unicode;
    Py_UCS4 maxchar = 0;
    Py_ssize_t num_surrogates;

    if (u == NULL && size != 0) {
        PyErr_BadInternalCall();
        return NULL;
    }

    if (size == -1) {
        size = wcslen(u);
    }

    /* If the Unicode data is known at construction time, we can apply
       some optimizations which share commonly used objects. */

    /* Optimization for empty strings */
    if (size == 0)
        _Py_RETURN_UNICODE_EMPTY();

    /* Single character Unicode objects in the Latin-1 range are
       shared when using this constructor */
    // 使用单字符缓存池
    if (size == 1 && (Py_UCS4)*u < 256)
        return get_latin1_char((unsigned char)*u);

    /* If not empty and not single character, copy the Unicode data
       into the new object */
    // 寻找在这个字符串中 最宽的字符,放到 maxchar, 如果 *maxchar > MAX_UNICODE 会 return -1
    if (find_maxchar_surrogates(u, u + size,
                                &maxchar, &num_surrogates) == -1)
        return NULL;
    // 建立一个 最宽字符串宽度为 maxchar 的对象, 至于大小,为什么这么算是为了兼容 不同的 SIZEOF_WCHAR_T 具体我也不太了解
    unicode = PyUnicode_New(size - num_surrogates, maxchar);
    if (!unicode)
        return NULL;

    switch (PyUnicode_KIND(unicode)) {
    case PyUnicode_1BYTE_KIND:
        _PyUnicode_CONVERT_BYTES(Py_UNICODE, unsigned char,
                                u, u + size, PyUnicode_1BYTE_DATA(unicode));
        break;
    case PyUnicode_2BYTE_KIND:
#if Py_UNICODE_SIZE == 2
        memcpy(PyUnicode_2BYTE_DATA(unicode), u, size * 2);
#else
        _PyUnicode_CONVERT_BYTES(Py_UNICODE, Py_UCS2,
                                u, u + size, PyUnicode_2BYTE_DATA(unicode));
#endif
        break;
    case PyUnicode_4BYTE_KIND:
#if SIZEOF_WCHAR_T == 2
        /* This is the only case which has to process surrogates, thus
           a simple copy loop is not enough and we need a function. */
        unicode_convert_wchar_to_ucs4(u, u + size, unicode);
#else
        assert(num_surrogates == 0);
        memcpy(PyUnicode_4BYTE_DATA(unicode), u, size * 4);
#endif
        break;
    default:
        Py_UNREACHABLE();
    }

    return unicode_result(unicode);
}
```
上面的代码具体就是 PyUnicode_FromWideChar 通过 PyUnicode_New 去创建一个 PyUnicodeObject 对象.在 PyUnicode_New 就是对不同的 maxchar 开辟空间,初始化这片空间, 因为 unicode 在 Python 中有好几种,所以这里面有各种 分类讨论,也不容易理解.

## PyUnicodeObject 操作效率

Python中的字符串"+"操作对应的就是PyUnicode_Concat函数：
在 Python中使用 PyUnicode_Concat 去连接两个字符串

```C
/* Concat to string or Unicode object giving a new Unicode object. */

PyObject *
PyUnicode_Concat(PyObject *left, PyObject *right)
{
    PyObject *result;
    Py_UCS4 maxchar, maxchar2;
    Py_ssize_t left_len, right_len, new_len;

    if (ensure_unicode(left) < 0)
        return NULL;

    if (!PyUnicode_Check(right)) {
        PyErr_Format(PyExc_TypeError,
                     "can only concatenate str (not \"%.200s\") to str",
                     right->ob_type->tp_name);
        return NULL;
    }
    if (PyUnicode_READY(right) < 0)
        return NULL;

    /* Shortcuts */
    // 讨论空串问题
    if (left == unicode_empty)
        return PyUnicode_FromObject(right);
    if (right == unicode_empty)
        return PyUnicode_FromObject(left);

    // 字符串连接后长度限制
    left_len = PyUnicode_GET_LENGTH(left);
    right_len = PyUnicode_GET_LENGTH(right);
    if (left_len > PY_SSIZE_T_MAX - right_len) {
        PyErr_SetString(PyExc_OverflowError,
                        "strings are too large to concat");
        return NULL;
    }
    new_len = left_len + right_len;

    // 确定 最大的 maxchar
    maxchar = PyUnicode_MAX_CHAR_VALUE(left);
    maxchar2 = PyUnicode_MAX_CHAR_VALUE(right);
    maxchar = Py_MAX(maxchar, maxchar2);


    /* Concat the two Unicode strings */
    // 新建 PyUnicodeObject 后拷贝原字符串
    result = PyUnicode_New(new_len, maxchar);
    if (result == NULL)
        return NULL;
    _PyUnicode_FastCopyCharacters(result, 0, left, 0, left_len);
    _PyUnicode_FastCopyCharacters(result, left_len, right, 0, right_len);
    assert(_PyUnicode_CheckConsistency(result, 1));
    return result;
}
```

因为字符串对象是不可变对象，进行连接操作是会创建一个新的字符串对象。所以两字符串对象连接会先计算连接后字符串的长度，通过PyUnicode_New来申请内存空间，最后复制两字符串的内存空间数据。

这种连接操作作用在N个字符串对象上就显得非常低效率，连接N个字符串对象就需要进行N-1次的内存申请和(N-1)*2次的内存搬运工作，另外还有隐藏的垃圾回收操作。更好的做法是通过join操作来连接。

下面我们去看一下 join 是怎么实现的

```C
// seqlen表示list中元素个数
PyObject * _PyUnicode_JoinArray(PyObject *separator, PyObject **items, Py_ssize_t seqlen)
{
    PyObject *res = NULL; /* the result */
    PyObject *sep = NULL;
    Py_ssize_t seplen;
    PyObject *item;
    ...     // 省略变量声明若干

    sz = 0; // 记录总共要存放字符个数

    for (i = 0; i < seqlen; i++) {
        size_t add_sz;
        item = items[i];

        add_sz = PyUnicode_GET_LENGTH(item);
        item_maxchar = PyUnicode_MAX_CHAR_VALUE(item);
        maxchar = Py_MAX(maxchar, item_maxchar);
        if (i != 0) {
            add_sz += seplen;
        }
        sz += add_sz;
        last_obj = item;
    }

    res = PyUnicode_New(sz, maxchar);   // 申请内存
    if (res == NULL)
        goto onError;

    for (i = 0, res_offset = 0; i < seqlen; ++i) {
        Py_ssize_t itemlen;
        item = items[i];

        /* Copy item, and maybe the separator. */
        if (i && seplen != 0) {
            // 内存搬运
            _PyUnicode_FastCopyCharacters(res, res_offset, sep, 0, seplen);
            res_offset += seplen;   // 调整偏移量
        }

        itemlen = PyUnicode_GET_LENGTH(item);
        if (itemlen != 0) {
            _PyUnicode_FastCopyCharacters(res, res_offset, item, 0, itemlen);
            res_offset += itemlen;
        }
    }
    // 断言检查
    assert(res_offset == PyUnicode_GET_LENGTH(res));

    Py_XDECREF(sep);
    assert(_PyUnicode_CheckConsistency(res, 1));
    return res;

  onError:
    Py_XDECREF(sep);
    Py_XDECREF(res);
    return NULL;
}
```

执行join操作时，首先会统计list中多少个PyUnicodeObject对象，并统计每个对象所维护的字符串有多长， 进行求和执行一次申请空间。再逐一进行字符串拷贝。