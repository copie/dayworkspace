# Python 内核源码阅读(五)

## 对象的行为

在[Python 内核源码阅读(三)](https://copie.cn/index.php/archives/Python-%E5%86%85%E6%A0%B8%E6%BA%90%E7%A0%81%E9%98%85%E8%AF%BB-%E4%B8%89.html)中我们了解到在 PyTypeObject 中定义了大量的函数指针,这些函数指针最终指向某个函数或者指向 NULL. 这些函数指针可以视类型对象所定义的操作,这些操作直接决定着一个对象在运行时所表现出的行为.

PyTypeObject 中 tp_hash 指明该类型的对象如何生成 hash 值. tp_hash 的类型 hashfunc 给定的是一个函数指针:


    typedef Py_hash_t (*hashfunc)(PyObject *);

---

在对象的创建中,tp_new 和 tp_init 决定了实例对象的创建和初始化,另外,在 PyTypeObject 中有三个很重要的操作族: tp_as_number, tp_as_squence 和 tp_as_mapping.


    /* Method suites for standard classes */

    PyNumberMethods *tp_as_number;   // 数值对象操作
    PySequenceMethods *tp_as_sequence; // 序列对象操作
    PyMappingMethods *tp_as_mapping;  // 字典对象操作

---
以其中 tp_as_sequence 为例


    typedef struct {
        lenfunc sq_length;
        binaryfunc sq_concat;
        ssizeargfunc sq_repeat;
        ssizeargfunc sq_item;
        void *was_sq_slice;
        ssizeobjargproc sq_ass_item;
        void *was_sq_ass_slice;
        objobjproc sq_contains;

        binaryfunc sq_inplace_concat;
        ssizeargfunc sq_inplace_repeat;
    } PySequenceMethods;


定义了作为一个序列对象支持的操作,如果一个对象被视为序列对象(如list,str),那么他的 tp_as_sequence.sq_concat (python 没有暴露类似与concat函数)就是将两个序列对象进行连接操作的具体行为.PyNumberMethods, PyMappingMethods 比较典型的例子就是 int, dict.

## 类型的类型

我们知道在 Python 中类型也是对象,每个对象都有自己的类型,那么类型的类型到底是什么呢?

    PyTypeObject PyType_Type = {
        PyVarObject_HEAD_INIT(&PyType_Type, 0)
        "type",                                     /* tp_name */
        sizeof(PyHeapTypeObject),                   /* tp_basicsize */
        sizeof(PyMemberDef),                        /* tp_itemsize */
        (destructor)type_dealloc,                   /* tp_dealloc */
        0,                                          /* tp_print */
        0,                                          /* tp_getattr */
        0,                                          /* tp_setattr */
        0,                                          /* tp_reserved */
        (reprfunc)type_repr,                        /* tp_repr */
        .
        .
        .
    };

---
我们可以清楚的看到 PyType_Type 的类型就是他本身.

```C
PyTypeObject PyLong_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    "int",                                      /* tp_name */
    offsetof(PyLongObject, ob_digit),           /* tp_basicsize */
    sizeof(digit),                              /* tp_itemsize */
    long_dealloc,                               /* tp_dealloc */
    0,                                          /* tp_print */
    0,                                          /* tp_getattr */
    0,                                          /* tp_setattr */
    0,                                          /* tp_reserved */
    long_to_decimal_string,                     /* tp_repr */
    &long_as_number,                            /* tp_as_number */
    0,                                          /* tp_as_sequence */
};
```
我们这里看到了 PyLong_Type 的类型也是 PyType_Type

所以在 Python 中任何一个对象都有一个type, 我们可以通过__class__获得.
任何一个实例对象的type都是一个类对象,而任何一个类对象的type都是元类对象.而大多情况下元类对象就是<type,'type'>,而在Python 内部<type,'type'> 对应的就是PyType_Type.

## 对象的多态

python 通过对象的 ob_type 域动态的判断,例如里面的 tp_print 的属性就是这样利用的:

```C
void Print(PyObject* object) {
    object->ob_type->tp_print(object);
}
```
---
函数之间一般通过泛型指针 PyObject* 来传递.
这样的 C API 建立在这多态机制上:
---

```C
Py_hash_t PyObject_Hash(PyObject *v)
{
    PyTypeObject *tp = Py_TYPE(v);
    if (tp->tp_hash != NULL)
        return (*tp->tp_hash)(v);
    ...
}
```
