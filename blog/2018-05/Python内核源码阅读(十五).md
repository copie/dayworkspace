# Python内核源码阅读(十五)

## 字典对象的创建

字典对象通过 PyDict_new 方法来创建.
```C
PyObject *
PyDict_New(void)
{
    // #define PyDict_MINSIZE 8 默认情况下会创建 8 个 entry
    PyDictKeysObject *keys = new_keys_object(PyDict_MINSIZE);
    if (keys == NULL)
        return NULL;
    return new_dict(keys, NULL);
}
```

```C
static PyDictKeysObject *new_keys_object(Py_ssize_t size)
{
    PyDictKeysObject *dk;
    Py_ssize_t es, usable;

    // size 必须大于 PyDict_MINSIZE , #define PyDict_MINSIZE 8
    // PyDict_MINSIZE 新字典的默认大小
    assert(size >= PyDict_MINSIZE);
    // size 必须是 2 的倍数
    assert(IS_POWER_OF_2(size));

    // #define USABLE_FRACTION(n) (((n) << 1)/3)
    // size 为 8 的字典中,最多只能容纳 5 个 PyDictKeyEntry
    usable = USABLE_FRACTION(size);
    // 通过 size 的大小确定 dk_entries 最多可以容纳的 PyDictKeyEntry 对象
    if (size <= 0xff) {
        es = 1;
    }
    else if (size <= 0xffff) {
        es = 2;
    }
#if SIZEOF_VOID_P > 4
    else if (size <= 0xffffffff) {
        es = 4;
    }
#endif
    else {
        es = sizeof(Py_ssize_t);
    }

    // Python 对象缓存机制, 创建默认 size 大小为 8 的字典会尝试从 keys_free_list 里面直接获取可用的 PyDictKeysObject 对象.
    
    if (size == PyDict_MINSIZE && numfreekeys > 0) {
        dk = keys_free_list[--numfreekeys];
        // 关于缓存下面介绍
    }
    else {
        // 这里的大小是 PyDictKeysObject 固定定义下的,和柔性数组 dk_indices 和 dk_entries 需要的的大小至于为什么不合 Python3.6 相同 请看十四
        dk = PyObject_MALLOC(sizeof(PyDictKeysObject)
                             + es * size
                             + sizeof(PyDictKeyEntry) * usable);
        if (dk == NULL) {
            PyErr_NoMemory();
            return NULL;
        }
    }
    DK_DEBUG_INCREF dk->dk_refcnt = 1;
    dk->dk_size = size;
    dk->dk_usable = usable;
    dk->dk_lookup = lookdict_unicode_nodummy;
    dk->dk_nentries = 0;
    // 初始化了dk_indices和dk_entries. dk_indices填充了0xff, 即DKIX_EMPTY(-1), dk_entries则初始化为空.
    memset(&dk->dk_indices[0], 0xff, es * size);
    memset(DK_ENTRIES(dk), 0, sizeof(PyDictKeyEntry) * usable);
    return dk;
}
```

PyDictKeyObject 创建完成后就会调用 new_dict 来完成对于 PyDictObject 对象的创建:

```C
/* Consumes a reference to the keys object */
static PyObject *
new_dict(PyDictKeysObject *keys, PyObject **values)
{
    PyDictObject *mp;
    assert(keys != NULL);
    if (numfree) {
        mp = free_list[--numfree];
        assert (mp != NULL);
        assert (Py_TYPE(mp) == &PyDict_Type);
        _Py_NewReference((PyObject *)mp);
    }
    else {
        mp = PyObject_GC_New(PyDictObject, &PyDict_Type);
        if (mp == NULL) {
            DK_DECREF(keys);
            free_values(values);
            return NULL;
        }
    }
    mp->ma_keys = keys;
    mp->ma_values = values;
    mp->ma_used = 0;
    mp->ma_version_tag = DICT_NEXT_VERSION();
    assert(_PyDict_CheckConsistency(mp));
    return (PyObject *)mp;
}
```

PyDictObject 的对象池机制和 PyListObject 的对象机制也类似,也是在 PyDictObject 对象销毁的时候放入 free_list 对象池.

```C

static void
dict_dealloc(PyDictObject *mp)
{
    PyObject **values = mp->ma_values;
    PyDictKeysObject *keys = mp->ma_keys;
    Py_ssize_t i, n;

    /* bpo-31095: UnTrack is needed before calling any callbacks */
    PyObject_GC_UnTrack(mp);
    Py_TRASHCAN_SAFE_BEGIN(mp)
    if (values != NULL) {
        if (values != empty_values) {
            for (i = 0, n = mp->ma_keys->dk_nentries; i < n; i++) {
                Py_XDECREF(values[i]);
            }
            free_values(values);
        }
        DK_DECREF(keys);
    }
    else if (keys != NULL) {
        assert(keys->dk_refcnt == 1);
        DK_DECREF(keys);
    }
    if (numfree < PyDict_MAXFREELIST && Py_TYPE(mp) == &PyDict_Type)
        free_list[numfree++] = mp;
    else
        Py_TYPE(mp)->tp_free((PyObject *)mp);
    Py_TRASHCAN_SAFE_END(mp)
}
```
这里也会对 PyDictObject 对象所指的 PyDictKeysObject 对象放入 keys_free_list 对象池中.