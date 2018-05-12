# Python内核源码阅读(十六)

## 字典对象的操作
字典对象的类型 PyDict_Type
```C
PyTypeObject PyDict_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    "dict",
    sizeof(PyDictObject),
    0,
    (destructor)dict_dealloc,                   /* tp_dealloc */
    0,                                          /* tp_print */
    0,                                          /* tp_getattr */
    0,                                          /* tp_setattr */
    0,                                          /* tp_reserved */
    (reprfunc)dict_repr,                        /* tp_repr */
    0,                                          /* tp_as_number */
    &dict_as_sequence,                          /* tp_as_sequence */
    &dict_as_mapping,                           /* tp_as_mapping */
...
};
```
字典对象的映射操作(tp_as_mapping),对应的函数是 dict_as_mapping
```C
static PyMappingMethods dict_as_mapping = {
    (lenfunc)dict_length, /*mp_length*/
    (binaryfunc)dict_subscript, /*mp_subscript*/
    (objobjargproc)dict_ass_sub, /*mp_ass_subscript*/
};
```
### 获取元素
```C
static PyObject *
dict_subscript(PyDictObject *mp, PyObject *key)
{
    Py_ssize_t ix;
    Py_hash_t hash;
    PyObject *value;

    if (!PyUnicode_CheckExact(key) ||
        (hash = ((PyASCIIObject *) key)->hash) == -1) {
        hash = PyObject_Hash(key);
        if (hash == -1)
            return NULL;
    }
    ix = (mp->ma_keys->dk_lookup)(mp, key, hash, &value);
    if (ix == DKIX_ERROR)
        return NULL;
    if (ix == DKIX_EMPTY || value == NULL) {
        if (!PyDict_CheckExact(mp)) {
            /* Look up __missing__ method if we're a subclass. */
            PyObject *missing, *res;
            _Py_IDENTIFIER(__missing__);
            missing = _PyObject_LookupSpecial((PyObject *)mp, &PyId___missing__);
            if (missing != NULL) {
                res = PyObject_CallFunctionObjArgs(missing,
                                                   key, NULL);
                Py_DECREF(missing);
                return res;
            }
            else if (PyErr_Occurred())
                return NULL;
        }
        _PyErr_SetKeyError(key);
        return NULL;
    }
    Py_INCREF(value);
    return value;
}
```
像 d[key] 这样的下标访问 会调用 dict_subscript 来获取字典的value.
dict_subscript 会对 key 进行类型检查和 hash 检查, 然后调用 PyDictObject 对象中的 PyDictKeyObject 对象的搜索函数 dk_lookup 来获取 value, 如果获取成功就会直接返回 value ,如果失败就会检查用户是否自己定义了 __missing__ 这个魔法函数.如果有定义就会按照其继续寻找.

## 搜索策略

Python3 为 PyDictObject 对象提供了 4 种搜索策略:

+ lookdict, 通用搜索函数
+ lookdict_unicode 针对 Unicode 字符串 keys 优化的搜索函数
+ lookdict_unicode_nodummp,类似于 lookdict_unicode 搜索,专门用在已知没有 dump 值的搜索.
+ look_split 被用在 split-table 的 lookdict 搜索.

让我们先看通用的搜索函数 lookdict:
```C
/*
The basic lookup function used by all operations.
This is based on Algorithm D from Knuth Vol. 3, Sec. 6.4.
Open addressing is preferred over chaining since the link overhead for
chaining would be substantial (100% with typical malloc overhead).

The initial probe index is computed as hash mod the table size. Subsequent
probe indices are computed as explained earlier.

All arithmetic on hash should ignore overflow.

The details in this version are due to Tim Peters, building on many past
contributions by Reimer Behrends, Jyrki Alakuijala, Vladimir Marangozov and
Christian Tismer.

lookdict() is general-purpose, and may return DKIX_ERROR if (and only if) a
comparison raises an exception.
lookdict_unicode() below is specialized to string keys, comparison of which can
never raise an exception; that function can never return DKIX_ERROR when key
is string.  Otherwise, it falls back to lookdict().
lookdict_unicode_nodummy is further specialized for string keys that cannot be
the <dummy> value.
For both, when the key isn't found a DKIX_EMPTY is returned.
*/
static Py_ssize_t _Py_HOT_FUNCTION
lookdict(PyDictObject *mp, PyObject *key,
         Py_hash_t hash, PyObject **value_addr)
{
    size_t i, mask, perturb;
    PyDictKeysObject *dk;
    PyDictKeyEntry *ep0;

top:
    dk = mp->ma_keys;
    ep0 = DK_ENTRIES(dk);
    mask = DK_MASK(dk);
    perturb = hash;
    // [1]
    i = (size_t)hash & mask;

    for (;;) {
        // [2]
        Py_ssize_t ix = dk_get_index(dk, i);
        // [3] 
        if (ix == DKIX_EMPTY) {
            *value_addr = NULL;
            return ix;
        }
        if (ix >= 0) {
            // [4]
            PyDictKeyEntry *ep = &ep0[ix];
            assert(ep->me_key != NULL);
            if (ep->me_key == key) {
                *value_addr = ep->me_value;
                return ix;
            }
            // [5]
            if (ep->me_hash == hash) {
                PyObject *startkey = ep->me_key;
                Py_INCREF(startkey);
                int cmp = PyObject_RichCompareBool(startkey, key, Py_EQ);
                Py_DECREF(startkey);
                if (cmp < 0) {
                    *value_addr = NULL;
                    return DKIX_ERROR;
                }
                if (dk == mp->ma_keys && ep->me_key == startkey) {
                    if (cmp > 0) {
                        *value_addr = ep->me_value;
                        return ix;
                    }
                }
                else {
                    /* The dict was mutated, restart */
                    goto top;
                }
            }
        }
        // [6]
        perturb >>= PERTURB_SHIFT;
        i = (i*5 + perturb + 1) & mask;
    }
    Py_UNREACHABLE();
}
```
[1] 我们需要将 hash 值映射到哈希表 dk_indices 中的某一个 slot,这里将 hash 与 DK_MASK(dk) 作与操作,保证了这个 slot 一定在哈希表上(小于 dk_size)

    #define DK_MASK(dk) (((dk)->dk_size)-1)

