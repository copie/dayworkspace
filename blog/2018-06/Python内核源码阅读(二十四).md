# Python内核源码阅读(二十四)

## 虚拟机产生异常及捕获

我们下面要研究的就是 1/0 这个计算过程中是如何将 ZeroDivisionError 抛出的.
```Python
>>> x = "1/0"
>>> from dis import  dis
>>> dis(x)
  1           0 LOAD_CONST               0 (1)
              2 LOAD_CONST               1 (0)
              4 BINARY_TRUE_DIVIDE
              6 RETURN_VALUE
>>> 
```
```C
TARGET(BINARY_TRUE_DIVIDE) {
    PyObject *divisor = POP();
    PyObject *dividend = TOP();
    PyObject *quotient = PyNumber_TrueDivide(dividend, divisor); // 进行数值真除法运算.
    Py_DECREF(dividend);
    Py_DECREF(divisor);
    SET_TOP(quotient);
    if (quotient == NULL)
        goto error;   // 一会我们就要跳到这里看看这个 error 到底干了什么
    DISPATCH();
}
```
```C
PyObject *
PyNumber_TrueDivide(PyObject *v, PyObject *w)
{
    return binary_op(v, w, NB_SLOT(nb_true_divide), "/");
    // NB_SLOT(nb_true_divide) 我的猜测是计算 nb_true_divide 这个函数在 PyNumberMethods 中的偏移.以后再说.
}
```
```C
static PyObject *
binary_op(PyObject *v, PyObject *w, const int op_slot, const char *op_name)
{
    PyObject *result = binary_op1(v, w, op_slot); // 这里就是进行计算的 op_slot 我们知道他是一个nb_true_divide 在PyNumberMethods 中的偏移
    if (result == Py_NotImplemented) {  // 计算失败
        Py_DECREF(result); 

        if (op_slot == NB_SLOT(nb_rshift) &&
            PyCFunction_Check(v) &&
            strcmp(((PyCFunctionObject *)v)->m_ml->ml_name, "print") == 0)
        {
            PyErr_Format(PyExc_TypeError,
                "unsupported operand type(s) for %.100s: "
                "'%.100s' and '%.100s'. Did you mean \"print(<message>, "
                "file=<output_stream>)\"?",
                op_name,
                v->ob_type->tp_name,
                w->ob_type->tp_name);
            return NULL;
        }

        return binop_type_error(v, w, op_name);
    }
    return result;
}
```
```C
// 这个宏就是将 PyNumberMethods 中 对应位置的计算方法取出来
//   &long_as_number,                            /* tp_as_number */ 这个在 PyLongObject 中整数对象的 tp_as_number
#define NB_BINOP(nb_methods, slot) \
        (*(binaryfunc*)(& ((char*)nb_methods)[slot]))
```
```C
static PyObject *
binary_op1(PyObject *v, PyObject *w, const int op_slot)
{
    PyObject *x;
    binaryfunc slotv = NULL;
    binaryfunc slotw = NULL;

    if (v->ob_type->tp_as_number != NULL) // 就是说 v 具有数值属性
        slotv = NB_BINOP(v->ob_type->tp_as_number, op_slot);  // 取出相应的计算函数.
    if (w->ob_type != v->ob_type &&
        w->ob_type->tp_as_number != NULL) {
        slotw = NB_BINOP(w->ob_type->tp_as_number, op_slot);
        if (slotw == slotv)
            slotw = NULL;
    }
    // 上面两个 if 就是为了寻找一个合适的 slotv 或者 slotw 也就是一个计算函数,如果知道 __add__, __radd__ 这样的魔法函数应该好理解这个
    if (slotv) {
        if (slotw && PyType_IsSubtype(w->ob_type, v->ob_type)) {
            // PyType_IsSubtype 是查看 w类型 的 mro 中是否有 v类型,也就是说 v的类型是不是w的类型的父类型
            x = slotw(v, w);
            if (x != Py_NotImplemented) 
                return x;
            Py_DECREF(x); /* can't do it */
            slotw = NULL;
        }
        x = slotv(v, w);
        if (x != Py_NotImplemented)
            return x;
        Py_DECREF(x); /* can't do it */
    }
    if (slotw) {
        x = slotw(v, w);
        if (x != Py_NotImplemented)
            return x;
        Py_DECREF(x); /* can't do it */
    }
    Py_RETURN_NOTIMPLEMENTED; // 如果上面都失败了 对 Py_NotImplemented 的引用及时 +1,并且返回 Py_NotImplemented
}
```
通过上面的分析如果我们的 v 是一个 int 的话那么 v->ob_type->tp_as_number 指向的就是,long_true_divide.

```C
static PyObject * long_true_divide(PyObject *v, PyObject *w)
{
    PyLongObject *a, *b, *x;
    Py_ssize_t a_size, b_size, shift, extra_bits, diff, x_size, x_bits;
    digit mask, low;
    int inexact, negate, a_is_small, b_is_small;
    double dx, result;

    CHECK_BINOP(v, w);
    a = (PyLongObject *)v;
    b = (PyLongObject *)w;
    a_size = Py_ABS(Py_SIZE(a));
    b_size = Py_ABS(Py_SIZE(b));
    negate = (Py_SIZE(a) < 0) ^ (Py_SIZE(b) < 0);
    if (b_size == 0) {  // 当发现除数是 0 的时候
        PyErr_SetString(PyExc_ZeroDivisionError,
                        "division by zero");
        goto error;
    }
    ...
}
```

## 记录异常信息

在 PyErr_SetString 后, 会沿着 PyErr_SetString -> PyErr_SetObject -> PyErr_Restore , 在 PyErr_Restore 中, python将存放这个异常:

```C
void
PyErr_Restore(PyObject *type, PyObject *value, PyObject *traceback)
{
    PyThreadState *tstate = PyThreadState_GET();  // 获取当前线程的状态对象
    PyObject *oldtype, *oldvalue, *oldtraceback;

    if (traceback != NULL && !PyTraceBack_Check(traceback)) {
        /* XXX Should never happen -- fatal error instead? */
        /* Well, it could be None. */
        Py_DECREF(traceback);
        traceback = NULL;
    }

    /* Save these in locals to safeguard against recursive
       invocation through Py_XDECREF */
    
    // 暂存 以前的异常信息
    oldtype = tstate->curexc_type;
    oldvalue = tstate->curexc_value;
    oldtraceback = tstate->curexc_traceback;

    // 设置当前的异常信息
    tstate->curexc_type = type;
    tstate->curexc_value = value;
    tstate->curexc_traceback = traceback;

    // 抛弃以前的异常信息
    Py_XDECREF(oldtype);
    Py_XDECREF(oldvalue);
    Py_XDECREF(oldtraceback);
}
```
最终 curexc_type 存放下了 PyExc_ZeroDivisionError , 而 curexc_value 存放了字符串 "division by zero" . 当前的活动线程用 PyThreadState_GET 获得, 将异常信息存放到线程状态对象中.

在python的sys模块中, 提供了一个接口, 我们可以访问python虚拟机存在线程状态中的异常信息:
```Python
In [1]: import sys
   ...: try:
   ...:     1/0
   ...: except Exception:
   ...:     print(sys.exc_info()[0])  # 获得tstate->curexc_type
   ...:     print(sys.exc_info()[1])  # 获得tstate->curexc_value
   ...:     
<class 'ZeroDivisionError'>
division by zero
```
上面符合我们的预期

