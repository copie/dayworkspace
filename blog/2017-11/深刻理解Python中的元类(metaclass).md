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

    In [8]: MyShinyClass = type('MyShinyClass', (), {})

    In [9]: print(MyShinyClass)

    In [11]: print(MyShinyClass())
    <__main__.MyShinyClass object at 0x0000000006051E48>

你会发现我们使用“MyShinyClass”作为类名，并且也可以把它当做一个变量来作为类的引用。类和变量是不同的，这里没有任何理由把事情弄的复杂。

type 接受一个字典来为类定义属性，因此


    In [12]: class Foo:
        ...:     bar = True
        ...:

可以翻译为：


    In [13]: Foo = type("Foo", (), {'bar':True})

并且可以将Foo当成一个普通的类一样使用：

    In [14]: print(Foo)
    <class '__main__.Foo'>

    In [15]: print(Foo.bar)
    True

    In [16]: f = Foo()

    In [17]: print(f)
    <__main__.Foo object at 0x000000000672A518>

    In [18]: print(f.bar)
    True

当然，你可以向这个类继承，所以，如下的代码：


    In [19]: class FooChild(Foo):
        ...:     pass
        ...:

就可以写成：

    In [21]: FooChild = type("FOOChild", (Foo, ), {})

    In [22]: print(FooChild)
    <class '__main__.FOOChild'>

    In [23]: print(FooChild.bar)
    True

最终你会希望为你的类增加方法。只需要定义一个有着恰当签名的函数并将其作为属性赋值就可以了。


    In [24]: def echo_bar(self):
        ...:     print(self.bar)
        ...:

    In [25]: FooChild = type("FooChild", (Foo, ), {'echo_bar' : echo_bar})

    In [27]: hasattr(Foo, "echo_bar")
    Out[27]: False

    In [28]: hasattr(FooChild, "echo_bar")
    Out[28]: True

你可以看到，在Python中，类也是对象，你可以动态的创建类。这就是当你使用关键字class时Python在幕后做的事情，而这就是通过元类来实现的。

## 到底什么是元类（终于到主题了）

元类就是用来创建类的“东西”。你创建类就是为了创建类的实例对象，不是吗？但是我们已经学习到了Python中的类也是对象。好吧，元类就是用来创建这些类（对象）的，元类就是类的类，你可以这样理解 为：

    MyClass = MetaClass()
    MyObject = MyClass()

你已经看到了type可以让你像这样做：

    MyClass = type('MyClass', (), {})

这是因为函数type实际上是一个元类。type就是Python在背后用来创建所有类的元类。现在你想知道那为什么type会全部采用小写形式而不是Type呢？好吧，我猜这是为了和str保持一致性，str是用来创建字符串对象的类，而int是用来创建整数对象的类。type就是创建类对象的类。你可以通过检查__class__属性来看到这一点。Python中所有的东西，注意，我是指所有的东西——都是对象。这包括整数、字符串、函数以及类。它们全部都是对象，而且它们都是从一个类创建而来。


    In [32]: age = 35

    In [33]: age.__class__
    Out[33]: int

    In [34]: name = "bbb"

    In [35]: name.__class__
    Out[35]: str

    In [36]: def foo():pass

    In [37]: foo.__class__
    Out[37]: function

    In [38]: class Bar: pass

    In [39]: b = Bar()

    In [40]: b.__class__
    Out[40]: __main__.Bar

现在，对于任何一个__class__的__class__属性又是什么呢？


    In [50]: age.__class__.__class__
    Out[50]: type

    In [51]: name.__class__.__class__
    Out[51]: type

    In [52]: foo.__class__.__class__
    Out[52]: type

    In [53]: b.__class__.__class__
    Out[53]: type

因此，元类就是创建类这种对象的东西。如果你喜欢的话，可以把元类称为“类工厂”（不要和工厂类搞混了:D） type就是Python的内建元类，当然了，你也可以创建自己的元类。

## __metaclass__属性

你可以在写一个类的时候为其添加__metaclass__属性, 定义了__metaclass__就定义了这个类的元类。

    class Foo(object):   # Python2
        __metaclass__ = something…


    class Foo(metaclass=something):   # Python3
        pass

