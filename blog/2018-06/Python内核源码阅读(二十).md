# Python内核源码阅读(二十)

## Python 虚拟机的运行框架

Python启动后,首先会进行 Python 运行环境的初始化.运行环境和执行环境不同,运行环境是一个全局的概念,而执行环境是一个栈帧,栈帧和 CodeBlock 对应.待初始化完成后,运行的过程就像多米诺骨牌一样,一环一环地展开.

现在假设运行时初始化已经完成,推动第一个骨牌的函数就是 PyEval_EvalFrameEx.

```C
PyObject *
PyEval_EvalFrameEx(PyFrameObject *f, int throwflag)
{
    PyThreadState *tstate = PyThreadState_GET();
    return tstate->interp->eval_frame(f, throwflag);
}
```
我们这里可以看到 interp->eval_frame 的默认值是 _PyEval_EvalFrameDefault
```C
PyInterpreterState *
PyInterpreterState_New(void)
{
    PyInterpreterState *interp = (PyInterpreterState *)
                                 PyMem_RawMalloc(sizeof(PyInterpreterState));
    .
    .
    .
    interp->eval_frame = _PyEval_EvalFrameDefault;
    .
    .
    .
    return interp;
}
```

```C
PyObject* _Py_HOT_FUNCTION
_PyEval_EvalFrameDefault(PyFrameObject *f, int throwflag)
{
    ......
    co = f->f_code;
    names = co->co_names;
    consts = co->co_consts;
    fastlocals = f->f_localsplus;
    freevars = f->f_localsplus + co->co_nlocals;
    .......
    first_instr = (_Py_CODEUNIT *) PyBytes_AS_STRING(co->co_code);
    next_instr = first_instr;
    f->f_stacktop = NULL;       /* remains NULL unless yield suspends frame */
    f->f_executing = 1;
    ......
}
```
我们知道在 PyCodeObject 对象的 co_code 域中保存这字节码指令和字节码指令参数, Python 在执行字节码指令的过程中就是从头到尾遍历整个 co_code,以此执行字节码指令.

+ first_instr 永远指向字节码指令的开始位置
+ next_instr 永远指向下一条待执行的指令字节码所在的位置
+ f_lasti 指向上一条已经执行过的字节码指令位置

运行的框架就是一个 for 循环加上一个巨大的 switch/case 结构.

