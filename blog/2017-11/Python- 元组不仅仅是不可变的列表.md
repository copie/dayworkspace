# Python-元组不仅仅是不可变的列表
 
我们最开始学习 Python 的时候我们都学到了"元组就是一个不可以变的一 (1920x1080 60fps)个列表" 这个时候我们就会有一个疑问了问什么要有设计元组这个东西。这个东西那么鸡肋是不。其实这个说法没有完全的概括元组的特点。除了做为不可变的列表以外它还可以用于没有字段名的记录。

## 元组与记录

元组其实就是对数据的记录: 元组中的每个元素都存放了记录中的一个字段数据，外加这个字段的位置。这个位置信息给数据赋予了意义。
比如下面这个用法

    In [1]: name, age, height, weight =("copie",21,170,100)

    In [2]: name
    Out[2]: 'copie'

    In [3]: age
    Out[3]: 21

    In [4]: height
    Out[4]: 170

    In [5]: weight
    Out[5]: 100

比如这个用法,位置信息是十分重要的
具名元组让这种使用变的更加的方便下面这个例子

    n [6]: from collections import namedtuple

    In [8]: man = namedtuple("man",['name', 'age', 'height', 'weight'])

    In [9]: man("copie", 21, 170,100)
    Out[9]: man(name='copie', age=21, height=170, weight=100)

    In [10]: y = man("copie", 21, 170,100)

    In [11]: y
    Out[11]: man(name='copie', age=21, height=170, weight=100)

    In [12]: name, age, height, weight =y

    In [13]: name
    Out[13]: 'copie'

    In [14]: age
    Out[14]: 21

    In [15]: height
    Out[15]: 170

    In [16]: weight
    Out[16]: 100

    In [18]: y._asdict()
    Out[18]: OrderedDict([('name', 'copie'), ('age', 21), ('height', 170), ('weight', 100)])

collections.namedtuple 是一个工厂函数,它可以用来构建一个带字段名的元组和一
个有名字的类——这个带名字的类对调试程序有很大帮助。

除了从普通元组那里继承来的属性之外,具名元组还有一些自己专有的属性。
下面代码中就展示了几个最有用的:_fields 类属性、类方法 _make(iterable) 和实例方法
_asdict()。

    In [2]:  man = namedtuple("man",['name', 'age', 'height', 'weight'])
    In [6]: x = man._make(("copie",21,170,100))

    In [7]: x
    Out[7]: man(name='copie', age=21, height=170, weight=100)

    In [8]: x._asdict()
    Out[8]: OrderedDict([('name', 'copie'), ('age', 21), ('height', 170), ('weight', 100)])

    In [9]: x._fields
    Out[9]: ('name', 'age', 'height', 'weight')

_fields 属性就是一个包含这个类的所有字段名称的元组。

_make() 通过接受一个可迭代对象来生成这个类的一个实例。

_asdict() 把具名元组以 collections.OrderedDict 的形式返回,我们可以利用它
来把元组里的信息友好地呈现出来。

## 元组的拆包

元组拆包可以应用到任何可迭代对象上,唯一的硬性要求是,被可迭代对象中
的元素数量必须要跟接受这些元素的元组的空档数一致。除非我们用 * 来表示忽略
多余的元素。

    name, age, height, weight =("copie",21,170,100)

这个就是 一个简单的拆包
用 * 的比如这个

    In [14]: name, age, *hw =("copie",21,170,100)
    In [15]: hw
    Out[15]: [170, 100]

    In [21]: divmod(34,7)
    Out[21]: (4, 6)

    In [22]: t = divmod(34,7)
    In [23]: t
    Out[23]: (4, 6)
    In [25]: quotient, remainder = divmod(*t)
    In [26]: quotient, remainder
    Out[26]: (0, 4)

简单的应用  os.path.split()
    In [35]: _, filemame = os.path.split("/home/copie/.ssh/id_rsa.pub")

    In [36]: filemame
    Out[36]: 'id_rsa.pub'
在进行拆包的时候,我们不总是对元组里所有的数据都感兴趣,_情况,上面这段代码也展示了它的用法。占位符能帮助处理这种情况






