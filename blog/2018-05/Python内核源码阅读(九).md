# Python内核源码阅读(九)

正是因为 Python2 的 UnicodeError 让我放弃了它. Python3 就很少遇到了,Python3 原生的支持 Unicode 功劳不少.

在 Python3 中默认的字符串采用 Unicode 编码方式,先看一下它的定义.

Unicode 字符串有 4 种形式:

+ compact ascii
+ compact
+ legacy string, not ready
+ legacy string, ready

compact string 只使用一个内存块(结构体+字符)来存储,也就是内存是紧凑的,数据紧跟在结构体后面. compact string 只包含 latin1 编码范围的字符, ASCII-only(7-bits/U+0000-U+007f 范围内的字符)保存在 PyASCIIObject 结构体中, Non-ASCII(8-bits/一个字节大小的字符) 保存在 PyCompactUnicode 结构体中. legacy string 使用一个内存块保存 PyUnicodeObject, 另一个内存块来保存字符.

整个字符串对象是以 PyASCIIObject 为基础并扩展的.

```
typedef struct {
    PyObject_HEAD
    Py_ssize_t length;          /* Number of code points in the string */
    Py_hash_t hash;             /* Hash value; -1 if not set */
    struct {
        unsigned int interned:2;
        unsigned int kind:3;
        unsigned int compact:1;
        unsigned int ascii:1;
        unsigned int ready:1;
        unsigned int :24;
    } state;
    wchar_t *wstr;
} PyASCIIObject;
```
其中, length 中保存了字符串中码位(code points)的数量(所谓的码位数就是在该编码下有多少这种编码的字符), hash 是该字符串的 hash 值,可以节省计算量. state 就是为了确定上面说的四种形式的. wstr 是真实字符串, 以 NULL(\0) 结尾 和 C 中的字符串一样.

state 中除了和对象的 4 种形式有关的值(kind/compact/ascii/ready)以外,还有一个 interned 值. interned 标记了该对象是否已经经过 intern 机制处理.

## interm 机制

```C
void
PyUnicode_InternInPlace(PyObject **p)
{
    PyObject *s = *p;
    PyObject *t;
#ifdef Py_DEBUG
    assert(s != NULL);
    assert(_PyUnicode_CHECK(s));
#else
    if (s == NULL || !PyUnicode_Check(s))
        return;
#endif
    /* If it's a subclass, we don't really know what putting
       it in the interned dict might do. */
    // 检查是否是缓存过的对象,如果是就直接退出
    if (!PyUnicode_CheckExact(s))
        return;
    if (PyUnicode_CHECK_INTERNED(s))
        return;
    if (interned == NULL) {
        // 如果 没有创建 interned 就创建一个
        interned = PyDict_New();
        if (interned == NULL) {
            PyErr_Clear(); /* Don't leave an exception */
            return;
        }
    }
    Py_ALLOW_RECURSION
    // 尝试把 s 放入 interned 如果成功 返回原对象s 如果放入失败(已经缓存过)返回以前缓存的对象
    t = PyDict_SetDefault(interned, s, s);
    Py_END_ALLOW_RECURSION
    if (t == NULL) {
        PyErr_Clear();
        return;
    }
    if (t != s) {
        // 如果 返回的不是是原对象s, t的引用计数+1
        Py_INCREF(t);
        // 改变 p 的指向  原来的 p 对象会被回收
        Py_SETREF(*p, t);
        return;
    }
    /* The two references in interned are not counted by refcnt.
       The deallocator will take care of this */
    // 因为在 dict 中有对 key 和 value 的引用 如果不去掉,缓存对象永远不会被回收 所以这里要对 s 的引用计数 -2 
    Py_REFCNT(s) -= 2;
    // 把字符串标记成 SSTATE_INTERNED_MORTAL 表示被 intern 机制处理
    // SSTATE_INTERNED_IMMORTAL 表示 被 intern 机制处理的对象不可销毁和 Python 解释器共存亡
    _PyUnicode_STATE(s).interned = SSTATE_INTERNED_MORTAL;
}
```

```C
/* Safely decref `op` and set `op` to `op2`.
 *
 * As in case of Py_CLEAR "the obvious" code can be deadly:
 *
 *     Py_DECREF(op);
 *     op = op2;
 *
 * The safe way is:
 *
 *      Py_SETREF(op, op2);
 *
 * That arranges to set `op` to `op2` _before_ decref'ing, so that any code
 * triggered as a side-effect of `op` getting torn down no longer believes
 * `op` points to a valid object.
 *
 * Py_XSETREF is a variant of Py_SETREF that uses Py_XDECREF instead of
 * Py_DECREF.
 */

#define Py_SETREF(op, op2)                      \
    do {                                        \
        PyObject *_py_tmp = (PyObject *)(op);   \
        (op) = (op2);                           \
        Py_DECREF(_py_tmp);                     \
    } while (0)
    //循环的为一个对象减少引用计数一直减少到 0 并 把 op 指向 op2 
```

从上面的处理步骤我们发现 即使 Python 要对一个字符串 进行 intern 处理,也会创建这个 PyUnicodeObject 对象.具体要不要保存这个对象就要看 interned 这个 dict 有没有这个对象的 key 了.

![](https://copie.cn/usr/uploads/2018/05/3982923230.png)

## 字符缓存池

Python3 的 PyUnicodeObject 有一个字符串缓存池:

```C
/* Single character Unicode strings in the Latin-1 range are being
   shared as well. */
static PyObject *unicode_latin1[256] = {NULL};
```

这个数组只有创建单个字符对象的时候才会启用
```C
static PyObject*
get_latin1_char(unsigned char ch)
{
    PyObject *unicode = unicode_latin1[ch];
    if (!unicode) {
        // 如果不存在
        unicode = PyUnicode_New(1, ch);
        // 创建一个对象
        if (!unicode)
            return NULL;
        PyUnicode_1BYTE_DATA(unicode)[0] = ch;
        assert(_PyUnicode_CheckConsistency(unicode, 1));
        unicode_latin1[ch] = unicode;
        // 放到unicode_latin1里面
    }
    Py_INCREF(unicode);
    // 引用计数 +1
    return unicode;
}
```
