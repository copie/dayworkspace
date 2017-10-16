# Python装饰器-LEGB命名空间

之所以我把命名空间和装饰器一起学习，是因为学装饰器前要理解闭包，毕竟装饰器就是对闭包的使用。要学闭包就要对Python的命名空间有了解。这样才会不什么都搞不懂。

## 命名空间
**命名空间(namespace)** : 名字(标识符)到对象的映射。

简而言之，命名空间 可以理解为: **记录对象和对象名字对应关系的空间**;现在Python的大部分命名空间是通过字典实现的，也就是一个命名空间就是一个名字到对象的映射，标识符是键，对象是值。像下面这个样子

    In [7]: def x(x):
    ...:     def y(y):
    ...:         print(locals())
    ...:     print(locals())
    ...:     return y
    ...:

    In [8]: z = x(10)(20)
    {'y': <function x.<locals>.y at 0x7fe1f40999d8>, 'x':10}
    {'y': 20}

## LEGB

### **LEGB 命名空间**

Python 四类命名空间 简写为 LEGB

1. 局部命名空间(local) : 指的是一个函数或者一个类所定义的命名空间;包括函数的参数，局部变量，类的属性等

2. 闭包命名空间(enclosing function) : 闭包名称空间(Python3引入)
3. 全局命名空间(global) : 读取一个模块(也就是一个.py文件)后产生的名称空间
4. 内建命名空间(builtin) : Python 解释器启动时自动载入的 __built__ 模块后形成的e名称空间;类似于这个

        {'In': ['', 'locals()'],
        'Out': {},
        '_': '',
        '__': '',
        '___': '',
        '__builtin__': <module 'builtins' (built-in)>,
        '__builtins__': <module 'builtins' (built-in)>,
        '__doc__': 'Automatically created module for IPython interactive environment',
        '__loader__': None,
        '__name__': '__main__',
        '__package__': None,
        '__spec__': None,
        '_dh': ['/home/copie'],
        '_i': '',
        '_i1': 'locals()',
        '_ih': ['', 'locals()'],
        '_ii': '',
        '_iii': '',
        '_oh': {},
        '_sh': <module 'IPython.core.shadowns' from '/usr/lib/python3.6/site-packages/IPython/core/shadowns.py'>,
        'exit': <IPython.core.autocall.ExitAutocall at 0x7fe1f4c7f860>,
        'get_ipython': <bound method InteractiveShell.get_ipython of <IPython.terminal.interactiveshell.TerminalInteractiveShell object at 0x7fe1f4c942e8>>,
        'quit': <IPython.core.autocall.ExitAutocall at 0x7fe1f4c7f860>}

### LEGB的访问规则

通过上面描述，我们发现 LEGB 四类命名空间本身具有明显的内外层级概念，而这种层级概念正是构建作用域的前提：

作用域依据这种层级概念将不同类型的命名空间组织起来并划归到不同层级的作用域，然后定义好不同层级作用域之间的访问规则，从而实现命名空间的直接访问;

LEGB 访问规则：
**同样的标识符在各层命名空间中可以被重复使用而不会发生冲突，但 Python 寻找一个标识符的过程总是从当前层开始逐层往上找，直到首次找到这个标识符为止;**