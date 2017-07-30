# python中的栈,队列,列表,集合,元组等数据结构解析

## 列表(list)

一下是列表的常用方法：

1. list.append(x)
    > 将 x 添加到 list 的末尾 相当与 a[len(a):] = [x]

1. list.extend(iterable)
    > 通过一个列表扩展出一个新的列表 相当于 a[len(a):] = iterable
1. list.insert(i, x)
    > 在 i 位置插入一个元素 x a.insert(0,x) 就是将 x 添加到 a 的头部 a.insert(len(a), x) 相当与 a.append(x)
1. list.remove(x)
    > 从list中移除第一个元素 x 如果没有 x 元素 会报错误
1. list.pop([i])
    > 删除列表中指定位置的项目，并返回，如果没有指定就是移除最后一个项目([] 表示该项目是可选的)
1. list.clear()
    > 移除 list 中所有项目 相当于 del a[:]
1. list.index(x[, start[, end]])
    > 返回第一个出现的 x项目的索引(从零开始) 可以指定自己的查找范围，如果没有这样的项目，则引发ValueError
1. list.count(x)
    > 返回 list 中 x 项目的个数
1. list.sort(key=None, reverse=False)
    > 将一个 list 进行排序 可以指定 key 表示键值 由于没有 cmp 参数如需使用详见[sorted](https://docs.python.org/3/library/functions.html#sorted)
1. list.reverse()
    > 将 list 倒置
1. list.copy()
    > 返回一个list的浅层拷贝 相当于a[]

一下是一个使用的例子:

    >>> fruits = ['orange', 'apple', 'pear', 'banana', 'kiwi', 'apple', 'banana']
    >>> fruits.count('apple')
    2
    >>> fruits.count('tangerine')
    0
    >>> fruits.index('banana')
    3
    >>> fruits.index('banana', 4)  # Find next banana starting a position 4
    6
    >>> fruits.reverse()
    >>> fruits
    ['banana', 'apple', 'kiwi', 'banana', 'pear', 'apple', 'orange']
    >>> fruits.append('grape')
    >>> fruits
    ['banana', 'apple', 'kiwi', 'banana', 'pear', 'apple', 'orange', 'grape']
    >>> fruits.sort()
    >>> fruits
    ['apple', 'apple', 'banana', 'banana', 'grape', 'kiwi', 'orange', 'pear']
    >>> fruits.pop()
    'pear'

## 栈(stack)

通过 list 可以轻易的实现 stack 的功能

    >>> stack = [3, 4, 5]
    >>> stack.append(6)
    >>> stack.append(7)
    >>> stack
    [3, 4, 5, 6, 7]
    >>> stack.pop()
    7
    >>> stack
    [3, 4, 5, 6]
    >>> stack.pop()
    6
    >>> stack.pop()
    5
    >>> stack
    [3, 4]

我写的一个 stack 的一个类

    class stack:

        def __init__(self):
            self.my_stack=[]
        def __len__(self):
            return len(self.my_stack)
        def size(self):
            return len(self.my_stack)
        def top(self):
            return self.my_stack[-1]
        def pop(self):
            return self.my_stack.pop()
        def push(self,x):
            return self.my_stack.append(x)
        def empty(self):
            return True if len(self.my_stack) == 0 else False
        def count(self,x):
            return self.my_stack.count(x)
        def __iter__(self):
            return iter(self.my_stack)
        def __repr__(self):
            return str(self.my_stack[::-1]) 
    if __name__ =="__main__":
        my = stack()
        my.push(1)
        print(my.top())
        my.push(2)
        print(my.top())
        my.pop()
        print(my.top())
        my.top()

## 队列(queue)

我们也可以通过 list 来实现队列但是通过 list 实现的复杂度比较高 不建议 官方提供了更好的方法

一下是一个例子:

    >>> from collections import deque
    >>> queue = deque(["Eric", "John", "Michael"])
    >>> queue.append("Terry")           # Terry arrives
    >>> queue.append("Graham")          # Graham arrives
    >>> queue.popleft()                 # The first to arrive now leaves
    'Eric'
    >>> queue.popleft()                 # The second to arrive now leaves
    'John'
    >>> queue                           # Remaining queue in order of arrival
    deque(['Michael', 'Terry', 'Graham'])

其他例子请见[collections.deque](https://docs.python.org/3/library/collections.html#collections.deque)
