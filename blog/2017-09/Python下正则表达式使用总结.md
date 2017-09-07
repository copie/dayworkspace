# Python 下正则表达式使用总结

## Python 下常用的 re 方法

### compile(pattern,flags = 0)

可以通过指定flags 值修改表达式的行为。值可以是任何以下变量， 组合使用 OR ( | 运算符)

使用任何可选的标记来编译正则表达式的模式，然后返回一个正则表达式对象(\<class '_sre.SRE_Pattern'\>)

表达式在单个程序中多次使用时， 使用re.compile() 和保存生成的正则表达式对象重用效率更高。

        >>> x=re.compile("foo")
        >>> type(x)
        <class '_sre.SRE_Pattern'>

还可以用一下方式写注释

        a = re.compile(r"""\d +  # the integral part
                   \.    # the decimal point
                   \d *  # some fractional digits""", re.X)

等同与

        b = re.compile(r"\d+\.\d*")

好用看的不止一点
其他的请看[官方文档](http://python.usyiyi.cn/translate/python_352/library/re.html#module-re)

### 匹配对象以及 group() 和 groups() 方法

匹配对象，是成功调用match()或者search()返回的对象(\<class '_sre.SRE_Match'\>)这里可以发现match() 和 search()返回的是一个相同的类的对象。

这个对象有两个主要方法 group()和groups()。

**group()** 要么返回整个匹配对象，要么根据要求返回特定的子组**比如:group(1)就是返回第一个子组**

**groups()** 仅返回仅有一个或者全部子组的元组。没有满足条件但是group()可以显示那个成功匹配。这时groups()的返回值是空元组。

### 使用 match() 方法匹配字符串

match() 函数试图从字符串的起始位置对模式进行匹配如果匹配成功就返回匹配对象如果失败就返回None，匹配对象的group方法就能够用来显示成功的匹配。

        >>> m = re.match('foo','foohhhhhhhhhh')
        >>> if m is not None : m.group()
        ...
        'foo'

不能匹配的

        >>> m = re.match('foo','xfoohhhhhhhhhh')
        >>> if m is not None : m.group()
        ... 
什么都有。
### 使用 search() 在一个字符串中查找模式(搜索和匹配的对比)

search() 的工作方式和 match() 完全相同，不同的地方在于search()不去强调匹配一定要在字符串的开头。以下是一个例子。

        >>> m = re.search('foo','xfoohhhhhhhhhh')
        >>> if m is not None : m.group()
        ... 
        'foo'

### findall() 和 finditer() 查找每一次出现的位置

从名字就可以看出来是在一个字符串里面查找所有的匹配并返回一个列表。如果没有匹配就返回一个空列表。

        >>> m = re.findall('foo','xfoohhhfoohhhfoohhhh')
        >>> m
        ['foo', 'foo', 'foo']
        >>> type(m[0])
        <class 'str'>
        >>> type(m)
        <class 'list'>

下面一个finditer()的示例

        >>> m = re.finditer('(foo)','xfoohhhfoohhhfoohhhh')
        >>> m
        <callable_iterator object at 0x7fa659873518>
        >>> next(m)
        <_sre.SRE_Match object; span=(1, 4), match='foo'>
        >>> next(m)
        <_sre.SRE_Match object; span=(7, 10), match='foo'>
        >>> next(m)
        <_sre.SRE_Match object; span=(13, 16), match='foo'>
        >>> next(m)
        Traceback (most recent call last):
        File "<stdin>", line 1, in <module>
        StopIteration

不难看出finditer()的返回值是一个迭代器。**与findall()相比更加节省内存**
### 使用 sub() 和subn()搜索和替换

这里说的替换就是一个正则替换以下是一个例子：

        >>> re.sub('X',"mm",'X/SSSS/X')
        'mm/SSSS/mm'

        >>> re.subn('X',"mm",'X/SSSS/X')
        ('mm/SSSS/mm', 2)

这里不难看出sub()的用法和subn()的区别。
subn() 返回一个元组包含替换了几个

        >>> re.subn('[aeiou]',"X",'aeiouxyz')
        ('XXXXXxyz', 5)

        >>> re.subn(r'(\d+)/(\d+)/(\d+)',r'\2/\1/\3','7/09/2017')
        ('09/7/2017', 1)

这里是两个比较高级的用法。

### 在限定模式上使用 split()分隔字符串

这里我们很容易就会想到 str.split() 这么一个函数 re 的split()是正则表达式的分隔

        >>> re.split("/","09/7/2017")
        ['09', '7', '2017']

复杂的方法都是上面的组合了。


## 练习的正则表达式

1. 获取篇文本里面所有链接中的域名

        ((?:http[s]?\/\/:)?(www\.)?(\w+(\.\w+)*\.)(com|cn|net))


这里总结了一些常用的方法其他的以后总结