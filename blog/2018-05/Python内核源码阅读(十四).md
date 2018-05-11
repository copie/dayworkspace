# Python内核源码阅读(十四)

## dict 的存储方式

Python3 的 dict 对象  PyDictObject:
```C
typedef struct _dictkeysobject PyDictKeysObject;

/* The ma_values pointer is NULL for a combined table
 * or points to an array of PyObject* for a split table
 */
typedef struct {
    PyObject_HEAD

    /* Number of items in the dictionary */
    // Active元素个数
    Py_ssize_t ma_used;

    /* Dictionary version: globally unique, value change each time
       the dictionary is modified */
    // 全局唯一, 值会随着 dict 的修改而变化
    uint64_t ma_version_tag;

    PyDictKeysObject *ma_keys;

    /* If ma_values is NULL, the table is "combined": keys and values
       are stored in ma_keys.

       If ma_values is not NULL, the table is splitted:
       keys are stored in ma_keys and values are stored in ma_values */
    // 见下解释
    PyObject **ma_values;
} PyDictObject;
```

从注释中可以看出,Python 中的 dict 在内存中有两种形式:

+ combined-table: **ma_values 这个指针则是空, key 和 values 都存储在 ma_keys(也就是 PyDictKeyObject) 中.
+ split-table: keys 和 values 分别存储着 ma_keys 和 ma_values 中.

split-table 这种形式是 Python3.3/3,4 引进的[Key-Sharing Dictionary](https://www.python.org/dev/peps/pep-0412/)其主要出于对优化同一类的实例对象的属性字典(__dict__), 共同分享同一份 Key, 在面向对象编程中,实例化对象较多的情况下,可以节省内存开销.

```C
struct _dictkeysobject {
    Py_ssize_t dk_refcnt;

    /* Size of the hash table (dk_indices). It must be a power of 2. */
    // hash 表允许容纳元素的个数 必定是 2 的倍数
    Py_ssize_t dk_size;

    /* Function to lookup in the hash table (dk_indices):

       - lookdict(): general-purpose, and may return DKIX_ERROR if (and
         only if) a comparison raises an exception.

       - lookdict_unicode(): specialized to Unicode string keys, comparison of
         which can never raise an exception; that function can never return
         DKIX_ERROR.

       - lookdict_unicode_nodummy(): similar to lookdict_unicode() but further
         specialized for Unicode string keys that cannot be the <dummy> value.

       - lookdict_split(): Version of lookdict() for split tables. */
    // 与 hash表 有关的函数
    dict_lookup_func dk_lookup;

    /* Number of usable entries in dk_entries. */
    // 可用的元素个数 
    // #define USABLE_FRACTION(n) (((n) << 1)/3)
    // 这个值是通过上面的宏算出来的
    Py_ssize_t dk_usable;

    /* Number of used entries in dk_entries. */
    // Active 元素个数
    Py_ssize_t dk_nentries;

    /* Actual hash table of dk_size entries. It holds indices in dk_entries,
       or DKIX_EMPTY(-1) or DKIX_DUMMY(-2).

       Indices must be: 0 <= indice < USABLE_FRACTION(dk_size).

       The size in bytes of an indice depends on dk_size:

       - 1 byte if dk_size <= 0xff (char*)
       - 2 bytes if dk_size <= 0xffff (int16_t*)
       - 4 bytes if dk_size <= 0xffffffff (int32_t*)
       - 8 bytes otherwise (int64_t*)

       Dynamically sized, SIZEOF_VOID_P is minimum. */
    // 397f1b28c4a12e3b3ed59a89599eabc457412649 这个提交说明了为什么和 Python3.6 不同
    // dk_indices 是一个柔性数组,存储的类型不是严格限制的
    char dk_indices[];  /* char is required to avoid strict aliasing. */

    /* "PyDictKeyEntry dk_entries[dk_usable];" array follows:
       see the DK_ENTRIES() macro */
};
```

```C
#define DK_ENTRIES(dk) \
    ((PyDictKeyEntry*)(&((int8_t*)((dk)->dk_indices))[DK_SIZE(dk) * DK_IXSIZE(dk)]))
```

从 Python3.6 开始,借鉴 PyPy 字典的设计.采用更加紧凑的储存结构.内存效率更高

内存分布是这样的:

```
layout:

+---------------+
| dk_refcnt     |
| dk_size       |
| dk_lookup     |
| dk_usable     |
| dk_nentries   |
+---------------+
| dk_indices    |
|               |
+---------------+
| dk_entries    |
|               |
+---------------+
``` 
我们举个例子:

    d = {'timmy': 'red', 'barry': 'green', 'guido': 'blue'}

Python3.6 之前:
```    
entries = [['--', '--', '--'],
        [-8522787127447073495, 'barry', 'green'],
        ['--', '--', '--'],
        ['--', '--', '--'],
        ['--', '--', '--'],
        [-9092791511155847987, 'timmy', 'red'],
        ['--', '--', '--'],
        [-6480567542315338377, 'guido', 'blue']]
```

Python3.6以后
```
indices =  [None, 1, None, None, None, 0, None, 2]
entries =  [[-9092791511155847987, 'timmy', 'red'],
            [-8522787127447073495, 'barry', 'green'],
            [-6480567542315338377, 'guido', 'blue']]

```
这种entries结构更加的紧凑了,并且 hash表 的内存占用也变小了,类似于这样:

    entries[indices[hash_fun("barry")]]

indices 中存储的就是 index .这样就可以容易找到我们想要的 entry 了.
 
## dict 中的 entry

在 dict 中, key-value 结构(键值对) 叫做 entry. 在同一个 dict 中,每个 entry 的 key 都是不同的,用来作为获取 value 的索引.

```C
typedef struct {
    /* Cached hash code of me_key. */
    Py_hash_t me_hash;
    PyObject *me_key;
    PyObject *me_value; /* This field is only meaningful for combined tables */
} PyDictKeyEntry;
``` 
在 Python3 中, 每个 entry 有四种状态:
+ Unused, index == DKIX_EMPTY. 这是每个 entry 的初始状态, me_key 和 me_value 都是 NULL.这个状态的 entry 可以转化成 Active 状态.
+ Active, index >= 0, me_key != NULL and me_value != NULL. 这时候, 该entry中存储了一个键值对, me_key和me_value都是NULL. 这也是唯一一种me_value不为NULL的状态.
+ Dummy, index == DKIX_DUMMY. dict中的一个元素被删除了, 这个元素所在的entry也不能从dict中删掉, 状态也不能直接转到Unused, 否则会导致探测链断掉, 其后的元素无法被探测. 但这个元素确实已经不再处于Active状态了. 这种情况下, 该entry就转为Dummy状态.
+ Pending. index >= 0, key != NULL, and value == NULL. 这种状态只发生在split-table中, 表示还没有插入到split-table中.








