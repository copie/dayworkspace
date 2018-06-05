# Python内核源码阅读(二十三)

## Python 虚拟机中的 for 循环控制流

我不应该跟着 cpython 的官方库去看的,赶脚自己就是铁头娃和填坑侠.
```
>>> x = "for i in (1, 2):\n    print(i)"
>>> dis(x)
  1           0 LOAD_CONST               0 ((1, 2))
              2 GET_ITER
        >>    4 FOR_ITER                12 (to 18)
              6 STORE_NAME               0 (i)

  2           8 LOAD_NAME                1 (print)
             10 LOAD_NAME                0 (i)
             12 CALL_FUNCTION            1
             14 POP_TOP
             16 JUMP_ABSOLUTE            4
        >>   18 LOAD_CONST               1 (None)
             20 RETURN_VALUE
```

```C
TARGET(GET_ITER) {
      /* before: [obj]; after [getiter(obj)] */
      PyObject *iterable = TOP();  // 获取可迭代对象
      PyObject *iter = PyObject_GetIter(iterable); // 获取迭代器
      Py_DECREF(iterable); // iterable 引用计数 -1
      SET_TOP(iter);  // 替代栈顶元素
      if (iter == NULL)
            goto error;
      PREDICT(FOR_ITER);  // 猜测下一个指令是 FOR_ITER
      PREDICT(CALL_FUNCTION); // 猜测下一个指令是 CALL_FUNCTION
      DISPATCH();
}
```

```C
PREDICTED(FOR_ITER);
TARGET(FOR_ITER) {
      /* before: [iter]; after: [iter, iter()] *or* [] */
      PyObject *iter = TOP(); // 读取栈顶迭代器
      PyObject *next = (*iter->ob_type->tp_iternext)(iter); // 通过 next 方法获取下一个值
      if (next != NULL) { // 如果值不为 NULL
            PUSH(next); // 将获取到的值压入运行时栈
            PREDICT(STORE_FAST); 
            PREDICT(UNPACK_SEQUENCE);
            DISPATCH(); // 可以理解为 continue
      }
      if (PyErr_Occurred()) {
            if (!PyErr_ExceptionMatches(PyExc_StopIteration))
                  goto error;
            else if (tstate->c_tracefunc != NULL)
                  call_exc_trace(tstate->c_tracefunc, tstate->c_traceobj, tstate, f);
            PyErr_Clear();
      }
      /* iterator ended normally */ // 这里说我们的循环正常结束
      STACKADJ(-1); // 将栈顶指针向下移动一位
      Py_DECREF(iter);
      JUMPBY(oparg);  // 跳转到相对路径 oparg 行
      PREDICT(POP_BLOCK); // 跳转到上一个 Frame, 这里没有道理啊, 这个 3.8a 版本 没有 SETUP_LOOP 没有看到新建也一个 FRame 啊,很尴尬.问题先放在这里. 
      DISPATCH();
}
```

```C
PREDICTED(JUMP_ABSOLUTE);
TARGET(JUMP_ABSOLUTE) {
      JUMPTO(oparg); // 通过绝对路径跳转
```

for 的运行思路我们已经看明白了.现在我们要看看几个函数