在[官方文档](https://docs.python.org/3/library/2to3.html?highlight=metaclass#2to3fixer-metaclass)里面十分清楚的写了

    metaclass
    Converts the old metaclass syntax (__metaclass__ = Meta in the class body) to the new (class X(metaclass=Meta)).    

虽然写法不同原理是一样的。

例如：当我们写如下代码时 :

    class Foo(Bar):
        pass

在该类并定义的时候，它还没有在内存中生成，直到它被调用。Python做了如下的操作：

1. Foo中有__metaclass__这个属性吗？如果是，Python会在内存中通过__metaclass__创建一个名字为Foo的类对象（我说的是类对象，请紧跟我的思路）。

2. 如果Python没有找到__metaclass__，它会继续在父类中寻找__metaclass__属性，并尝试做和前面同样的操作。

3. 如果Python在任何父类中都找不到__metaclass__，它就会在模块层次中去寻找__metaclass__，并尝试做同样的操作。

4. 如果还是找不到__metaclass__,Python就会用内置的type来创建这个类对象。

现在的问题就是，你可以在__metaclass__中放置些什么代码呢？

答案就是：可以创建一个类的东西。那么什么可以用来创建一个类呢？type，或者任何使用到type或者子类化type的东西都可以。

## 自定义元类

元类的主要目的就是为了当创建类时能够自动地改变类。通常，你会为API做这样的事情，你希望可以创建符合当前上下文的类。假想一个很傻的例子，你决定在你的模块里所有的类的属性都应该是大写形式。有好几种方法可以办到，但其中一种就是通过设定__metaclass__。采用这种方法，这个模块中的所有类都会通过这个元类来创建，我们只需要告诉元类把所有的属性都改成大写形式就万事大吉了。

__metaclass__实际上可以被任意调用，它并不需要是一个正式的类。所以，我们这里就先以一个简单的函数作为例子开始。

    # 元类会自动将你通常传给‘type’的参数作为自己的参数传入
    def upper_attr(future_class_name, future_class_parents, future_class_attr):
        '''返回一个类对象，将属性都转为大写形式'''
        # 选择所有不以'__'开头的属性
        attrs = ((name, value) for name, value in future_class_attr.items()
                if not name.startswith('__'))
        # 将它们转为大写形式
        uppercase_attr = {name.upper(): value for name, value in attrs}
        # 通过'type'来做类对象的创建
        return type(future_class_name, future_class_parents, uppercase_attr)


    class Foo(metaclass = upper_attr):
        bar = "bip"

测试如下：

    In [25]: print(hasattr(Foo, "bar"))
    False

    In [26]: print(hasattr(Foo, "BAR"))
    True

    In [27]: f = Foo()

    In [28]: print(f.BAR)
    bip

现在让我们再做一次，这一次用一个真正的class来当做元类。

    # 请记住，'type'实际上是一个类，就像'str'和'int'一样。所以，你可以从type继承
    # __new__ 是在__init__之前被调用的特殊方法，__new__是用来创建对象并返回之的方法，__new_()是一个类方法
    # 而__init__只是用来将传入的参数初始化给对象，它是在对象创建之后执行的方法。
    # 你很少用到__new__，除非你希望能够控制对象的创建。这里，创建的对象是类，我们希望能够自定义它，所以我们这里改写__new__
    # 如果你希望的话，你也可以在__init__中做些事情。还有一些高级的用法会涉及到改写__call__特殊方法，但是我们这里不用，下面我们可以单独的讨论这个使用

    class UpperAttrMetaClass(type):
        def __new__(upperattr_metaclass, future_class_name, future_class_parents, future_class_attr):
            # 选择所有不以'__'开头的属性
            attrs = ((name, value) for name, value in future_class_attr.items()
                    if not name.startswith('__'))
            # 将它们转为大写形式
            uppercase_attr = {name.upper(): value for name, value in attrs}
            # 通过'type'来做类对象的创建
            # 返回一个对象，但同时这个对象是一个类
            return type(future_class_name, future_class_parents, uppercase_attr)


    class Foo(metaclass=UpperAttrMetaClass):
        bar = "bip"

测试如下：

    In [6]: print(hasattr(Foo,"bar"))
    False

    In [7]: print(hasattr(Foo,"BAR"))
    True

    In [8]: f = Foo()

    In [9]: f.BAR
    Out[9]: 'bip'

但是，这种方式其实不是OOP。我们直接调用了type，而且我们没有改写父类的__new__方法。现在让我们这样去处理:

    class UpperAttrMetaClass(type):
        def __new__(upperattr_metaclass, future_class_name, future_class_parents, future_class_attr):
            # 选择所有不以'__'开头的属性
            attrs = ((name, value) for name, value in future_class_attr.items()
                    if not name.startswith('__'))
            # 将它们转为大写形式
            uppercase_attr = {name.upper(): value for name, value in attrs}
            # 通过'type'来做类对象的创建
            # 返回一个对象，但同时这个对象是一个类
            # 复用type.__new__方法
            # 这就是基本的OOP编程，没什么魔法。由于type是元类也就是类，因此它本身也是通过__new__方法生成其实例，只不过这个实例是一个类.
            return  type.__new__(upperattr_metaclass, future_class_name, future_class_parents, uppercase_attr)

    class Foo(metaclass=UpperAttrMetaClass):
        bar = "bip"

测试如下：

    In [5]: hasattr(Foo,"bar")
    Out[5]: False

    In [6]: hasattr(Foo,"BAR")
    Out[6]: True

    In [7]: f = Foo()

    In [8]: f.BAR
    Out[8]: 'bip'

你可能已经注意到了有个额外的参数upperattr_metaclass，这并没有什么特别的。类方法的第一个参数总是表示当前的实例，就像在普通的类方法中的self参数一样。当然了，为了清晰起见，这里的名字我起的比较长。但是就像self一样，所有的参数都有它们的传统名称。因此，在真实的产品代码中一个元类应该是像这样的：

    class UpperAttrMetaClass(type):
        def __new__(cls, name, bases, dct):
            attrs = ((name, value) for name, value in dct.items()
                    if not name.startswith('__'))
            uppercase_attr = {name.upper(): value for name, value in attrs}
            return type.__new__(cls, name, bases, uppercase_attr)


    class Foo(metaclass=UpperAttrMetaClass):
        bar = "bip"

如果使用super方法的话，我们还可以使它变得更清晰一些。

    class UpperAttrMetaClass(type):
        def __new__(cls, name, bases, dct):
            attrs = ((name, value) for name, value in dct.items()
                    if not name.startswith('__'))
            uppercase_attr = {name.upper(): value for name, value in attrs}
            return super(UpperAttrMetaClass,cls).__new__(cls, name, bases, uppercase_attr)


    class Foo(metaclass=UpperAttrMetaClass):
        bar = "bip"