```C
for (;;) {
    _Py_CODEUNIT word = *next_instr;
    opcode = _Py_OPCODE(word);
    oparg = _Py_OPARG(word);
    next_instr++;

    switch (opcode) {
        ...
    }
}
```
由于我阅读的代码是 Python3.8 在 520b7ae27e39d1c77ea74ccd1b184d7cb43f9dcb 这个提交的时候 已经删除了 why_code ,大概的意思就是因为把原来的 伪异常处理变为编译器内部处理,这样的话可以提高 1.5% 的速度.有兴趣的可以看[Move unwinding of stack for "pseudo exceptions" from interpreter to compiler.](https://bugs.python.org/issue17611)和[bpo-17611. Move unwinding of stack for "pseudo exceptions" from interpreter to compiler. #5006](https://github.com/.python/cpython/pull/5006)
它这样一改我就有点看不懂了,以后看大牛的解释了.

## Python 运行时环境初探

```C
typedef struct _is {

    struct _is *next;// 显然这个指示的就是下一个模拟进程
    struct _ts *tstate_head;  // 这个应该就是模拟进程中的线程集合

    int64_t id;
    int64_t id_refcount;
    PyThread_type_lock id_mutex;

    PyObject *modules;
    PyObject *modules_by_index;
    PyObject *sysdict;
    PyObject *builtins;
    PyObject *importlib;

    /* Used in Python/sysmodule.c. */
    int check_interval;

    /* Used in Modules/_threadmodule.c. */
    long num_threads;
    /* Support for runtime thread stack size tuning.
       A value of 0 means using the platform's default stack size
       or the size specified by the THREAD_STACK_SIZE macro. */
    /* Used in Python/thread.c. */
    size_t pythread_stacksize;

    PyObject *codec_search_path;
    PyObject *codec_search_cache;
    PyObject *codec_error_registry;
    int codecs_initialized;
    int fscodec_initialized;

    _PyCoreConfig core_config;
    _PyMainInterpreterConfig config;
#ifdef HAVE_DLOPEN
    int dlopenflags;
#endif

    PyObject *builtins_copy;
    PyObject *import_func;
    /* Initialized to PyEval_EvalFrameDefault(). */
    _PyFrameEvalFunction eval_frame;

    Py_ssize_t co_extra_user_count;
    freefunc co_extra_freefuncs[MAX_CO_EXTRA_USERS];

#ifdef HAVE_FORK
    PyObject *before_forkers;
    PyObject *after_forkers_parent;
    PyObject *after_forkers_child;
#endif
    /* AtExit module */
    void (*pyexitfunc)(PyObject *);
    PyObject *pyexitmodule;

    uint64_t tstate_next_unique_id;
} PyInterpreterState;
```
```C
typedef struct _ts {
    /* See Python/ceval.c for comments explaining most fields */

    struct _ts *prev;
    struct _ts *next;   // 模拟线程集合是一个双向的链表
    PyInterpreterState *interp;  // 所属的模拟进程.

    struct _frame *frame;        // 模拟线程的调用堆栈
    int recursion_depth;
    char overflowed; /* The stack has overflowed. Allow 50 more calls
                        to handle the runtime error. */
    char recursion_critical; /* The current calls must not cause
                                a stack overflow. */
    int stackcheck_counter;

    /* 'tracing' keeps track of the execution depth when tracing/profiling.
       This is to prevent the actual trace/profile code from being recorded in
       the trace/profile. */
    int tracing;
    int use_tracing;

    Py_tracefunc c_profilefunc;
    Py_tracefunc c_tracefunc;
    PyObject *c_profileobj;
    PyObject *c_traceobj;

    /* The exception currently being raised */
    PyObject *curexc_type;
    PyObject *curexc_value;
    PyObject *curexc_traceback;

    /* The exception currently being handled, if no coroutines/generators
     * are present. Always last element on the stack referred to be exc_info.
     */
    _PyErr_StackItem exc_state;

    /* Pointer to the top of the stack of the exceptions currently
     * being handled */
    _PyErr_StackItem *exc_info;

    PyObject *dict;  /* Stores per-thread state */

    int gilstate_counter;

    PyObject *async_exc; /* Asynchronous exception to raise */
    unsigned long thread_id; /* Thread id where this tstate was created */

    int trash_delete_nesting;
    PyObject *trash_delete_later;

    /* Called when a thread state is deleted normally, but not when it
     * is destroyed after fork().
     * Pain:  to prevent rare but fatal shutdown errors (issue 18808),
     * Thread.join() must wait for the join'ed thread's tstate to be unlinked
     * from the tstate chain.  That happens at the end of a thread's life,
     * in pystate.c.
     * The obvious way doesn't quite work:  create a lock which the tstate
     * unlinking code releases, and have Thread.join() wait to acquire that
     * lock.  The problem is that we _are_ at the end of the thread's life:
     * if the thread holds the last reference to the lock, decref'ing the
     * lock will delete the lock, and that may trigger arbitrary Python code
     * if there's a weakref, with a callback, to the lock.  But by this time
     * _PyThreadState_Current is already NULL, so only the simplest of C code
     * can be allowed to run (in particular it must not be possible to
     * release the GIL).
     * So instead of holding the lock directly, the tstate holds a weakref to
     * the lock:  that's the value of on_delete_data below.  Decref'ing a
     * weakref is harmless.
     * on_delete points to _threadmodule.c's static release_sentinel() function.
     * After the tstate is unlinked, release_sentinel is called with the
     * weakref-to-lock (on_delete_data) argument, and release_sentinel releases
     * the indirectly held lock.
     */
    void (*on_delete)(void *);
    void *on_delete_data;

    int coroutine_origin_tracking_depth;

    PyObject *coroutine_wrapper;
    int in_coroutine_wrapper;

    PyObject *async_gen_firstiter;
    PyObject *async_gen_finalizer;

    PyObject *context;
    uint64_t context_ver;

    /* Unique thread state id. */
    uint64_t id;

    /* XXX signal handlers should also be here */

} PyThreadState;
```
看完模拟线程和模拟进程,再去看最前面的两个代码段就很好理解了,现在我们差不多已经可以画出 Python 运行环境图了
![Python运行时环境](https://copie.cn/usr/uploads/2018/06/3309775948.png)