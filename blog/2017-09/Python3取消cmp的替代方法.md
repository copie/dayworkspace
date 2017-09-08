# Python3取消cmp的替代方法

    >>> cmp(12,3)
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    NameError: name 'cmp' is not defined

今天我发现Python3 的 cmp内置方法不可以用来，发现原来Python3 取消了魔法函数__cmp__(),为了替代原来的cmp官方提供了新的方法下面就是一些简单的示例

    operator.lt(a, b)   
    operator.le(a, b)   
    operator.eq(a, b)   
    operator.ne(a, b)   
    operator.ge(a, b)   
    operator.gt(a, b)
    operator.__lt__(a, b)   
    operator.__le__(a, b)   
    operator.__eq__(a, b)   
    operator.__ne__(a, b)   
    operator.__ge__(a, b)   
    operator.__gt__(a, b)

用来替代 cmp 就是这几个函数代表一下意思

    lt(a, b) 相当于 a < b
    le(a,b) 相当于 a <= b
    eq(a,b) 相当于 a == b
    ne(a,b) 相当于 a != b
    gt(a,b) 相当于 a > b
    ge(a, b)相当于 a>= b

##　用法示例

__it__ 需要 self 和 other 两个参数，需要 return self 是否小于 other：

    class Point(object):
    ...
    def __lt__(self, other):
        return ((self.x < other.x) and (self.y < other.y))

如果你有一下情况

    p1 = Point(1, 2)
    p2 = Point(3, 4)

    p1 < p2

他就相当于

    p1.__lt__(p2)

如果你想用 functools.total.ordering 装饰器如下所示：

     @total_ordering
     class stu:
         def __init__(self,a,b):
            self.a=a
            self.b=b
         def __eq__(self,other):
             return self.b==other.b
         def __lt__(self,other):
             return self.b<other.b
---

    In [30]: x=stu(1,0)

    In [31]: y=stu(1,100)

    In [32]: x==y
    Out[32]: False

    In [33]: x<y
    Out[33]: True

    In [34]: x>y
    Out[34]: False

    In [35]: x<=y
    Out[35]: True

    In [36]: x>=y
    Out[36]: False

---

在 queue.PriorityQueue 中使用的a简单示例：

from queue import PriorityQueue


    class myjob(object):
        def __init__(self, a, b):
            self.a = a
            self.b = b

        def __lt__(self, other):
            return self.b > other.b

        def __repr__(self):
            return ' '.join(map(str, [self.a, self.b]))


    eqw = PriorityQueue()
    eqw.put(myjob(1, 9))
    eqw.put(myjob(1, 8))
    eqw.put(myjob(1, 10))

    while not eqw.empty():
        print(eqw.get())


## functools.total.ordering 装饰器的解释

这个装饰器装饰的类必须提供__lt__(), __le__(), __gt__(), or __ge__()中的任意一个和__eq__().
    
它会把其他几个比较函数补全

例子:

    @total_ordering
    class Student:
        def _is_valid_operand(self, other):
            return (hasattr(other, "lastname") and
                    hasattr(other, "firstname"))
        def __eq__(self, other):
            if not self._is_valid_operand(other):
                return NotImplemented
            return ((self.lastname.lower(), self.firstname.lower()) ==
                    (other.lastname.lower(), other.firstname.lower()))
        def __lt__(self, other):
            if not self._is_valid_operand(other):
                return NotImplemented
            return ((self.lastname.lower(), self.firstname.lower()) <
                    (other.lastname.lower(), other.firstname.lower()))

**注意**虽然这个装饰器使得容易创建行为良好的完全有序类型，但是以导致比较方法的较慢执行和更复杂的堆栈跟踪为代价的。如果性能基准测试表明这是给定应用程序的瓶颈，则实施所有六种丰富的比较方法可能提供一个容易的速度提升。

python3.4 实现 NotImplemented 现在支持从未被识别的类型的底层比较函数。

## hasattr(object, name)
判断一个对象里面是否有name属性或者name方法，返回BOOL值，有name特性返回True， 否则返回False。







