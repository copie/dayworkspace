# Python_super_深入理解
这个 Blog 是我年内要写的但是由于各种不可抗力(懒),一直都拖着,然后欠下的帐早晚都是要还的.
:)手动苦笑

我在上一篇文章[多重继承与方法解析](https://copie.cn/index.php/archives/%E5%A4%9A%E9%87%8D%E7%BB%A7%E6%89%BF%E4%B8%8E%E6%96%B9%E6%B3%95%E8%A7%A3%E6%9E%90%E9%A1%BA%E5%BA%8F-1.html)这篇Blog里面说到了,Python的多继承与Python是如何处理如果多继承的话,发生函数名冲突的话保留那些函数.

但是我们还要研究一个问题就是子类是调用父类的方法,所用的 super() 是怎么样的一个形态.单继承很好理解如果是多继承的话super()这个函数他的返回值到底是哪一个父类,如果在父类里面也用super()访问父类的父类会发生什么情况.如果理解这些问题就是这篇Blog的目的.

## super()的简单使用

我们知道在类的继承过程中,如果在子类中重新的定义了某个方法.那么该方法就会覆盖父类中的同名方法,但是用时候我们也会用到父类的方法(比如: super.__init__())看下面的一个例子:

```python
class Animal:
    def __init__(self, name):
        self.name = name
    def greet(self):
        print("Hello, I am " + self.name)

class Dog(Animal):
    def __init__(self,name,age):
        super().__init__(name)
        self.age = age
    def greet(self):
        super().greet()
        print(f"I am {self.age} years old")

def main():
    xiao_bai = Dog("xiao_bai",3)
    xiao_bai.greet()

if __name__ == '__main__':
    main()
```
在上面, Animal 是父类, Dog 是子类,我们在 Dog 类中重定义了 __init__ 和 greet 方法为了能同时实现父类的功能,我们又调用了父类的方法.看一下下面的输出:

```powershell
PS C:\Users\copie\Desktop> python .\test.py
Hello, I am xiao_bai
I am 3 years old
```
## 深入理解 super()

上面都是一些简单的使用,是不是觉得 super 也是很简单的,就是简单的获取了父类,并调用父类的方法,因为上面的例子是一个单继承.如果是多继承的话情况就不一样了,**super 其实和父类没有实质性的关联**

让我们看一下复杂的例子,涉及到多重继承, 代码如下:

```python
class Base():
    def __init__(self):
        print("进入 Base")
        print("离开 Base")

class A(Base):
    def __init__(self):
        print("进入 A")
        super().__init__()
        print("离开 A")

class B(Base):
    def __init__(self):
        print("进入 B")
        super().__init__()
        print("离开 B")

class C(B,A):
    def __init__(self):
        print("进入 C")
        super().__init__()
        print("离开 C")

def main():
    D = C()

if __name__ == '__main__':
    main()
```

上面的代码中, Base 是父类, A, B 继承自 Base, C继承自B,A,他们的继承关系如下:

```
      Base
      /  \
     /    \
    A      B
     \    /
      \  /
        C
```
我们看一下输出

```
PS C:\Users\copie\Desktop> python .\test.py
进入 C
进入 B
进入 A
进入 Base
离开 Base
离开 A
离开 B
离开 C
```
如果你的理解是super() 是***调用父类的方法***,是不是根本不能够理解上面的输出.如果想要理解上面的输出还是要说的就是**super 和父类没有实质性的关联**.下面将会对上面的输出做出一个合理的解释.

## MRO 列表
在[多重继承与方法解析顺序](https://copie.cn/index.php/archives/%E5%A4%9A%E9%87%8D%E7%BB%A7%E6%89%BF%E4%B8%8E%E6%96%B9%E6%B3%95%E8%A7%A3%E6%9E%90%E9%A1%BA%E5%BA%8F-1.html)这篇文章中我们就说到了 __mro__ 这个列表 **方法解析顺序(Method Resolution Order, MRO)**这里就不再多说,理解Python多继承的时候是按照这个列表中的顺序的前后来,进行方法的覆盖的.
这个列表有几个规则:
1.  其顺序会随着子类定义是的书写方式变化而变化
2. 子类永远在父类之前
3. 如果有多个父类,会根据他们在列表中的顺序被检查
4. 前一个类中的方法会覆盖后面类实现的方法

## super 原理

super 的工作原理如下:

``` python
def super(cls, inst):
    mro = inst.__mro__()
    return mro[mro.index(cls) + 1]
```
在Python中的实现肯定不会这么的简单. 但是这个例子还是能够说明super到底干了一些什么
从上面的代码中我们不难看出**super() 的返回值就是实例中方法解析顺序中当前类的下一个**

如果这么解析super的返回和使用的话就很好解释上面看似奇怪的输出了.

## 总结

1. super 和父类没有实质性的关联
2. super 的返回值是实例中方法解析顺序中当前类的下一个
