# Python nonlocal 声明

看这篇 blog 的时候假定你已经对于[Python-变量作用域规则](https://copie.cn/index.php/archives/Python-%E5%8F%98%E9%87%8F%E4%BD%9C%E7%94%A8%E5%9F%9F%E8%A7%84%E5%88%99.html)和[Python 闭包](https://copie.cn/index.php/archives/Python-%E9%97%AD%E5%8C%85.html)里面所说的知识有学习.


我们在 [Python 闭包](https://copie.cn/index.php/archives/Python-%E9%97%AD%E5%8C%85.html) 实现的 make_averager 函数的方法效率不高.在代码中所有的值都存储在历史数列中然后每次调用 average 时使用 sum 求和. 更好的实现是,只储存目前的总值和元素的个数,然后使用这两个数计算均值.

代码段一 中的实现有缺陷,只是为了阐明观点.你可以尝试看看缺陷在什么地方.

**代码段一: 计算移动平均值的高阶函数,不保存所有历史值,但有缺陷**

    def make_averager():
        count = 0
        total = 0
        def average(new_value):
            count += 1
            total += new_value
            return total/count
        return average

尝试使用代码段一中定义的函数,会得到如下的结果:

    In [4]: avg = make_averager()

    In [5]: avg(10)
    ---------------------------------------------------------------------------
    UnboundLocalError                         Traceback (most recent call last)
    <ipython-input-5-ace390caaa2e> in <module>()
    ----> 1 avg(10)

    ~/Desktop/test.py in average(new_value)
        3     total = 0
        4     def average(new_value):
    ----> 5         count += 1
        6         total += new_value
        7         return total/count

    UnboundLocalError: local variable 'count' referenced before assignment

问题是,当 count 是数字或者任何不可变类型时,count += 1 语法的作用其实与 count = count + 1 一样.因此我们在 averager 的定义体中为 count 赋值了,会把count变成局部变量. total 变量也会受到这个问题的影响.

我们没有在 [Python 闭包](https://copie.cn/index.php/archives/Python-%E9%97%AD%E5%8C%85.html) 这个里面遇到因为我们没有给 series 赋值,我们只是调用了 series.append, 并把他传给 sum 和 len. 也就是说我们利用了列表是可变对象这一事实.

但对于数字,字符串,元组等不可变类型来说,只能读取,不能更新.如果尝试从新绑定,例如 count　= count + 1,其会隐式的创建局部变量　count, 这样 count 就不是自由变量了, 因此不会保存在闭包中．

为了解决这个问题, Python3 引入了 nonlocal 声明. 它的作用是把变量标记为自由变量, 即使在函数中为变量赋予新值了, 也会变成自由变量. 如果为 nonlocal 声明的变量赋予新值, 闭包中保存的绑定会更新. 最新版的　make_averager 的正确实现如代码段二所示:

**代码段二: 计算移动平均值, 不保存所有历史(使用　nonlocal 修正)**

    def make_averager():
        count = 0
        total = 0
        def average(new_value):
            nonlocal count,total
            count += 1
            total += new_value
            return total/count
        return average

## 如何解决 Python2 中没有 nonlocal

在 python2 中没有　nonlocal, 因此需要变通方法, 基本上, 这种处理方式是把内部函数需要修改的变量(如 count 和 total) 储存为可变对象(如字典或简单的实例)的元素或属性,并把那个对象绑定给一个自由变量