```C
PyObject *
PyObject_GetIter(PyObject *o) // 获取一个可迭代对象的迭代器
{
    PyTypeObject *t = o->ob_type;
    getiterfunc f;

    f = t->tp_iter;
    if (f == NULL) {
        if (PySequence_Check(o)) // 检查这个对象是不是一个序列,如果是序列的话可以通过当前对象新建一个迭代器
            return PySeqIter_New(o);
        return type_error("'%.200s' object is not iterable", o);
    }
    else { // 如果 这个对象有实现 ob_type->tp_iter, 如果记得 __iter__ 的话
        PyObject *res = (*f)(o);  // 调用函数获取迭代器
        if (res != NULL && !PyIter_Check(res)) {
            PyErr_Format(PyExc_TypeError,
                         "iter() returned non-iterator "
                         "of type '%.100s'",
                         res->ob_type->tp_name);
            Py_DECREF(res);
            res = NULL;
        }
        return res;
    }
}
```
```C
PyObject *
PySeqIter_New(PyObject *seq)
{
    seqiterobject *it;

    if (!PySequence_Check(seq)) {
        PyErr_BadInternalCall();
        return NULL;
    }
    it = PyObject_GC_New(seqiterobject, &PySeqIter_Type); // 新建一个 PySeqIter_Type 的对象, 一个序列迭代器对象.
    if (it == NULL)
        return NULL;
    it->it_index = 0; // next 也用到了 也提一下
    Py_INCREF(seq);
    it->it_seq = seq;  // 设置 it->it_seq 这个会在next处用到提一下
    _PyObject_GC_TRACK(it);  // 内存相关
    return (PyObject *)it;
}
```
```C
PyTypeObject PySeqIter_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    "iterator",                                 /* tp_name */
    sizeof(seqiterobject),                      /* tp_basicsize */
    0,                                          /* tp_itemsize */
    /* methods */
    (destructor)iter_dealloc,                   /* tp_dealloc */
    0,                                          /* tp_print */
    0,                                          /* tp_getattr */
    0,                                          /* tp_setattr */
    0,                                          /* tp_reserved */
    0,                                          /* tp_repr */
    0,                                          /* tp_as_number */
    0,                                          /* tp_as_sequence */
    0,                                          /* tp_as_mapping */
    0,                                          /* tp_hash */
    0,                                          /* tp_call */
    0,                                          /* tp_str */
    PyObject_GenericGetAttr,                    /* tp_getattro */
    0,                                          /* tp_setattro */
    0,                                          /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,/* tp_flags */
    0,                                          /* tp_doc */
    (traverseproc)iter_traverse,                /* tp_traverse */
    0,                                          /* tp_clear */
    0,                                          /* tp_richcompare */
    0,                                          /* tp_weaklistoffset */
    PyObject_SelfIter,                          /* tp_iter */
    iter_iternext,                              /* tp_iternext */
    seqiter_methods,                            /* tp_methods */
    0,                                          /* tp_members */
};
```

```C
PyObject *
PyObject_SelfIter(PyObject *obj) // 这里就可以看出一个迭代器对象的 __iter__ 返回的就是它自身.
{
    Py_INCREF(obj);
    return obj;
}
```

```C
static PyObject *
iter_iternext(PyObject *iterator)
{
    seqiterobject *it;
    PyObject *seq;
    PyObject *result;

    assert(PySeqIter_Check(iterator));
    it = (seqiterobject *)iterator; //  类型转换
    seq = it->it_seq;  // 获取可迭代对象 类似与 [1,2,3] 这种
    if (seq == NULL)
        return NULL;
    if (it->it_index == PY_SSIZE_T_MAX) {
        PyErr_SetString(PyExc_OverflowError,
                        "iter index too large");
        return NULL;
    }

    result = PySequence_GetItem(seq, it->it_index);
    if (result != NULL) {
        it->it_index++; // 索引 +1
        return result;
    }
    if (PyErr_ExceptionMatches(PyExc_IndexError) ||
        PyErr_ExceptionMatches(PyExc_StopIteration))
    {
        PyErr_Clear();
        it->it_seq = NULL;
        Py_DECREF(seq);
    }
    return NULL;
}
```

```C
PyObject *
PySequence_GetItem(PyObject *s, Py_ssize_t i)
{
    PySequenceMethods *m;

    if (s == NULL) {
        return null_error();
    }

    m = s->ob_type->tp_as_sequence;
    if (m && m->sq_item) {
        if (i < 0) { // 如果负索引的话
            if (m->sq_length) {
                Py_ssize_t l = (*m->sq_length)(s);
                if (l < 0) {
                    assert(PyErr_Occurred());
                    return NULL;
                }
                i += l; // 将索引值 加上 可迭代对象的长度.
            }
        }
        return m->sq_item(s, i); // 返回 s[i]
    }

    return type_error("'%.200s' object does not support indexing", s);
}
```