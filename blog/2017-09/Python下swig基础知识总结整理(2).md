# Python下swig基础知识总结整理(2)

上一篇 Blog 我展示了一些 swig 最简单的一些用法，谁然我们还不是很明白但是还是可以从那一个Dome中写出简单的解决问题的方案的。今天呢将总结一些常用的swig 的用法。这里就不是全是示例代码了。包含一些解释了。


## 基本的对于 C/C++ 的包装

默认情况下，SWIG尝试为您的 C/C++ 代码构建一个非常自然的Python接口。函数被包装为函数，类被包装成类，等等。

### Modules

SWIG 中 ％module指令，指定 Python 模块的名称。如果你指定 '％module example'，那么所有的东西都被包装成一个 Python 的 'example' 模块

### Functions

全局函数被包装为新的Python内置函数。例如:

    %module example
    int fact(int n);

创建一个内置函数example.fact（n），它的工作原理和你想的一样：

    >>> import example
    >>> print example.fact(4)
    24
    >>>

### Global variables

SWIG完全支持 C/C++ 全局变量 然而，底层的机制有点不同于你可能期望，因为Python分配的工作原理问题。在Python中键入以下内容时:

    a = 3.4

“a”成为包含值3.4的对象的名称。如果你以后输入:

    b = a

那么“a”和“b”都是包含值3.4的对象的名称。因此，只有一个对象包含3.4，“a”和“b”都是引用它的名称。 这与C完全不同，其中变量名称是指存储值的存储器位置 (并且分配将数据复制到该位置).因此，没有直接方法将C中的变量赋值映射到Python中的变量赋值。为了提供对C全局变量的访问，SWIG创建一个被称为“cvar”的特殊对象，它被添加到每个SWIG生成的模块中。然后将全局变量作为该对象的属性进行访问。例如，考虑这个接口

    // SWIG interface file with global variables
    %module example
    ...
    %inline %{
    extern int My_variable;
    extern double density;
    %}

我们去Python 界面看一下:

    >>> import example
    >>> # Print out value of a C global variable
    >>> print example.cvar.My_variable
    4
    >>> # Set the value of a C global variable
    >>> example.cvar.density = 0.8442
    >>> # Use in a math operation
    >>> example.cvar.density = example.cvar.density*1.10

如果您在变量赋值中发生错误，您将收到一条错误消息:

    >>> example.cvar.density = "Hello"
    Traceback (most recent call last):
    File "<stdin>", line 1, in ?
    TypeError: C variable 'density (double )'
    >>>

如果一个变量被声明为const，它被包装为只读变量。尝试修改其值将导致错误。

要使普通变量为只读，可以使用％immutable指令。例如：

    %{
    extern char *path;
    %}
    %immutable;
    extern char *path;
    %mutable;

### Constants and enums

C/C++ 常量作为包含适当值的Python对象进行安装。要创建常量，请使用#define，enum或％constant指令。例如


    #define PI 3.14159
    #define VERSION "1.0"

    enum Beverage { ALE, LAGER, STOUT, PILSNER };

    %constant int FOO = 42;
    %constant const char *path = "/usr/local";

对于枚举，请确保枚举的定义实际上出现在头文件或包装文件中.如果你只是在一个SWIG界面上粘贴一个枚举，而不用告诉C编译器，封装代码就不会编译

### Structures

如果你包装一个C结构，它被一个Python类包装起来。这提供了非常自然的界面。例如：

    struct Vector {
        double x,y,z;
    };

使用方法如下：

    >>> v = example.Vector()
    >>> v.x = 3.5
    >>> v.y = 7.2
    >>> print(v.x, v.y, v.z)
    7.8 -4.5 0.0
    >>>

一个结构的const成员是只读的。数据成员也可以使用％immutable伪指令强制为只读。例如：

    struct Foo {
    ...
    %immutable;
    int x;        /* Read-only members */
    char *name;
    %mutable;
    ...
    };

### C++ classes

Python类也包含C ++类。例如，如果你有这个类

    class List {
    public:
    List();
    ~List();
    int  search(char *item);
    void insert(char *item);
    void remove(char *item);
    char *get(int n);
    int  length;
    };

你可以在Python中使用它：

    >>> l = example.List()
    >>> l.insert("Ale")
    >>> l.insert("Stout")
    >>> l.insert("Lager")
    >>> l.get(1)
    'Stout'
    >>> print(l.length)
    3
    >>>

这里是一些简单的用法 以后再总结其他的高级用法。

