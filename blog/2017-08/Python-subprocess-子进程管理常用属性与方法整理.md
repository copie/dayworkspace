# Python-subprocess-子进程管理常用属性与方法整理

subprocess 模块允许你生成新进程，连接到其输入/输出/错误管道，并获取其返回码。此模块旨在替换多个旧的模块和函数:

    os.system
    os.spawn*

## 使用 subprocess 模块

调用 subprocess 的推荐方法是对于它处理的所有场景都是用 run 函数。对于更高级的使用场景，可以直接使用底层的Popen接口。

run 函数是在 Python3.5 中添加的; 如果你需要保留与旧版本的兼容性，请另行参考。

    subprocess.run(args, *, stdin=NOne, input=None, stdout=None, stderr=None, shell=False, timeout=None, check=False)

运行 args 描述的命令。等待命令的完成。然后返回一个 CompletedProcess 实例

下面是一些使用的简单例子:
    
    # 绑定输出和错误
    >>> import subprocess
    >>> pro = subprocess.run(['ls','-l'],stdout=subprocess.PIPE,stderr=subprocess.PIPE,timeout=1)
    >>> print(pro.stdout.decode())
    -rw-rw-r-- 1 copie copie     95 8月  28 21:40 1.cpp
    drwxrwxr-x 9 copie copie   4096 8月  28 00:34 dayworkspace
    drwxr-xr-x 5 copie copie   4096 8月  28 21:59 Desktop
    drwxr-xr-x 2 copie copie   4096 8月  23 13:53 Documents
    drwxr-xr-x 2 copie copie   4096 8月  28 01:03 Downloads
    drwxr-xr-x 3 copie copie   4096 8月  15 15:02 Music
    drwxrwxr-x 2 copie copie   4096 8月  19 08:10 myarchlinux
    drwxrwxr-x 5 copie copie   4096 8月  20 22:35 mypython
    drwxr-xr-x 3 copie copie   4096 8月  25 19:09 Pictures
    drwxrwxrwx 2 copie copie   4096 8月  19 08:41 Public
    -rw-rw-r-- 1 copie copie 525260 8月  15 08:08 sXqufJs.png
    drwxr-xr-x 2 copie copie   4096 8月  15 06:44 Templates
    drwxr-xr-x 2 copie copie   4096 8月  15 06:44 Videos
    >>> pro.returncode
    0
    >>> pro.args
    ['ls', '-l']

---
    1.bc
    1*23+98+(89-87)
    # 输入是文件
    >>>  pro = subprocess.run(['bc'],stdin=open('1.bc','rb'),stdout=subprocess.PIPE,stderr=subprocess.PIPE,timeout=1)
    >>> pro.stdout
    b'123\n'
    # 输入是另一个进程的输出

     >>> pro = subprocess.run(['echo','1*23+98+(89-87)'],stdout=subprocess.PIPE,stderr=subprocess.PIPE,timeout=1)
     >>> pro.stdout
     b'1*23+98+(89-87)\n'
     subprocess.PIPE,timeout=1)
    >>> pro1.stdout
    b'123\n'

---

这是一些简单的使用

上面显示的参数只是一些比较常用的参数，在下面对常用参数的描述。

完整的函数形式很大程度上与Popen构造函数相同 ---- 除 timeout，input， check之外，该函数的所有参数都传给Popen接口

默认情况下，它不捕获标准输出和标准错误。如果想这样做，请为stdout和/或stderr参数传递PIPE ps: 类似于我上面的例子

**timeout** 参数被传递给 Popen.communicate().如果 timeout 超时，子进程将被终止并等待。子进程终止后，将重新引发 TimeoutExpired 异常。

**input** 参数被传给 Popen.communicate(),因此传递到子进程的标准输入。如果使用，它必须是字节序列，或者如果 universal_newlines = True, 则为字符串。用到时，会自动以stdin=PIPE 创建内部的Popen 对象，也可能用不到stdin参数。

如果**check** 为True ，并且进程以非零退出码退出，则会引发 CalledProcessError 异常 。该异常的属性中保存有参数，退出码和标准输出和标准错误(如果他们被捕捉的到)。

例子：

---

    >>> subprocess.run(["ls", "-l"])  # doesn't capture output
    CompletedProcess(args=['ls', '-l'], returncode=0)

    >>> subprocess.run("exit 1", shell=True, check=True)
    Traceback (most recent call last):
    ...
    subprocess.CalledProcessError: Command 'exit 1' returned non-zero exit status 1

    >>> subprocess.run(["ls", "-l", "/dev/null"], stdout=subprocess.PIPE)
    CompletedProcess(args=['ls', '-l', '/dev/null'], returncode=0,
    stdout=b'crw-rw-rw- 1 root root 1, 3 Jan 23 16:23 /dev/null\n')

版本3.5中的新功能。

