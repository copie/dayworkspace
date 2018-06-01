# Python内核源码阅读(十九)

## PyFrameObject

```C
typedef struct _frame {
    PyObject_VAR_HEAD
    struct _frame *f_back;      /* previous frame, or NULL */                   // 执行链上的前一个 frame
    PyCodeObject *f_code;       /* code segment */                              // PyCodeObject 对象
    PyObject *f_builtins;       /* builtin symbol table (PyDictObject) */       // builtin 名字空间
    PyObject *f_globals;        /* global symbol table (PyDictObject) */        // global 名字空间
    PyObject *f_locals;         /* local symbol table (any mapping) */          // local 名字空间
    PyObject **f_valuestack;    /* points after the last local */               // 运行时栈的栈底
    /* Next free slot in f_valuestack.  Frame creation sets to f_valuestack.
       Frame evaluation usually NULLs it, but a frame that yields sets it
       to the current stack top. */
    PyObject **f_stacktop;                                                      // 运行时栈的栈顶位置
    PyObject *f_trace;          /* Trace function */
    char f_trace_lines;         /* Emit per-line trace events? */
    char f_trace_opcodes;       /* Emit per-opcode trace events? */

    /* Borrowed reference to a generator, or NULL */
    PyObject *f_gen;

    int f_lasti;                /* Last instruction if called */                // 上一条字节码指令在 f_code 中的偏移位置
    /* Call PyFrame_GetLineNumber() instead of reading this field
       directly.  As of 2.3 f_lineno is only valid when tracing is
       active (i.e. when f_trace is set).  At other times we use
       PyCode_Addr2Line to calculate the line from the current
       bytecode index. */
    int f_lineno;               /* Current line number */                       // 当前字节码对应源码位置
    int f_iblock;               /* index in f_blockstack */
    char f_executing;           /* whether the frame is still executing */
    PyTryBlock f_blockstack[CO_MAXBLOCKS]; /* for try and loop blocks */
    PyObject *f_localsplus[1];  /* locals+stack, dynamically sized */           // 动态内存,维护局部变量+cell对象集合
                                                                                // +free 对象集合 + 运行时栈
                                                                                // 因为这里所以使用 PyObject_VAR_HEAD
} PyFrameObject;
```

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

#ifdef Py_DEBUG
    if (code == NULL || globals == NULL || !PyDict_Check(globals) ||
        (locals != NULL && !PyMapping_Check(locals))) {
        PyErr_BadInternalCall();
        return NULL;
    }
#endif
    if (back == NULL || back->f_globals != globals) {
        builtins = _PyDict_GetItemId(globals, &PyId___builtins__);
        if (builtins) {
            if (PyModule_Check(builtins)) {
                builtins = PyModule_GetDict(builtins);
                assert(builtins != NULL);
            }
        }
        if (builtins == NULL) {
            /* No builtins!              Make up a minimal one
               Give them 'None', at least. */
            builtins = PyDict_New();
            if (builtins == NULL ||
                PyDict_SetItemString(
                    builtins, "None", Py_None) < 0)
                return NULL;
        }
        else
            Py_INCREF(builtins);

    }
    else {
        /* If we share the globals, we share the builtins.
           Save a lookup and a call. */
        builtins = back->f_builtins;
        assert(builtins != NULL);
        Py_INCREF(builtins);
    }
    if (code->co_zombieframe != NULL) {
        f = code->co_zombieframe;
        code->co_zombieframe = NULL;
        _Py_NewReference((PyObject *)f);
        assert(f->f_code == code);
    }
    else {
        Py_ssize_t extras, ncells, nfrees;
        ncells = PyTuple_GET_SIZE(code->co_cellvars);   // Code Block 中嵌套函数所引用的局部变量名集合
        nfrees = PyTuple_GET_SIZE(code->co_freevars);   // Code Block 中的自由变量名集合(与闭包有关)
                                                        // co_nlocals	Code Block 局部变量的个数
                                                        // co_stacksize	执行该段 Code Block 需要的栈空间
        extras = code->co_stacksize + code->co_nlocals + ncells +           
            nfrees;               // extras 就是动态区域的大小
        if (free_list == NULL) { // 这里可以看到缓存机制
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
                PyFrameObject *new_f = PyObject_GC_Resize(PyFrameObject, f, extras);   // 重用缓存的 PyFrameObject 并修改 f_localsplus 的大小为 extras
                if (new_f == NULL) {
                    PyObject_GC_Del(f);
                    Py_DECREF(builtins);
                    return NULL;
                }
                f = new_f;
            }
            _Py_NewReference((PyObject *)f);
        }
        // 以下的代码就是初始化 PyFrameObject
        f->f_code = code;
        extras = code->co_nlocals + ncells + nfrees;
        // 我们知道 f_valuestack 是运行时栈的栈底,他的计算方式就是 f_localsplus 加上一个偏移
        f->f_valuestack = f->f_localsplus + extras;
        for (i=0; i<extras; i++)
            f->f_localsplus[i] = NULL;
        f->f_locals = NULL;
        f->f_trace = NULL;
    }
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

通过上面我们已经可以看到一个 PyFrameObject 在内存中的分布了


![内存分布](https://copie.cn/usr/uploads/2018/06/587616470.png)

这里 extras = code->co_nlocals + ncells + nfrees 以后我们再讨论符合把实际的东西放进去

## Python 中访问 PyFrameObject 对象

```Python
import sys

value = 3

def g():
    frame = sys._getframe()
    print(f"函数名: {frame.f_code.co_name}")
    caller = frame.f_back
    print(f"调用的函数名是: {caller.f_code.co_name}")
    print(f"调用的函数的 local 名字空间: {caller.f_locals}")
    print(f"调用的函数的 global 名字空间: {caller.f_globals.keys()}")

def f():
    a = 1
    b = 2
    g()

def show():
    f()

show()
```
```
函数名: g
调用的函数名是: f
调用的函数的 local 名字空间: {'b': 2, 'a': 1}
调用的函数的 global 名字空间: dict_keys(['__name__', '__doc__', '__package__', '__loader__', '__spec__', '__annotations__', '__builtins__', '__file__', '__cached__', 'sys', 'value', 'g', 'f', 'show'])
```