# Python-生成器(1)

## 用生成器创建新的迭代模式

我们要实现一个自定义的迭代模式,让他区别于常见的内建函数(即 range(), reversed())

### 例子1

我们要实现一个新的迭代模式, 产生: 从 start -> stop 间隔 increment 的 浮点数

    def frange(start,stop,increment=0.1):
        x = start
        while x < stop:
            yield x
            x += increment

    f = frange(0,1,0.2)
    print(f)
    for i in f:
        print(i)
    print(list(frange(1,5,0.5)))

示例输出

    <generator object frange at 0x7f5b0796a048>
    0
    0.2
    0.4
    0.6000000000000001
    0.8
    [1, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5]

对于我们定义的 frange() 这个函数,我们可以使用 for对其进行迭代或者通过其他可以访问迭代对象的元素的函数(例如: list(),sum(),max(),next(),min() 等)

我们 可以看到只要出现了 yield 语句 就会n将其转变成一个生成器。与普通函数不同,生成器只会在响应迭代操作的时候才运行。为了了解底层的机制我们看一下 下面的代码示例

    def countdown(n):
        print("从%d开始"%(n,))
        while n > 0:
            yield n
            n -= 1
        print("Done!")

    x = countdown(3)
    print(x)
    print(next(x))
    print(next(x))
    print(next(x))
    print(next(x))
    print(next(x))

输出示例

    <generator object countdown at 0x7f896c857048>
    从3开始
    3
    2
    1
    Done!
    Traceback (most recent call last):
    File "1.py", line 37, in <module>
        print(next(x))
    StopIteration

## 实现迭代协议

我们正在构建一个自定义对象, 希望他可以支持迭代操作, 但也希望能有一种简单的方式来实现迭代协议

### 解决方案

我们可以通过 __iter__() 方法来实现生成函数，下面我们来实现迭代器以深度优先搜索的方式遍历一颗树

    class Node(object):
        def __init__(self, vale):
            self.vale = vale
            self._children = []

        def __repr__(self):
            return f'Node({self.vale})'

        def add_child(self, node):
            self._children.append(node)

        def __iter__(self):
            return iter(self._children)

        def deepin_first(self):
            yield self
            for c in self:
                yield from c.deepin_first()


    if __name__ == "__main__":
        root = Node(0)
        child1 = Node(1)
        child2 = Node(2)
        root.add_child(child1)
        root.add_child(child2)
        child1.add_child(Node(3))
        child1.add_child(Node(4))
        child2.add_child(Node(5))

        for ch in root.deepin_first():
            print(ch,end=', ')
### 输出

    Node(0), Node(1), Node(3), Node(4), Node(2), Node(5),

### 思考

我们知道 Python 迭代协议要求 \_\_iter\_\_() 返回一个特殊的迭代对象，该对象必须实现 \_\_next\_\_()方法，并使用 StopIteration 异常来通知迭代的完成, 但是这实现实在是太麻烦了。