## **class** subprocess.**CompletedProcess**

从run()返回的值，表示已完成的进程。

**args**

用于启动进程的参数。这可能是一个列表或字符串。

**returncode**

子进程的退出状态。通常，退出状态为0表示它已成功运行。

负值-N表示子进程被信号N终止（仅POSIX）。

**stdout**

从子进程中捕获的标准输出。一个字节序列，如果run()用universal_newlines=True调用则为一个字符串。如果没有捕获标准输出，则为None。

如果使用stderr=subprocess.STDOUT运行进程，stdout和stderr将在此属性中合并，stderr将为None。

**stderr**

从子进程中捕获的标准错误。一个字节序列，如果run()用universal_newlines=True调用则为一个字符串。如果没有捕获标准错误，则为None。

**check_returncode()**

如果returncode不为零，则引发CalledProcessError。

版本3.5中的新功能。

**subprocess.DEVNULL**

可用作Popen的stdin、stdout或stderr参数的特殊值，指示将使用os.devnull这个特殊文件。

版本3.3中的新功能。

**subprocess.PIPE**

可用作Popen的stdin、stdout或stderr参数的特殊值，表示应打开相应标准流的管道。主要用于Popen.communicate()。

**subprocess.STDOUT**

可用作Popen的stderr参数的特殊值，表示标准错误应与标准输出放在同一句柄中。


## **exception** subprocess.**SubprocessError**

此模块中所有其他异常的基类。

版本3.3中的新功能。

## **exception** subprocess.**TimeoutExpired** 和 **exception** subprocess.**CalledProcessError**

SubprocessError子类，当check_call()或check_output()运行的进程返回非零退出状态时引发。
SubprocessError的子类，当等待子进程的timeout超时时引发。

**cmd**

用于产生子进程的命令。

**timeout**

超时（以秒为单位）。

**output**

子进程的输出（如果它由run()或check_output()捕获）。否则，为None。

**stdout**

用于输出的别名，为了与stderr对称。

**stderr**

子进程的标准错误输出（如果它由run()捕获）。否则，为None。

版本3.3中的新功能。
在版本3.5中的更改：添加stdout和stderr属性

## 常用参数

为了支持各种各样的场景，Popen构造函数（和其便利函数）接受大量的可选参数。对于大部分典型的使用场景，这些参数中的许多个可以安全地保持为默认值。最常用到的参数有：

args是所有调用所必需的，应该为一个字符串或一个程序参数序列。通常倾向提供参数序列，因为它允许这个模块来处理任何所需的转义和引用参数（例如，允许文件名中的空格）。如果传递单个字符串，shell必须为True（见下文），否则字符串必须简单地命名要执行的程序而不指定任何参数。

stdin、stdout和stderr分别指定执行程序的标准输入，标准输出和标准错误文件句柄。有效值有PIPE、DEVNULL，一个存在的文件描述器（正整数），一个存在的文件对象和None。PIPE表示应该为子进程创建新的管道。DEVNULL表示将使用特殊文件os.devnull。使用默认设置None，则不会发生重定向；子进程的文件句柄将从父进程继承。此外，stderr可以是STDOUT，表示来自子进程的标准错误数据应该捕获到与stdout相同的文件句柄中。

如果universal_newlines为False，则文件对象stdin、stdout和stderr将以二进制流打开，并且不对行结束进行转换。

如果universal_newlines为True，则这些文件对象将使用locale.getpreferredencoding(False)返回的编码以通用换行符格式的文本流打开。对于stdin，输入中的行结束字符'\n'将转换为默认行分隔符os.linesep。对于stdout和stderr，输出中的所有行结尾将转换为'\n'。有关详细信息，请参阅io.TextIOWrapper类的文档中其构造函数的newline参数为None的时候。

**注意** 文件对象Popen.stdin、Popen.stdout和Popen.stderr的新行属性不会由Popen.communicate()方法更新。

如果shell是True，则将通过shell执行指定的命令。如果你使用Python主要是由于它能提供大多数系统shell不能提供的增强的控制流，并且仍然希望方便地访问其他shell功能，如shell管道、文件名通配符、环境变量扩展和扩展〜到用户的主目录，这会很有用。但是请注意，Python本身提供许多类shell特性的实现（特别是glob、fnmatch、os.walk()、os.path.expandvars()、os.path.expanduser()和shutil）。

版本3.3中的变化：当universal_newlines为True时，类使用locale.getpreferredencoding(False)而不是locale.getpreferredencoding()的编码。有关此更改的详细信息，请参阅io.TextIOWrapper类。

**注意** 在使用shell=True之前，请先阅读安全注意事项部分。

这些选项以及所有其他选项在Popen构造函数文档中有更详细的描述。

更多详细内容 [官方文档](http://usyiyi.cn/translate/python_352/library/subprocess.html#module-subprocess)