# 深刻理解Python中的元类(metaclass)

读了这篇文章收获很大特意去翻译的原文去看了一下。我们知道 Python3 和 Python2 还是有一些改变的所以在这篇文章里有些例子已经不能用了。 所以我会在这里保证所有的例子都能正确的运行在 Python3.6.3 上。转载的同时让自己更好的理解。

## 译注

这是一篇在[Stack overflow](https://stackoverflow.com/questions/100003/what-is-a-metaclass-in-python)上很热的帖子。提问者自称已经掌握了有关Python OOP编程中的各种概念，但始终觉得元类(metaclass)难以理解。他知道这肯定和自省有关，但仍然觉得不太明白，希望大家可以给出一些实际的例子和代码片段以帮助理解，以及在什么情况下需要进行元编程。于是e-satis同学给出了神一般的回复，该回复获得了985点的赞同点数，更有人评论说这段回复应该加入到Python的官方文档中去。而e-satis同学本人在Stack Overflow中的声望积分也高达64271分。以下就是这篇精彩的回复（提示：非常长）

## 类也是对象

在理解元类之前，你需要先掌握Python中的类。Python中类的概念借鉴于Smalltalk，这显得有些奇特。在大多数编程语言中，类就是一组用来描述如何生成一个对象的代码段。在Python中这一点仍然成立：

    In [3]: class ObjectCreator():
    ...:     pass
    ...:

    In [4]: my_object = ObjectCreator()

    In [5]: print(my_object)
    <__main__.ObjectCreator object at 0x0000000004C432E8>

但是，Python中的类还远不止如此。类同样也是一种对象。是的，没错，就是对象。只要你使用关键字class，Python解释器在执行的时候就会创建一个OBJECT。下面的代码段：


    In [3]: class ObjectCreator():
    ...:     pass
    ...:

将在内存中创建一个对象，名字就是ObjectCreator。 **这个对象（类）自身拥有创建对象（类实例）的能力，而这就是为什么它是一个类的原因**。但是，它的本质仍然是一个对象，于是乎你可以对它做如下的操作：

1. 你可以将它赋值给一个变量
2. 你可以拷贝它
3. 你可以为它增加属性
4. 你可以将它作为函数参数进行传递

下面是示例：


In [6]: print(ObjectCreator)        # 你可以打印一个类，因为它其实也是一个对象
<class '__main__.ObjectCreator'>

In [7]: def echo(o):
   ...:     print(o)
   ...:

In [8]: echo(ObjectCreator)     # 你可以将类做为参数传给函数
<class '__main__.ObjectCreator'>

In [10]: hasattr(ObjectCreator, 'new_attribute')
Out[10]: False

In [11]: ObjectCreator.new_attribute = 'foo'        #  你可以为类增加属性

In [12]: hasattr(ObjectCreator, 'new_attribute')
Out[12]: True

In [13]: ObjectCreator.new_attribute
Out[13]: 'foo'

In [14]: ObjectCreatorMirror = ObjectCreator        # 你可以将类赋值给一个变量

In [15]: ObjectCreatorMirror()
Out[15]: <__main__.ObjectCreator at 0x4c36240>


## 动态地创建类

因为类也是对象，你可以在运行时动态的创建它们，就像其他任何对象一样。首先，你可以在函数中创建类，使用class关键字即可。

    In [17]: def choose_class(name):
        ...:     if name == 'foo':
        ...:         class Foo:
        ...:             pass
        ...:         return Foo
        ...:     else:
        ...:        class Bar:
        ...:            pass
        ...:        return Bar
        ...:

    In [18]: MyClass = choose_class("foo")

    In [19]: print(MyClass)
    <class '__main__.choose_class.<locals>.Foo'>

    In [21]: print(MyClass())
    <__main__.choose_class.<locals>.Foo object at 0x0000000005102048>

    In [22]:

但这还不够动态，因为你仍然需要自己编写整个类的代码。由于类也是对象，所以它们必须是通过什么东西来生成的才对。当你使用class关键字时，Python解释器自动创建这个对象。但就和Python中的大多数事情一样，Python仍然提供给你手动处理的方法。还记得内建函数type吗？这个古老但强大的函数能够让你知道一个对象的类型是什么，就像这样：


    In [23]: print(type(1))
    <class 'int'>

    In [24]: print(type("1"))
    <class 'str'>

    In [25]: print(type(ObjectCreator))
    <class 'type'>
    
    In [33]: print(type(ObjectCreator()))
    <class '__main__.ObjectCreator'>

这里，type有一种完全不同的能力，它也能动态的创建类。type可以接受一个类的描述作为参数，然后返回一个类。（我知道，根据传入参数的不同，同一个函数拥有两种完全不同的用法是一件很傻的事情，但这在Python中是为了保持向后兼容性）


type可以像这样工作：

    type(类名, 父类的元组（针对继承的情况，可以为空），包含属性的字典（名称和值）)

比如下面的代码：

    In [34]: class MyShinyClass:
        ...:     pass
        ...:

可以手动像这样创建：

