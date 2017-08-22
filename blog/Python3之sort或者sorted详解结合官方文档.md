# Python3之sort或者sorted详解结合官方文档

以前，我一直在纠结在 Python 如何多条件的对一个 对象进行排序， Python2 的时候 在sort 中会有一个 cmp 的一个参数 可以像 C++ 一样用 但是Python3 就不行了 官方 去掉了 cmp 虽然 为了兼容 提供了一个函数 functions.cmp_to_key 来实现 相应的功能 总的来说 还是不方便。所以我在这里结合官方文档对sort的使用进行一次总结。完全抛弃旧的写法。

## 旧写法回顾

    l =[[1,3],[2,4]]
    l.sort(cmp=lambda x,y:cmp(y[1],x[1]))
    print l
    >>> [[2, 4], [1, 3]]

这里是一个简单的按照list 中的第二个数字进行排序

当然这不是我们的重点

## Python3 中 sort

1. 用 sorted() 排序 返回 一个新的对象 原对象不变

        >>> sorted([5, 2, 3, 1, 4])
        [1, 2, 3, 4, 5]

2. 还可以用 list.sort() 进行排序 这个排序是会改变原list的 它的返回值是None

        >>> a = [5, 2, 3, 1, 4]
        >>> a.sort()
        >>> a
        [1, 2, 3, 4, 5]

3. 与list.sort() 只可以对 list 进行排序不同 sorted() 可以对 任意的可迭代对象进行排序

        >>> sorted({1: 'D', 2: 'B', 3: 'B', 4: 'E', 5: 'A'})
        [1, 2, 3, 4, 5]

    ----
    
        >>> sorted({1: 'D', 2: 'B', 3: 'B', 5: 'E', 4:'A'}.items())
        [(1, 'D'), (2, 'B'), (3, 'B'), (4, 'A'), (5, 'E')]

## Key Functions

list.sort()和sorted()都有一个**key**参数, 用于指定在进行比较之前对每个列表元素调用的函数。ps: 这一就话不是很好理解， 就是说你按照什么规则进行排序

例如，这是不区分大小写的字符串比较︰

    >>> sorted("This is a test string from Andrew".split(), key=str.lower)
    ['a', 'Andrew', 'from', 'is', 'string', 'test', 'This'] 

参数的值应为接受单个参数并返回键以用于排序目的的函数。这种技术是快速的，因为对于每个输入记录精确地调用一次键功能。

一个常见的模式是使用一些对象的索引作为键对复杂对象进行排序。例如：

    >>> student_tuples = [
    ...     ('john', 'A', 15),
    ...     ('jane', 'B', 12),
    ...     ('dave', 'B', 10),
    ... ]
    >>> sorted(student_tuples, key=lambda student: student[2])   # sort by age
    [('dave', 'B', 10), ('jane', 'B', 12), ('john', 'A', 15)]

相同的技术适用于具有命名属性的对象。例如：

    >>> class Student:
    ...     def __init__(self, name, grade, age):
    ...         self.name = name
    ...         self.grade = grade
    ...         self.age = age
    ...     def __repr__(self):
    ...         return repr((self.name, self.grade, self.age))

---
    >>> student_objects = [
    ...     Student('john', 'A', 15),
    ...     Student('jane', 'B', 12),
    ...     Student('dave', 'B', 10),
    ... ]
    >>> sorted(student_objects, key=lambda student: student.age)   # sort by age
    [('dave', 'B', 10), ('jane', 'B', 12), ('john', 'A', 15)]

## Operator Module Functions

上面显示的键功能模式是非常常见的，所以Python提供了方便的功能，使访问器功能更容易和更快。operator模块具有itemgetter()，attrgetter()和methodcaller()函数。

使用这些函数，上面的例子变得更简单和更快：

    >>> from operator import itemgetter, attrgetter
---

    >>> sorted(student_tuples, key=itemgetter(2))
    [('dave', 'B', 10), ('jane', 'B', 12), ('john', 'A', 15)]

---

    >>> sorted(student_objects, key=attrgetter('age'))
    [('dave', 'B', 10), ('jane', 'B', 12), ('john', 'A', 15)]

操作符模块函数允许多级排序。例如，要按年级，然后按年龄进行排序：

    >>> sorted(student_tuples, key=itemgetter(1,2))
    [('john', 'A', 15), ('dave', 'B', 10), ('jane', 'B', 12)]

---

    >>> sorted(student_objects, key=attrgetter('grade', 'age'))
    [('john', 'A', 15), ('dave', 'B', 10), ('jane', 'B', 12)]

以上 是官方文档给的方法 对于 *要按年级，然后按年龄进行排序* 还可以这么写

    >>> sorted(student_tuples,key=lambda student:(student[1],student[2]))
    [('john', 'A', 15), ('dave', 'B', 10), ('jane', 'B', 12)]

---

    >>> sorted(student_objects,key=lambda student:(student.grade,student.age))
    [('john', 'A', 15), ('dave', 'B', 10), ('jane', 'B', 12)]

这样写看起来更加的好理解一点了

## Ascending and Descending

list.sort()和sorted()接受带有布尔值的reverse参数。这用于标记降序排序。例如，要按照年龄顺序获取学生数据：

    >>> sorted(student_tuples, key=itemgetter(2), reverse=True)
    [('john', 'A', 15), ('jane', 'B', 12), ('dave', 'B', 10)]

---

    >>> sorted(student_objects, key=attrgetter('age'), reverse=True)
    [('john', 'A', 15), ('jane', 'B', 12), ('dave', 'B', 10)]

## 排序稳定性和复杂排序 

排序保证稳定。这意味着当多个记录具有相同的键时，它们的原始顺序被保留。

        >>> data = [('red', 1), ('blue', 1), ('red', 2), ('blue', 2)]
        >>> sorted(data, key=itemgetter(0))
        [('blue', 1), ('blue', 2), ('red', 1), ('red', 2)]

注意blue的两个记录如何保留其原始顺序，以便保证（'blue'， 1） 在（'blue'， 2）之前。

这个奇妙的属性让你在一系列的排序步骤中构建复杂的排序。例如，要按年级降序排序学生数据，然后按年龄升序，请先按年龄排序，然后使用年级：

    >>> s = sorted(student_objects, key=attrgetter('age'))     # sort on secondary key
    >>> sorted(s, key=attrgetter('grade'), reverse=True)       # now sort on primary key, descending
    [('dave', 'B', 10), ('jane', 'B', 12), ('john', 'A', 15)]

对于类似于[[1,6,9],[2,3,4],[3,6,1]]这样每一位都是数字的 我们还可以采取以下的排序方式

    >>> l = [[1,6,9],[2,3,4],[3,6,1]]
    >>> sorted(l,key=lambda x :(x[1],-x[0]))
    [[2, 3, 4], [3, 6, 1], [1, 6, 9]]

Python中使用的**Timsort**算法有效地执行多种排序，因为它可以利用数据集中已存在的任何排序。

有时间去看看 Timsort 算法



