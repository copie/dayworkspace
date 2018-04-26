# Python 内核源码阅读(一): 了解 Python 源码的结构与编译

## 自述

现在 <<Python 源码剖析>> 已经绝版了 我淘宝20块买的一本盗版的:) 刚开始过了大部分,到最后几章还是理解不动了.没有办法放在那里去写了一个 基于 Flask 的一个 Blog 系统, 但是审美有点问题所以界面比较难看. 由于大部分功能都写完了,剩下的就是我以后慢慢的添加东西.进行美化工作了.所以我又拿起来源码剖析这本书进行充电. 由于自己的水平有限,不能想大牛一样,能够很快的把握代码结构,还有就是 Python3 相对于 Python2 的改变还是很大的 这一次基于 Python3.6 的源码分析学习,有很大的压力,书上的有些代码示例在 Python3 中是被删除的所以,有些例子我会按照我自己的理解进行学习.可能不是很准确,我写的有什么地方不正确的请指正批评.  

## 克隆源码仓库

从 github 克隆 Python 内核源码仓库(也可以从官网下载)

    git clone https://github.com/python/cpython.git

切换 python 版本

    git checkout v3.6.5

## 目录简介

+ Include: 该目录包含 Python 提供的所有头文件, 如果用户需要自己用 C/C++ 编写自定义模块扩展 Python, 那么就需要用到这里面的头文件.
+ Lib: 该目录包含了 Python 自带的所有标准库, Lib 中的库都是 Python 语言编写的.
+ Modules: 该目录包含了所有用 C 编写的模块, 比如 random, cString 等.(速度要求高)
+ Parser: 该目录了 Python 解释器中的 Scanner 和 Parser 部分, 也就是词法分析和语法分析部分.
+ Object: 该目录包含所有 Python 的内建对象, 包括整数, list, dict 等.同时该目录还包括了 Python 在运行是所有的内部使用对象的实现.
+ Python: 该目录包含了 Python 解释器中的 Compiler 和 执行引擎部分,是 Python 的核心所在.


## Linux 环境下编译 Python

    ./configure -prefix=<你想要 Python 安装在什么目录下>
    make -j5
    make install

ps: make -j5 为使用多线程编程

## Python3 中与 << Python 源码剖析 >> hack 代码失败

我按照 << Python 源码剖析 >> 中 Hack 第一个 例子就失败了

书上给出的源码:

    [object.h]
    int PyObject_Print(PyObject *, FILE *, int)

---
    [intobject.h]
    static int int_print(PyIntObject *v, FILE* , int)

虽然 object.h 中还存在 Pyobject_Print() 函数 但是在 longobject.h 中已经没有类似 long_print() 这样的函数存在了

查看 Python3 源码 得到如下结果

    [longobject.c]
    [PyTypeObject PyLong_Type]
    0,                                          /* tp_print */

从上面可以看出在 python3 中 int 没有自己定义 print 方法 在 PyType_Type 中也没有发现. 所以 int 如何输出的那就要以后去看 python print 的源码了解发现了.


## PyLongObject和PyIntObject

在 Python3 中 PyLongObject 取代了 PyIntObject 也就是说 python 中 int 类型的实现 已经从原来简单的对 C long 的封装 变成另外的一种实现,具体是什么,我也不太了解.在以后的学习中再慢慢的发现吧.