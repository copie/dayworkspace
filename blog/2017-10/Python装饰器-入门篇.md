# Python 装饰器-入门篇

一般来说 "装饰器"(decorator)是个单参数的函数, 其参数是一个函数，装饰器返回的新函数与经由参数传入的原函数名相同, 但功能更强。框架(例如 WEB 框架)经常通过装饰器把用户所编写的函数集成进来。

由于装饰器模式非常有用, 所以 Python 提供了原生支持。 在Python 语言中，函数与方法都可以用装饰器来装饰。此外还有"类装饰器"(class decorator),他也是一个单参数的函数，其参数是一个类，又这种装饰器所返回的新类的名称与原类相同，但功能更多。有时可以通过类装饰器来实现继承。

例如 我在这篇 [blog](https://copie.cn/index.php/archives/Python3%E5%8F%96%E6%B6%88cmp%E7%9A%84%E6%9B%BF%E4%BB%A3%E6%96%B9%E6%B3%95-1.html)

说到的**functools.total.ordering 装饰器**

这个装饰器装饰的类必须提供__lt__(), __le__(), __gt__(), or __ge__()中的任意一个和__eq__().

它会把其他几个比较函数补全

会帮我们理解装饰器到底可以干些什么。

## 具体例子

假如我们有一个输出"Hello world!"的函数

    def hello():
        print("Hello World!")

然后我们要加需求了要在 "Hello world!" 之前添加 "博主最帅"，之后添加输出 "么么哒" 还有就是不能修改原函数

我们这里要新写一个函数

    def say_shuai(fun):
        def wrapper():
            print("博主最帅")
            fun()
            print("么么哒")
            return fun
        return wrapper

    hello = say_shuai(hello)

添加上面的代码然后就实现了我们的需求。由于 Pyhon 原生支持装饰器 我们可以 通过语法糖 "@" 来实现 "hello = say_shuai(hello)"比如下面的例子

    def say_shuai(fun):
        def wrapper():
            print("博主最帅")
            fun()
            print("么么哒")
            return fun
        return wrapper

    @say_shuai
    def hello():
        print("Hello World!")

实现我们同样的需求

下面问题来了如果我们的原函数是带有参数的呢

    def ji_suan(fun):
        def wrapper(a,b):
            # 分别计算乘除加减以后的和
            #  fun(fun(fun(fun(a,b),a*b),a/b),a-b)
            return fun(a,b)+a*b+a/b+a-b
        return wrapper

    @ji_suan
    def add(a,b):
        return a+b

下面 还有一个就是我们的装饰器函数也有参数我们要怎么弄

    def ji_suan(ch):
        def suan(fun):
            def a_add_b(a, b):
                return a + b + fun(a, b)

            def a_sub_b(a, b):
                return a - b - fun(a, b)
            if ch == '+':
                return a_add_b
            else:
                return a_sub_b
        return suan


    @ji_suan("+")
    def hello(a, b):
        return a * b


    @ji_suan("-")
    def hi(a, b):
        return a / b

类似这样就可以实现相应的功能了
今天就先写这些 快要熄灯了
