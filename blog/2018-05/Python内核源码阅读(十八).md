# Python内核源码阅读(十八)
Python 对原程序编译结果生成一个 .pyc 文件. Python 对 .py 文件的编译结果是字节码,为了能重复使用而不需要重新编译才有了写成 .pyc 文件. 对于解释器来说 PyCodeObject 对象才是真正的编译结果, pyc 文件只是这个对象在硬盘上的表现形式.
## PyCodeObject
```C
/* Bytecode object */
typedef struct {
    PyObject_HEAD
    int co_argcount;            /* #arguments, except *args */
    int co_kwonlyargcount;      /* #keyword only arguments */
    int co_nlocals;             /* #local variables */
    int co_stacksize;           /* #entries needed for evaluation stack */
    int co_flags;               /* CO_..., see below */
    int co_firstlineno;         /* first source line number */
    PyObject *co_code;          /* instruction opcodes */
    PyObject *co_consts;        /* list (constants used) */
    PyObject *co_names;         /* list of strings (names used) */
    PyObject *co_varnames;      /* tuple of strings (local variable names) */
    PyObject *co_freevars;      /* tuple of strings (free variable names) */
    PyObject *co_cellvars;      /* tuple of strings (cell variable names) */
    /* The rest aren't used in either hash or comparisons, except for co_name,
       used in both. This is done to preserve the name and line number
       for tracebacks and debuggers; otherwise, constant de-duplication
       would collapse identical functions/lambdas defined on different lines.
    */
    Py_ssize_t *co_cell2arg;    /* Maps cell vars which are arguments. */
    PyObject *co_filename;      /* unicode (where it was loaded from) */
    PyObject *co_name;          /* unicode (name, for reference) */
    PyObject *co_lnotab;        /* string (encoding addr<->lineno mapping) See
                                   Objects/lnotab_notes.txt for details. */
    void *co_zombieframe;       /* for optimization only (see frameobject.c) */
    PyObject *co_weakreflist;   /* to support weakrefs to code objects */
    /* Scratch space for extra data relating to the code object.
       Type is a void* to keep the format private in codeobject.c to force
       people to go through the proper APIs. */
    void *co_extra;
} PyCodeObject;
```
编译器在对源码进行编译的时候 没哟个 Code Block 会创建一个 PyCodeObject 对象,在 Python 中 Code Block 出现层层嵌套的情况 我们看到的 .pyc 文件就像是最外面一层

 <table>
     <tr>
         <th>Field</th>
         <th>Content</th>
         <th>Type</th>
     </tr>
     <tr>
         <td>co_argcount</td>
         <td>Code Block 的位置参数的个数,比如说一个函数的位置参数的个数</td>
         <td>int</td>
     </tr>
     <tr>
        <td>co_kwonlyargcount</td>
        <td>Code Block 关键字参数的个数</td>
        <td>int</td>
     </tr>
     <tr>
        <td>co_nlocals</td>
        <td>Code Block 局部变量的个数</td>
        <td>int</td>
     </tr>
     <tr>
        <td>co_stacksize</td>
        <td>执行该段 Code Block 需要的栈空间</td>
        <td>int</td>
     </tr>
     <tr>
        <td>co_firstlineno</td>
        <td>Code Block 对应的 .py 文件中的起始行号</td>
        <td>int</td>
     </tr>
     <tr>
        <td>co_code</td>
        <td>Code Block 编译所得的字节码</td>
        <td>PyBytesObject</td>
     </tr>
     <tr>
        <td>co_consts</td>
        <td>Code Block 中的常量集合</td>
        <td>PyTupleObject</td>
    </tr>
    <tr>
        <td>co_names</td>
        <td>Code Block 中的符号集合</td>
        <td>PyTupleObject</td>
    </tr>
    <tr>
        <td>co_varnames</td>
        <td>Code Block 中的局部变量名集合</td>
        <td>PyTupleObject</td>
    </tr>
    <tr>
        <td>co_freevars</td>
        <td>Code Block 中的自由变量名集合(与闭包有关)</td>
        <td>PyTupleObject</td>
    </tr>
    <tr>
        <td>co_cellvars</td>
        <td>Code Block 中嵌套函数所引用的局部变量名集合</td>
        <td>PyTupleObject</td>
    </tr>
    <tr>
        <td>co_filename</td>
        <td>Code Block 对应的 .py 文件名</td>
        <td>PyUnicodeObject</td>
    </tr>
    <tr>
        <td>co_name</td>
        <td>Code Block 的名字，通常是函数名/类名/模块名</td>
        <td>PyUnicodeObject</td>
    </tr>
    <tr>
        <td>co_lnotab</td>
        <td>Code Block 的字节码指令于 .py 文件中 source code 行号对应关</td>
        <td>PyBytesObject</td>
    </tr>
 </table>

 > Python编译器在对Python源代码进行编译的时候，对于代码中的一个Code Block，会创建一个PyCodeObject对象与这段代码对应。那么如何确定多少代码算是一个Code Block呢？事实上，Python有一个简单而清晰的规则：当进入一个新的名字空间，或者说作用域时，我们就算是进入了一个新的Code Block了。<p>
> 摘自：《Python源码剖析》 — 陈儒

## 访问 PyCodeObject 对象
在 python 中,有与 C 一级的 PyCodeObject对象对应的对象---code对象

```Python
[1.py]
a = 100
b = "hello"
c = b + " world!\n"

print(c*a)
```

```Python
>>> source = open("1.py").read()
>>> co = compile(source,'1.py','exec')
>>> dir(co)
['__class__', '__delattr__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__le__', '__lt__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', 'co_argcount', 'co_cellvars', 'co_code', 'co_consts', 'co_filename', 'co_firstlineno', 'co_flags', 'co_freevars', 'co_kwonlyargcount', 'co_lnotab', 'co_name', 'co_names', 'co_nlocals', 'co_stacksize', 'co_varnames']
>>> co.co_names
('a', 'b', 'c', 'print')
>>> co.co_consts
(100, 'hello', ' world!\n', None)
```

## 字节码

```
>>> source = open("1.py").read()
>>> co = compile(source,'1.py','exec')
>>> import dis
>>> dis.dis(co)
  1           0 LOAD_CONST               0 (100)
              2 STORE_NAME               0 (a)

  2           4 LOAD_CONST               1 ('hello')
              6 STORE_NAME               1 (b)

  3           8 LOAD_NAME                1 (b)
             10 LOAD_CONST               2 (' world!\n')
             12 BINARY_ADD
             14 STORE_NAME               2 (c)

  5          16 LOAD_NAME                3 (print)
             18 LOAD_NAME                2 (c)
             20 LOAD_NAME                0 (a)
             22 BINARY_MULTIPLY
             24 CALL_FUNCTION            1
             26 POP_TOP
             28 LOAD_CONST               3 (None)
             30 RETURN_VALUE
```

+ 第一列 字节码指令对应源码的行数
+ 第二列 当前字节码在 co_code 中的偏移位置
+ 第三列 当前字节码指令
+ 第四列 当前字节码的指令参数