如何保证呢? 因为hash表的大小是 2 的幂次, 对于一个值对 2 的幂次取余会等于对 2 的幂次 -1 作与运算.

```python
In [2]: size = 2 << 5

In [3]: 100 % size
Out[3]: 36

In [4]: 100&(size-1)
Out[4]: 36

In [5]: 
```

[2] 这里通过 dk_get_index 函数获取从 dk_indices 到 dk_entries 的 index

 ```C
 /* lookup indices.  returns DKIX_EMPTY, DKIX_DUMMY, or ix >=0 */
static inline Py_ssize_t
// #define DKIX_EMPTY (-1)
// #define DKIX_DUMMY (-2)
dk_get_index(PyDictKeysObject *keys, Py_ssize_t i)
{
    Py_ssize_t s = DK_SIZE(keys);
    Py_ssize_t ix;

    if (s <= 0xff) {
        int8_t *indices = (int8_t*)(keys->dk_indices);
        ix = indices[i];
    }
    else if (s <= 0xffff) {
        int16_t *indices = (int16_t*)(keys->dk_indices);
        ix = indices[i];
    }
#if SIZEOF_VOID_P > 4
    else if (s > 0xffffffff) {
        int64_t *indices = (int64_t*)(keys->dk_indices);
        ix = indices[i];
    }
#endif
    else {
        int32_t *indices = (int32_t*)(keys->dk_indices);
        ix = indices[i];
    }
    // 保证返回值符合上方注释的要求
    assert(ix >= DKIX_DUMMY);
    return ix;
}
```

[3] 如果 entry 是 Unused 状态 index == DKIX_EMPTY 表示该 entry 可以被使用

[4] 对于 index >= 0 情况下, 取出 index 对应在 dk_entries 中的 entry, 比较 key 的引用是否相等.因为两个 key 都是 PyObject* 指针,所以比较的是引用相等,而不是值相等.

[5] 如果 key 的引用不相等的话, 就会对两个 key 进行值检查. 值检查之前会判断连个对象的 hash 值是否相同不相等的话值一定不相等; 如果 hash 值相等 ,就通过 PyObject_RichCompareBool 进行值相等判断.

```C
/* Perform a rich comparison with integer result.  This wraps
   PyObject_RichCompare(), returning -1 for error, 0 for false, 1 for true. */
int
PyObject_RichCompareBool(PyObject *v, PyObject *w, int op)
{
    PyObject *res;
    int ok;

    /* Quick result when objects are the same.
       Guarantees that identity implies equality. */
    if (v == w) {
        if (op == Py_EQ)
            return 1;
        else if (op == Py_NE)
            return 0;
    }

    res = PyObject_RichCompare(v, w, op);
    if (res == NULL)
        return -1;
    if (PyBool_Check(res))
        ok = (res == Py_True);
    else
        ok = PyObject_IsTrue(res);
    Py_DECREF(res);
    return ok;
}
```
PyObject_RichCompareBool 提供指定的比较操作类型 当(v op w) 成立时返回 1 不成立 0 异常 -1.

[6] 到达这里有两种可能:

+ index == DKIX_DUMP
+ hash 相等, key 不相等

这就说明发生了冲突,我们前面已经说了 Python 使用的是 开放定址法.通过:

        perturb >>= PERTURB_SHIFT;
        i = (i*5 + perturb + 1) & mask;
我们知道这是使用的随机探测:

> 将线性探测的步长从常数改为随机数，即令： j ＝ (j ＋ RN) % m ，其中 RN 是一个随机数。在实际程序中应预先用随机数发生器产生一个随机序列，将此序列作为依次探测的步长。这样就能使不同的关键字具有不同的探测次序，从而可以避 免或减少堆聚。基于与线性探测法相同的理由，在线性补偿探测法和随机探测法中，删除一个记录后也要打上删除标记。