# Python 闭包

记得我过去的一篇[博客](https://copie.cn/index.php/archives/Python-%E8%A3%85%E9%A5%B0%E5%99%A8-%E5%87%86%E5%A4%87%E7%AF%87.html)里面说道了闭包当时自己的能力不够学的也是云里雾里的.也不敢写太多.经过这一段时间的充电.确实学到了不少.这篇blog是对上篇blog的填坑吧.自己写的blog哭着也要写好.

在博客圈,人们有时会把闭包和匿名函数弄混。这是有历史原因的:在函数内部定义函数不常见,直到开始使用匿名函数才会这样做。而且,只有涉及嵌套函数时才有闭包问题。因此,很多人是同时知道这两个概念的。

其实闭包是指**延伸了作用域的函数** **其中包含函数定义体中引用、但是不在定义体中定义的非全局变量**。(这里说的很明白)

这个概念难以掌握,最好通过示例理解。


假如有个名为 avg 的函数,它的作用是计算不断增加的系列值的均值;例如,整个历史中某个商品的平均收盘价。每天都会增加新价格,因此平均值要考虑至目前为止所有的价格。

代码段一 : 起初,avg 是这样使用的: 

    In [3]: avg(10)
    Out[3]: 10.0

    In [4]: avg(11)
    Out[4]: 10.5

    In [5]: avg(12)
    Out[5]: 11.0

avg 从何而来,它又在哪里保存历史值呢?

初学者可能会像下面那样使用类实现。

代码段二:

    class Averager():
        def __init__(self):
            self.series = []

        def __call__(self, new_value):
            self.series.append(new_value)
            total = sum(self.series)
            return total / len(self.series)

Averager 的实例是可调用对象

代码段三:

    In [2]: avg = Averager()

    In [3]: avg(10)
    Out[3]: 10.0

    In [4]: avg(11)
    Out[4]: 10.5

    In [5]: avg(12)
    Out[5]: 11.0

下面是函数式实现,使用高阶函数 make_averager

averager.py: 计算移动平均值的高阶函数

代码段四:

    def make_averager():
        series = []

        def average(new_value):
            series.append(new_value)
            total = sum(series)
            return total / len(series)
        return average

调用 make_averager 时,返回一个 averager 函数对象。每次调用
averager 时,它会把参数添加到系列值中,然后计算当前平均值,如下所示:
输出

代码段五:

    In [2]: avg = make_averager()

    In [3]: avg(10)
    Out[3]: 10.0

    In [4]: avg(11)
    Out[4]: 10.5

    In [5]: avg(12)
    Out[5]: 11.0

注意,这两个示例有共通之处:调用 Averager() 或 make_averager() 得到一个可调用对象 avg,它会更新历史值,然后计算当前均值。在 代码段二 中,avg 是 Averager 的实例;在 代码段四中是内部函数 averager。不管怎样,我们都只需调用 avg(n),把 n 放入系列值中,然后重新计算均值。

Averager 类的实例 avg 在哪里存储历史值很明显:self.series 实例属性。但是第二个示例中的 avg 函数在哪里寻找 series 呢?

注意,series 是 make_averager 函数的局部变量,因为那个函数的定义体中初始化了 series: series = []。可是,调用 avg(10)时,make_averager 函数已经返回了,而它的本地作用域也一去不复返了。

在 averager 函数中,series 是自由变量(free variable)。这是一个技术术语,指未在本地作用域中绑定的变量,参见下图
![示例图片](https://copie.cn/usr/uploads/2017/12/2288663997.png)

上图:averager 的闭包延伸到那个函数的作用域之外,包含自由变量 series 的绑定

审查返回的 averager 对象,我们发现 Python 在 __code__ 属性(表示编译后的函数定义体)中保存局部变量和自由变量的名称,如示例 代码段六

代码段六:

    In [6]: avg.__code__.co_varnames
    Out[6]: ('new_value', 'total')

    In [7]: avg.__code__.co_freevars
    Out[7]: ('series',)

series 的绑定在返回的 avg 函数的 __closure__ 属性中。avg.__closure__ 中的各个元素对应于avg.__code__.co_freevars 中的一个名称。这些元素是 cell 对象,有个 cell_contents 属性,保存着真正的值。这些属性的值如示例 代码段七:

代码段七

In [7]: avg.__code__.co_freevars
Out[7]: ('series',)
In [8]: avg.__closure__
Out[8]: (<cell at 0x7fad3eb8e1c8: list object at 0x7fad3d84e948>,)
In [10]: avg.__closure__[0].cell_contents
Out[10]: [10, 11, 12]

综上,**闭包是一种函数,它会保留定义函数时存在的自由变量的绑定,这样调用函数时,虽然定义作用域不可用了,但是仍能使用那些绑定。**

**注意,只有嵌套在其他函数中的函数才可能需要处理不在全局作用域中的外部变量。**
