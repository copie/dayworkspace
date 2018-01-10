# Python 变量作用域规则

想要了解 Python 变量作用域规则,先看一下我这篇blog[Python装饰器-LEGB命名空间](https://copie.cn/index.php/archives/Python%E8%A3%85%E9%A5%B0%E5%99%A8-LEGB%E5%91%BD%E5%90%8D%E7%A9%BA%E9%97%B4.html)来了解Python LEGB的访问规则
下面说的会在这个基础之上.
## 变量作用域

我们定义并测试一个函数,它读取两个变量的值:一个是局部变量 a ,是函数的参数; 另一个是变量 b, 这个函数没有定义它.

### 代码端一 : 一个函数,读取一个局部变量和一个全局变量

    In [1]: def f1(a):
    ...:     print(a)
    ...:     print(b)
    ...:     

    In [2]: f1(3)
    3
    ---------------------------------------------------------------------------
    NameError                                 Traceback (most recent call last)
    <ipython-input-2-db0f80b394ed> in <module>()
    ----> 1 f1(3)

    <ipython-input-1-c1318c6d0711> in f1(a)
        1 def f1(a):
        2     print(a)
    ----> 3     print(b)
        4 

    NameError: name 'b' is not defined

这里出现错误并不奇怪了. 在代码段一如果先给全局变量 b 赋值,然后在调用 f1 就不会出现错误了.

### 代码段二:

    In [3]: b = 6

    In [4]: f1(3)
    3
    6

    In [5]: 

看代码段三中的 f2 函数. 前两行代码和代码段一中的 f1 一样,然后为 b 赋值, 再打印它的值.可是,在赋值之前,第二个 print 就失败了.

### 代码段三: b 是局部变量,因为在函数定义体中给它赋值了

    In [5]: b = 6

    In [6]: def f2(a):
    ...:     print(a)
    ...:     print(b)
    ...:     b = 9
    ...:     

    In [7]: f2(3)
    3
    ---------------------------------------------------------------------------
    UnboundLocalError                         Traceback (most recent call last)
    <ipython-input-7-ddde86392cb4> in <module>()
    ----> 1 f2(3)

    <ipython-input-6-2304a03d7bfd> in f2(a)
        1 def f2(a):
        2     print(a)
    ----> 3     print(b)
        4     b = 9
        5 

    UnboundLocalError: local variable 'b' referenced before assignment
 
 注意,首先输出了 3,这说明 print(a) 语句是执行了. 但第二个语句 print(b) 执行不了.一开始我很吃惊,我觉得会打印出 6 ,因为有个全局变量 b, 而且是在 print(b) 之后为局部变量 b 赋值的.

可事实是,Python编译函数的定义体时,它判断 b 是全局变量, 因为在函数中给他赋值了.生成的字节码证实了这种判断, Python 会尝试从本地环境获取变量 b. 后面调用 f2(3)时,f2 定义体会获取并打印局部变量 a 的值,但是获取局部变量 b 的值时,发现 b 并没有绑定值.

这不是缺陷,而是设计的选择: Python 不要求声明变量, 但是假定在函数定义体中赋值的变量是局部变量,这比 JS 的行为好多了, JS 也并不要求声明变量,但是如果忘记把变量声明为局部变量 (使用var), 可能会在不知情的情况下获取全局变量.

如果函数中赋值时想让解释器把 b 当成全局变量,使用 global 声明:

### 代码段四

    In [9]: b = 6

    In [10]: def f3(a):
        ...:     global b
        ...:     print(a)
        ...:     print(b)
        ...:     b = 9
        ...:     

    In [11]: f3(3)
    3
    6

    In [12]: b
    Out[12]: 9

    In [13]: b = 30

    In [14]: b
    Out[14]: 30

    In [15]: 

### 附加内容(比较字节码)

dis 模块为反汇编 Python 函数字节码提供了简单的方式,代码段 五和六 分别是代码段一 f1 和代码段三中的 f2 的字节码.

#### 代码段五: 反汇编代码段一中的 f1 函数

    In [15]: from dis import dis

    In [16]: dis(f1)
    2           0 LOAD_GLOBAL              0 (print) ① 
                2 LOAD_FAST                0 (a) ②
                4 CALL_FUNCTION            1
                6 POP_TOP

    3           8 LOAD_GLOBAL              0 (print)
                10 LOAD_GLOBAL              1 (b) ③
                12 CALL_FUNCTION            1
                14 POP_TOP
                16 LOAD_CONST               0 (None)
                18 RETURN_VALUE

① 加载全局名称 print
② 加载本地名称 a
③ 加载本地名称 b

请比较 代码段五中 f1 的字节码和代码段六中 f2 的字节码

#### 代码段六: 反汇编代码段三中的 f2 的字节码

    In [17]: dis(f2)
    2           0 LOAD_GLOBAL              0 (print)
                2 LOAD_FAST                0 (a)
                4 CALL_FUNCTION            1
                6 POP_TOP

    3           8 LOAD_GLOBAL              0 (print)
                10 LOAD_FAST                1 (b) ①
                12 CALL_FUNCTION            1
                14 POP_TOP

    4          16 LOAD_CONST               1 (9)
                18 STORE_FAST               1 (b)
                20 LOAD_CONST               0 (None)
                22 RETURN_VALUE

① 加载本地名称 b. 这表明,编译器把 b 视作局部变量,即使后面才为 b 赋值, 因为变量的种类(是不是局部变量)不能改变函数的定义体.

运行字节码的 CPython VM 是栈机器,因此 LOAD 和 POP 操作引用的是栈.
