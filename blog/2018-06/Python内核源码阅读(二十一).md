# Python内核源码阅读(二十一)

## 内建对象的创建

```
In [2]: dis("a = 1")
  1           0 LOAD_CONST               0 (1)
              2 STORE_NAME               0 (a)
              4 LOAD_CONST               1 (None)
              6 RETURN_VALUE
```

```C
TARGET(LOAD_CONST) {
    PyObject *value = GETITEM(consts, oparg);
    Py_INCREF(value);
    PUSH(value);
    FAST_DISPATCH();
}
```
我们可以看到所谓的 LOAD_CONST, 字节码指令就是从 f->f_code->co_consts 中获取 oparg 位置的数,然后按照这个数的类型的对象,创建这个对象,然后对这个对象进行引用计数 +1.

```C
TARGET(STORE_NAME) {
    PyObject *name = GETITEM(names, oparg); // 获取 f->f_code->co_names 中对应 oparg 位置的字符串,创建 PyUnicodeObject 后返回 
    PyObject *v = POP(); // 获取栈顶的元素
    PyObject *ns = f->f_locals; // 获取保存局部变量的 PyDictObject 对象指针
    int err;
    if (ns == NULL) {
        PyErr_Format(PyExc_SystemError,
                        "no locals found when storing %R", name);
        Py_DECREF(v);
        goto error;
    }
    if (PyDict_CheckExact(ns))
        err = PyDict_SetItem(ns, name, v); // 将 name:v 插入 f->f_locals
    else
        err = PyObject_SetItem(ns, name, v);
    Py_DECREF(v);
    if (err != 0)
        goto error;
    DISPATCH();
}
```

```
In [4]: dis("x = {a:2,b:4}")
  1           0 LOAD_NAME                0 (a)
              2 LOAD_CONST               0 (2)
              4 LOAD_NAME                1 (b)
              6 LOAD_CONST               1 (4)
              8 BUILD_MAP                2
             10 STORE_NAME               2 (x)
             12 LOAD_CONST               2 (None)
             14 RETURN_VALUE
```

```C
TARGET(BUILD_MAP) {
    Py_ssize_t i;
    PyObject *map = _PyDict_NewPresized((Py_ssize_t)oparg); // 获取一个 能存 oparg 大小的 PyDictObject,这之间的获取也是比较复杂的
    if (map == NULL)
        goto error;
    for (i = oparg; i > 0; i--) {
        int err;
        PyObject *key = PEEK(2*i);
        PyObject *value = PEEK(2*i - 1); // 由于我们是先将 a 和 2 压入栈的,所以如果我们想要 a 优先与 b 插入栈,这里就是一点小手段
        err = PyDict_SetItem(map, key, value);
        if (err != 0) {
            Py_DECREF(map);
            goto error;
        }
    }

    while (oparg--) {
        Py_DECREF(POP());
        Py_DECREF(POP());
    }
    PUSH(map);
    DISPATCH();
}
```
为了优化创建 dict 其实 Python 还有
```C
In [3]: dis("x = {1:2,3:4}")
  1           0 LOAD_CONST               0 (2)
              2 LOAD_CONST               1 (4)
              4 LOAD_CONST               2 ((1, 3))
              6 BUILD_CONST_KEY_MAP      2
              8 STORE_NAME               0 (x)
             10 LOAD_CONST               3 (None)
             12 RETURN_VALUE
```
这里就是一些细节问题了不深入考虑.

```
In [5]: dis("x = [1,2,3,4,5,6]")
  1           0 LOAD_CONST               0 (1)
              2 LOAD_CONST               1 (2)
              4 LOAD_CONST               2 (3)
              6 LOAD_CONST               3 (4)
              8 LOAD_CONST               4 (5)
             10 LOAD_CONST               5 (6)
             12 BUILD_LIST               6
             14 STORE_NAME               0 (x)
             16 LOAD_CONST               6 (None)
             18 RETURN_VALUE
```

