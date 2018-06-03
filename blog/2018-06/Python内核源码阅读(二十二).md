# Python内核源码阅读(二十二)

## Python 虚拟机中的 if 控制流

```Python
a = 1
if a > 10:
    print("a > 10")
elif a < -2:
    print("a < -2")
elif a == 1:
    print("a == 1")
else:
    print("unkonwn")
```
```
In [12]: dis(open("1.py").read())
  1           0 LOAD_CONST               0 (1)
              2 STORE_NAME               0 (a)

  2           4 LOAD_NAME                0 (a)
              6 LOAD_CONST               1 (10)
              8 COMPARE_OP               4 (>)
             10 POP_JUMP_IF_FALSE       22

  3          12 LOAD_NAME                1 (print)
             14 LOAD_CONST               2 ('a > 10')
             16 CALL_FUNCTION            1
             18 POP_TOP
             20 JUMP_FORWARD            44 (to 66)

  4     >>   22 LOAD_NAME                0 (a)
             24 LOAD_CONST               8 (-2)
             26 COMPARE_OP               0 (<)
             28 POP_JUMP_IF_FALSE       40

  5          30 LOAD_NAME                1 (print)
             32 LOAD_CONST               4 ('a < -2')
             34 CALL_FUNCTION            1
             36 POP_TOP
             38 JUMP_FORWARD            26 (to 66)

  6     >>   40 LOAD_NAME                0 (a)
             42 LOAD_CONST               0 (1)
             44 COMPARE_OP               2 (==)
             46 POP_JUMP_IF_FALSE       58

  7          48 LOAD_NAME                1 (print)
             50 LOAD_CONST               5 ('a == 1')
             52 CALL_FUNCTION            1
             54 POP_TOP
             56 JUMP_FORWARD             8 (to 66)

  9     >>   58 LOAD_NAME                1 (print)
             60 LOAD_CONST               6 ('unkonwn')
             62 CALL_FUNCTION            1
             64 POP_TOP
        >>   66 LOAD_CONST               7 (None)
             68 RETURN_VALUE
```

### 比较操作
Python 的字节码的 if 操作和汇编很像,都是进行判断 然后通过 jump 跳到正确的地方

```C
/* Rich comparison opcodes */
#define Py_LT 0
#define Py_LE 1
#define Py_EQ 2
#define Py_NE 3
#define Py_GT 4
#define Py_GE 5
[opcode.h]
enum cmp_op {PyCmp_LT=Py_LT, PyCmp_LE=Py_LE, PyCmp_EQ=Py_EQ, PyCmp_NE=Py_NE,
                PyCmp_GT=Py_GT, PyCmp_GE=Py_GE, PyCmp_IN, PyCmp_NOT_IN,
                PyCmp_IS, PyCmp_IS_NOT, PyCmp_EXC_MATCH, PyCmp_BAD};
```

大于是 PyCmp_GT 操作对应 4,因此 COMPARE_OP 指令的参数就是 PyCmp_GT

