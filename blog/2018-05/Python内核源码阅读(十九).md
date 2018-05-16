## Python内核源码阅读(十九)

Python 的字节码和汇编代码差不多, 这些指令需要 Python 虚拟机接手整个工作, Python 虚拟机会从编译得到的 PyCodeObject 对象中依次读入每一条字节码指令, 并在当前上下文环境中执行.

## PyFrameObject
在 Python 中 PyFrameObject 对象就是我们说的执行环境, 也是 Python 虚拟机模拟cpu的运行模式--栈帧

```Python
typedef struct _frame {
    PyObject_VAR_HEAD
    struct _frame *f_back;      // 执行环境链的上一个frame
    PyCodeObject *f_code;       // PyCodeObject对象
    PyObject *f_builtins;       // builtin名字空间
    PyObject *f_globals;        // global 名字空间
    PyObject *f_locals;         // local 名字空间
    PyObject **f_valuestack;    // 运行栈的栈底
    /* Next free slot in f_valuestack.  Frame creation sets to f_valuestack.
       Frame evaluation usually NULLs it, but a frame that yields sets it
       to the current stack top. */
    PyObject **f_stacktop;      // 运行栈的栈顶
    PyObject *f_trace;          // 异常时调用的句柄
    char f_trace_lines;         /* Emit per-line trace events? */
    char f_trace_opcodes;       /* Emit per-opcode trace events? */

    /* Borrowed reference to a generator, or NULL */
    PyObject *f_gen;

    int f_lasti;               // 上一条字节码指令在f_code中的偏移位置
    /* Call PyFrame_GetLineNumber() instead of reading this field
       directly.  As of 2.3 f_lineno is only valid when tracing is
       active (i.e. when f_trace is set).  At other times we use
       PyCode_Addr2Line to calculate the line from the current
       bytecode index. */
    int f_lineno;               // 当前字节码对应的源代码行
    int f_iblock;               // 当前指令在栈f_blockstack中的索引
    char f_executing;           /* whether the frame is still executing */
    PyTryBlock f_blockstack[CO_MAXBLOCKS]; /* for try and loop blocks */
    PyObject *f_localsplus[1]; // locals+stack, 动态内存, 维护(局部变量+运行时栈)所需要的空间 */
} PyFrameObject;
```
栈帧通过 f_back 将对象形成一条执行环境链表.这就类似 X86 系统上栈帧间通过 esp 和 ebp 指针建立关系, 使新的栈帧在结束后可以顺利的回到旧的栈帧中. f_code 存放的是一个待执行的 PyCodeObject 对象, 而接下来的 f_builtins , f_globals 和 f_locals 是三个独立的名字空间, 关系到维护着变量名和变量值之间的关系,他们本身是 PyDictObject 对象.

PyFrameObject 对象也是一个变长对象, 每次创建 PyFrameObject 对象的大小可能是不一样的(体现在  PyObject *f_localsplus[1];)

## 栈帧的创建

```C
PyFrameObject*
PyFrame_New(PyThreadState *tstate, PyCodeObject *code,
            PyObject *globals, PyObject *locals)
{
    PyFrameObject *f = _PyFrame_New_NoTrack(tstate, code, globals, locals);
    if (f)
        _PyObject_GC_TRACK(f);
    return f;
}
```
```C

PyFrameObject* _Py_HOT_FUNCTION
_PyFrame_New_NoTrack(PyThreadState *tstate, PyCodeObject *code,
                     PyObject *globals, PyObject *locals)
{
    PyFrameObject *back = tstate->frame;
    PyFrameObject *f;
    PyObject *builtins;
    Py_ssize_t i;
    ....
    if (code->co_zombieframe != NULL) {
        ....
    }
    else {
        Py_ssize_t extras, ncells, nfrees;
        ncells = PyTuple_GET_SIZE(code->co_cellvars);
        nfrees = PyTuple_GET_SIZE(code->co_freevars);
        // 四部分构成了 PyFrameObject维护的动态内存区
        // code->co_nlocals(Code Block 中局部变量的个数)
        // PyTuple_GET_SIZE(code->co_cellvars) (Code Block 中嵌套函数所引用的局部变量名集合)
        // PyTuple_GET_SIZE(code->co_freevars) (Code Block 中自由变量名集合)
        // code->co_stacksize 
        extras = code->co_stacksize + code->co_nlocals + ncells +
            nfrees;
        if (free_list == NULL) {
            f = PyObject_GC_NewVar(PyFrameObject, &PyFrame_Type,
            extras);
            if (f == NULL) {
                Py_DECREF(builtins);
                return NULL;
            }
        }
        else {
            assert(numfree > 0);
            --numfree;
            f = free_list;
            free_list = free_list->f_back;
            if (Py_SIZE(f) < extras) {
                PyFrameObject *new_f = PyObject_GC_Resize(PyFrameObject, f, extras);
                if (new_f == NULL) {
                    PyObject_GC_Del(f);
                    Py_DECREF(builtins);
                    return NULL;
                }
                f = new_f;
            }
            _Py_NewReference((PyObject *)f);
        }

        f->f_code = code;
        extras = code->co_nlocals + ncells + nfrees;
        f->f_valuestack = f->f_localsplus + extras;   // 运行时的栈底
        for (i=0; i<extras; i++)
            f->f_localsplus[i] = NULL;
        f->f_locals = NULL;
        f->f_trace = NULL;
    }
    // f_stacktop维护 "运行时栈" 的栈顶,当前指向栈底位置.
    f->f_stacktop = f->f_valuestack;
    f->f_builtins = builtins;
    Py_XINCREF(back);
    f->f_back = back;
    Py_INCREF(code);
    Py_INCREF(globals);
    f->f_globals = globals;
    /* Most functions have CO_NEWLOCALS and CO_OPTIMIZED set. */
    if ((code->co_flags & (CO_NEWLOCALS | CO_OPTIMIZED)) ==
        (CO_NEWLOCALS | CO_OPTIMIZED))
        ; /* f_locals = NULL; will be set by PyFrame_FastToLocals() */
    else if (code->co_flags & CO_NEWLOCALS) {
        locals = PyDict_New();
        if (locals == NULL) {
            Py_DECREF(f);
            return NULL;
        }
        f->f_locals = locals;
    }
    else {
        if (locals == NULL)
            locals = globals;
        Py_INCREF(locals);
        f->f_locals = locals;
    }

    f->f_lasti = -1;
    f->f_lineno = code->co_firstlineno;
    f->f_iblock = 0;
    f->f_executing = 0;
    f->f_gen = NULL;
    f->f_trace_opcodes = 0;
    f->f_trace_lines = 1;

    return f;
}
```