```C
TARGET(BUILD_LIST) {
    PyObject *list =  PyList_New(oparg);
    if (list == NULL)
        goto error;
    while (--oparg >= 0) {
        PyObject *item = POP();
        PyList_SET_ITEM(list, oparg, item);
    }
    PUSH(list);
    DISPATCH();
}
```
```C
TARGET(RETURN_VALUE) {
    retval = POP();
    assert(f->f_iblock == 0);
    goto return_or_yield;   // 这要跳转应该就是我们之前说的删除 why_code 的替代处理
}
```
```C
return_or_yield:
    if (tstate->use_tracing) {
        if (tstate->c_tracefunc) {
            if (call_trace_protected(tstate->c_tracefunc, tstate->c_traceobj,
                                     tstate, f, PyTrace_RETURN, retval)) {
                Py_CLEAR(retval);
            }
        }
        if (tstate->c_profilefunc) {
            if (call_trace_protected(tstate->c_profilefunc, tstate->c_profileobj,
                                     tstate, f, PyTrace_RETURN, retval)) {
                Py_CLEAR(retval);
            }
        }
    }// 这里我看不太懂大概就是返回值的一些处理
```

## 其他一般表达式

### 符号搜索
```
In [5]: dis("a = b")
  1           0 LOAD_NAME                0 (b)
              2 STORE_NAME               1 (a)
              4 LOAD_CONST               0 (None)
              6 RETURN_VALUE
```

```C
TARGET(LOAD_NAME) {
    PyObject *name = GETITEM(names, oparg); // 获取 f->f_code->co_names 中对应 oparg 位置的字符串,创建 PyUnicodeObject 后返回
    PyObject *locals = f->f_locals;
    PyObject *v;
    if (locals == NULL) {
        PyErr_Format(PyExc_SystemError,
                        "no locals when loading %R", name);
        goto error;
    }
    if (PyDict_CheckExact(locals)) {
        v = PyDict_GetItem(locals, name); // 尝试从局部变量中获取
        Py_XINCREF(v);
    }
    else {
        v = PyObject_GetItem(locals, name); // 这里我记得插入的时候有一句和他对应但是不知道他是干嘛的.
        if (v == NULL) {
            if (!PyErr_ExceptionMatches(PyExc_KeyError))
                goto error;
            PyErr_Clear();
        }
    }
    if (v == NULL) {
        v = PyDict_GetItem(f->f_globals, name); // 尝试从全局变量中获取
        Py_XINCREF(v);
        if (v == NULL) {
            if (PyDict_CheckExact(f->f_builtins)) {
                v = PyDict_GetItem(f->f_builtins, name); // 尝试从 builtins 获取 
                if (v == NULL) {
                    format_exc_check_arg(
                                PyExc_NameError,
                                NAME_ERROR_MSG, name);
                    goto error;
                }
                Py_INCREF(v);
            }
            else {
                v = PyObject_GetItem(f->f_builtins, name);
                if (v == NULL) {
                    if (PyErr_ExceptionMatches(PyExc_KeyError))
                        format_exc_check_arg(
                                    PyExc_NameError,
                                    NAME_ERROR_MSG, name);
                    goto error;
                }
            }
        }
    }
    PUSH(v);
    DISPATCH();
}
```
所以我们看到变量的搜索顺序是LGB,说好的 LEGB 呢,闭包为什么没有找(其实我也不知道,我想以后分析函数那部分就可以知道了)

### 数值运算
```
In [6]: dis("a = b + c")
  1           0 LOAD_NAME                0 (b)
              2 LOAD_NAME                1 (c)
              4 BINARY_ADD
              6 STORE_NAME               2 (a)
              8 LOAD_CONST               0 (None)
             10 RETURN_VALUE
```
```C
    TARGET(BINARY_ADD) {
        PyObject *right = POP();
        PyObject *left = TOP();
        PyObject *sum;
        /* NOTE(haypo): Please don't try to micro-optimize int+int on
            CPython using bytecode, it is simply worthless.
            See http://bugs.python.org/issue21955 and
            http://bugs.python.org/issue10044 for the discussion. In short,
            no patch shown any impact on a realistic benchmark, only a minor
            speedup on microbenchmarks. */
        if (PyUnicode_CheckExact(left) &&
                    PyUnicode_CheckExact(right)) { // 如果两个都是字符串的话直接连接起来
            sum = unicode_concatenate(left, right, f, next_instr);
            /* unicode_concatenate consumed the ref to left */
        }
        else {
            sum = PyNumber_Add(left, right); // 使用慢速通道加法
            Py_DECREF(left);
        }
        Py_DECREF(right);
        SET_TOP(sum);
        if (sum == NULL)
            goto error;
        DISPATCH();
    }
```
PyNumber_Add 会首先尝试 nb_add,然后尝试 sq_concat,实在不行就报错.