# Python内核源码阅读(十一)

## PyListObject 的定义

```C
typedef struct {
    PyObject_VAR_HEAD
    /* Vector of pointers to list elements.  list[0] is ob_item[0], etc. */
    // ob_item 指向 list 的首地址 list[0] == ob_item[0]
    PyObject **ob_item;

    /* ob_item contains space for 'allocated' elements.  The number
     * currently in use is ob_size.
     * Invariants:
     *     0 <= ob_size <= allocated
     *     len(list) == ob_size
     *     ob_item == NULL implies ob_size == allocated == 0
     * list.sort() temporarily sets allocated to -1 to detect mutations.
     *
     * Items must normally not be NULL, except during construction when
     * the list is not yet visible outside the function that builds it.
     */
    // PyObject_VAR_HEAD 中的 ob_size 是列表的长度
    // allocated 维护了当前列表可容纳的元素多少,已申请的空间大小,如果空间不够用会重新调整内存
    // 满足以下条件
    // 0 <= ob_size <= allocated
    // len(list) == ob_size
    // ob_item == NULL implies ob_size == allocated == 0
    Py_ssize_t allocated;
} PyListObject;
```

## 创建 PyListObject 对象

创建列表只能通过 PyList_New 函数来创建, 该函数接受一个size参数,意味着列表初始化可容纳元素的个数.

```C
PyObject *
PyList_New(Py_ssize_t size)
{
    PyListObject *op;
#ifdef SHOW_ALLOC_COUNT
    static int initialized = 0;
    if (!initialized) {
        Py_AtExit(show_alloc);
        initialized = 1;
    }
#endif

    if (size < 0) {
        PyErr_BadInternalCall();
        return NULL;
    }
    // list 对象缓存池是否可用
    if (numfree) {
        numfree--;
        op = free_list[numfree];
        _Py_NewReference((PyObject *)op);
#ifdef SHOW_ALLOC_COUNT
        count_reuse++;
#endif
    } else {
        // 申请内存创建 PyListObject
        op = PyObject_GC_New(PyListObject, &PyList_Type);
        if (op == NULL)
            return NULL;
#ifdef SHOW_ALLOC_COUNT
        count_alloc++;
#endif
    }
    if (size <= 0)
        op->ob_item = NULL;
    else {
        // 申请数据空间
        op->ob_item = (PyObject **) PyMem_Calloc(size, sizeof(PyObject *));
        if (op->ob_item == NULL) {
            Py_DECREF(op);
            return PyErr_NoMemory();
        }
    }
    Py_SIZE(op) = size;
    op->allocated = size;
    _PyObject_GC_TRACK(op);
    return (PyObject *) op;
}
```
定义在 Include/objimpl.h 的 PyObject_GC_New 实际上是 gc 模块 Modules/gcmodule.c 里面的一个函数_PyObject_GC_New。除了申请内存之外，还会为 Pytho n中的自动垃圾收集机制做一些准备工作。

```C
/* Empty list reuse scheme to save calls to malloc and free */
#ifndef PyList_MAXFREELIST
#define PyList_MAXFREELIST 80
#endif
static PyListObject *free_list[PyList_MAXFREELIST];
static int numfree = 0;
```
如果 numfree 不为 0, 则会从对象池 free_list 中获取可用的 PyListObject 对象, 对象池 free_list 中默认最多维护 80 个 PyListObject 对象:

但是我们看这里的定义是 numfree = 0, 因为在 一个 PylistObject 对象被销毁时尝试着添加.

```C
static void
list_dealloc(PyListObject *op)
{
    Py_ssize_t i;
    PyObject_GC_UnTrack(op);
    Py_TRASHCAN_SAFE_BEGIN(op)
    if (op->ob_item != NULL) {
        /* Do it backwards, for Christian Tismer.
           There's a simple test case where somehow this reduces
           thrashing when a *very* large list is created and
           immediately deleted. */
        i = Py_SIZE(op);
        // 为列表中存储的对象 进行 引用计数 -1
        while (--i >= 0) {
            Py_XDECREF(op->ob_item[i]);
        }
        // 释放 ob_item
        PyMem_FREE(op->ob_item);
    }
    // 如果该对象 是 list 并且 list 缓存有足够的空间
    if (numfree < PyList_MAXFREELIST && PyList_CheckExact(op))
        // 放入缓存池
        free_list[numfree++] = op;
    else
        // 释放
        Py_TYPE(op)->tp_free((PyObject *)op);
    Py_TRASHCAN_SAFE_END(op)
}
```