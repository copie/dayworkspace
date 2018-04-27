# Python 内核源码阅读(二) -- 对象的机制的基石-PyObject

## 整体架构 

Python 整体架构可分为3个部分,内建模块, Python 内核,Python 虚拟机.
内建模块就诸如 import os 时,这个 os 就是 Python 的内建模块.Python 内核就包括定义Python 的对象/类型系统,处理垃圾回收机制等,虚拟机就是解释器,对Python 代码进行词法语法分析等.

## PyObject 

都知道在 Python 中万物皆对象 PyObject 就是处理这个的.

    [onject.h]
    typedef struct _object {
        _PyObject_HEAD_EXTRA
        Py_ssize_t ob_refcnt;
        struct _typeobject *ob_type;
    } PyObject;

我们先看第一个定义  _PyObject_HEAD_EXTRA 

    [onject.h]
    #ifdef Py_TRACE_REFS
    /* Define pointers to support a doubly-linked list of all live heap objects. */
    #define _PyObject_HEAD_EXTRA            \
        struct _object *_ob_next;           \
        struct _object *_ob_prev;

    #define _PyObject_EXTRA_INIT 0, 0,

    #else
    #define _PyObject_HEAD_EXTRA
    #define _PyObject_EXTRA_INIT
    #endif

从注释不难看出这是建立了一个双向链表,其中包括所有在堆栈上活动的对象

我们再看 Py_TRACE_REFS

    [onject.h]
    /* Py_DEBUG implies Py_TRACE_REFS. */
    #if defined(Py_DEBUG) && !defined(Py_TRACE_REFS)
    #define Py_TRACE_REFS
    #endif

注释说只有在 Python Debug 模式下才会定义这个宏,到此 PyObject 的第一句已经搞明白了.

下面我们接着看 Py_ssize_t

    [pyport.h]
    /* Py_ssize_t is a signed integral type such that sizeof(Py_ssize_t) ==
    * sizeof(size_t).  C99 doesn't define such a thing directly (size_t is an
    * unsigned integral type).  See PEP 353 for details.
    */
    #ifdef HAVE_SSIZE_T
    typedef ssize_t         Py_ssize_t;
    #elif SIZEOF_VOID_P == SIZEOF_SIZE_T
    typedef Py_intptr_t     Py_ssize_t;
    #else
    #   error "Python needs a typedef for Py_ssize_t in pyport.h."
    #endif

注释说的很明白 Py_ssize_t 是一个有符号的整型, 我们追着 ssize_t 看看他到底是什么

    [pyconfig.h]
    /* Define like size_t, omitting the "unsigned" */
    #ifdef MS_WIN64
    typedef __int64 ssize_t;
    #else
    typedef _W64 int ssize_t;
    #endif

到这里我们也明白了 Py_ssize_t 是 __int64 或者 _W64 两种C类型 其范围是 [-2^63, 2^63) 我们这里可以把他看做 int
所以 PyObject 其实是下面这个模样


    typedef struct _object {
        int ob_refcnt;
        struct _typeobject *ob_type;
    } PyObject;

## ob_refcnt 和 *ob_typ 作用

**ob_refcnt** 与 Python 内存管理机制有关,它实现了基于引用计数的垃圾收集机制.当某个对象的引用计数减少到 0 时 A **就可以**从堆上删除,以释放内存供别的对象使用. 

**ob_type** 它是用来指定一个对象类型的类型对象.

因此 PyObject 这个结构体定义了两个内容:一个是引用计数,一个是类型信息.但是当有一个 int 数 300 他的一个引用是 a 那么 存放 300 的那么个结构体, 他的ob_refcnt 就是 1 (不要问我为什么选300,我现在不想讨论小整数的问题所以选了300),而 ob_type 就是 int. 这样看这个变量我们保存的信息太少了,让我们看看其他的信息保存在什么地方.(以 PyLongObject 为例)


    [longobject.h]
    /* Long (arbitrary precision) integer object interface */

    typedef struct _longobject PyLongObject; /* Revealed in longintrepr.h */   


    [longintrepr.h]

    struct _longobject {
        PyObject_VAR_HEAD
        digit ob_digit[1];
    };

从这里我们可以看出在 Python3 中 int 是任意大小的一个数,没有了 python2 中先判断 long 如果溢出就走慢速通道了.

总结一下 PyObject 保存了在 Python3 中所有对象的公共部分.

