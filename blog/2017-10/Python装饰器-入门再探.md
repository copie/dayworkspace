# Python装饰器-入门再探

## 装饰器的副作用

上面的 blog 我们明白了 有一个新的对象替代原来的对象虽然他们的名字是一样的。但是他的元属性就不见了。看一下下面的例子。

    def log(fun):
        def wrapper():
            print("运行-> ",fun.__name__)
            fun()
            print(fun.__name__,"结束")
            return fun
        return wrapper
    @log
    def foo():
        print("hello 我是主要的代码")


    foo()
    print(foo.__name__)

### **输出:**

    运行->  foo
    hello 我是主要的代码
    foo 结束
    wrapper

在这里 foo.\_\_name\_\_ 不是 'foo' 了 变成 'wrapper'

修改成 下面的样子 就可以克服副作用

    from functools import wraps
    def log(fun):
        @wraps(fun)
        def wrapper():
            print("运行-> ",fun.__name__)
            fun()
            print(fun.__name__,"结束")
            return fun
        return wrapper
    @log
    def foo():
        print("hello 我是主要的代码")


    foo()
    print(foo.__name__)

### 输出

    运行->  foo
    hello 我是主要的代码
    foo 结束
    foo

## 内部装饰器

在Python中有三个内置的装饰器, 都是跟class相关的:

1. staticmethod
2. classmethod
3. property

---

1. staticmethod 是类静态方法, 其跟成员方法的区别是没有 self 参数，并且可以在类不进行实例化的情况下调用

2. classmethod 与成员方法的区别在于所接收的第一个参数不是 self （类实例的指针），而是cls（当前类的具体类型）

3. property 是属性的意思，表示可以通过通过类实例直接访问的信息