```C
TARGET(COMPARE_OP) {
    PyObject *right = POP();  
    PyObject *left = TOP();
    PyObject *res = cmp_outcome(oparg, left, right); // 这一句就是通过 oparg 的方式进行比较
    Py_DECREF(left);
    Py_DECREF(right);
    SET_TOP(res);
    if (res == NULL)
        goto error;
    PREDICT(POP_JUMP_IF_FALSE);
    PREDICT(POP_JUMP_IF_TRUE);
    DISPATCH();
}
```
```C
static PyObject *
cmp_outcome(int op, PyObject *v, PyObject *w)
{
    int res = 0;
    switch (op) {
    case PyCmp_IS:
        res = (v == w);  // is 比较的是不是指针相同
        break;
    case PyCmp_IS_NOT:
        res = (v != w); // 指针不相同
        break;
    case PyCmp_IN:
        res = PySequence_Contains(w, v); // in 使用 Sequence 的 Contains
        if (res < 0)
            return NULL;
        break;
    case PyCmp_NOT_IN:
        res = PySequence_Contains(w, v);  
        if (res < 0)
            return NULL;
        res = !res;
        break;
    case PyCmp_EXC_MATCH:
        if (PyTuple_Check(w)) {
            Py_ssize_t i, length;
            length = PyTuple_Size(w);
            for (i = 0; i < length; i += 1) {
                PyObject *exc = PyTuple_GET_ITEM(w, i);
                if (!PyExceptionClass_Check(exc)) {
                    PyErr_SetString(PyExc_TypeError,
                                    CANNOT_CATCH_MSG);
                    return NULL;
                }
            }
        }
        else {
            if (!PyExceptionClass_Check(w)) {
                PyErr_SetString(PyExc_TypeError,
                                CANNOT_CATCH_MSG);
                return NULL;
            }
        }
        res = PyErr_GivenExceptionMatches(v, w);
        break;
    default:
        return PyObject_RichCompare(v, w, op); // 我们比较大于所以用它
    }
    v = res ? Py_True : Py_False;
    Py_INCREF(v);
    return v;
}
```
```C
PyObject *
PyObject_RichCompare(PyObject *v, PyObject *w, int op)
{
    PyObject *res;

    assert(Py_LT <= op && op <= Py_GE); // 0 到 5 之间
    if (v == NULL || w == NULL) {
        if (!PyErr_Occurred())
            PyErr_BadInternalCall();
        return NULL;
    }
    if (Py_EnterRecursiveCall(" in comparison"))
        return NULL;
    res = do_richcompare(v, w, op);
    Py_LeaveRecursiveCall();
    return res;
}
```
```C
/* Perform a rich comparison, raising TypeError when the requested comparison
   operator is not supported. */
static PyObject *
do_richcompare(PyObject *v, PyObject *w, int op)
{
    richcmpfunc f;
    PyObject *res;
    int checked_reverse_op = 0;

    if (v->ob_type != w->ob_type &&
        PyType_IsSubtype(w->ob_type, v->ob_type) &&
        (f = w->ob_type->tp_richcompare) != NULL) {
        // 如果v 和 w 的类型属于父类型和子类型的关系,并且 w 类定义了tp_richcompare 
        checked_reverse_op = 1;
        res = (*f)(w, v, _Py_SwappedOp[op]);
        if (res != Py_NotImplemented)
            return res;
        Py_DECREF(res);
    }
    if ((f = v->ob_type->tp_richcompare) != NULL) {
        // 如果 v 类定义了 tp_richcompare
        res = (*f)(v, w, op);
        if (res != Py_NotImplemented)
            return res;
        Py_DECREF(res);
    }
    if (!checked_reverse_op && (f = w->ob_type->tp_richcompare) != NULL) {   // 两个类类型不同也要比较
        res = (*f)(w, v, _Py_SwappedOp[op]);
        if (res != Py_NotImplemented)
            return res;
        Py_DECREF(res);
    }
    /* If neither object implements it, provide a sensible default
       for == and !=, but raise an exception for ordering. */
    switch (op) {
    // 比较是不是相同的指针
    case Py_EQ:
        res = (v == w) ? Py_True : Py_False;
        break;
    case Py_NE:
        res = (v != w) ? Py_True : Py_False;
        break;
    default:
    // 实在没有比较下去的必要了 就报错喽
        PyErr_Format(PyExc_TypeError,
                     "'%s' not supported between instances of '%.100s' and '%.100s'",
                     opstrings[op],
                     v->ob_type->tp_name,
                     w->ob_type->tp_name);
        return NULL;
    }
    Py_INCREF(res);
    return res;
}
```
### bool 对象

```C
/* Use these macros */
#define Py_False ((PyObject *) &_Py_FalseStruct)
#define Py_True ((PyObject *) &_Py_TrueStruct)
```
```C
/* The objects representing bool values False and True */

struct _longobject _Py_FalseStruct = {
    PyVarObject_HEAD_INIT(&PyBool_Type, 0)
    { 0 }
};

struct _longobject _Py_TrueStruct = {
    PyVarObject_HEAD_INIT(&PyBool_Type, 1)
    { 1 }
};
```
我们看到 Python 中 True 和 False 是通过 0 和 1 表示的.

### 跳跃指令
```C
#define PREDICT(op) \
    do{ \
        _Py_CODEUNIT word = *next_instr; \
        opcode = _Py_OPCODE(word); \
        if (opcode == op){ \
            oparg = _Py_OPARG(word); \
            next_instr++; \
            goto PRED_##op; \
        } \
    } while(0)
``` 
这里是一个优化, 如果下一个是我们猜测的 POP_JUMP_IF_FALSE 或者是 POP_JUMP_IF_TRUE, 会直接跳转 PREDICTED(POP_JUMP_IF_FALSE) 或者 PREDICTED(POP_JUMP_IF_TRUE); 
```C
#define PREDICTED(op)           PRED_##op:
```
总感觉这样优化不太多.
```C
PREDICTED(POP_JUMP_IF_FALSE);
TARGET(POP_JUMP_IF_FALSE) {
    PyObject *cond = POP();
    int err;
    if (cond == Py_True) { // 如果 是 True 的话直接向下运行
        Py_DECREF(cond);
        FAST_DISPATCH();
    }
    if (cond == Py_False) { // False 跳转
        Py_DECREF(cond);
        JUMPTO(oparg);   
        FAST_DISPATCH();
    }
    err = PyObject_IsTrue(cond);  // 通用判断
    Py_DECREF(cond);
    if (err > 0)
        ;
    else if (err == 0)
        JUMPTO(oparg);
    else
        goto error;
    DISPATCH();
}
```

```C
#define JUMPTO(x)       (next_instr = first_instr + (x) / sizeof(_Py_CODEUNIT))
```
不难看出 这个是通过绝对位置算出下一个位置的 oparg = 22:
_Py_CODEUNIT 是 uint16_t 的别名 typedef uint16_t _Py_CODEUNIT; 因此它的sizeof是2. 这边就是将指令跳到第11条指令了.