# Python_内(自)省机制

## 什么是内(自)省?

在日常生活中， 内省(introspection) 是一种自我检查的行为。内省是指对某人自身思想，情绪，动机和行为的检查。伟大的哲学家苏格拉底将生命的大部分是时间用于自我的检查，并鼓励他的雅典的朋友也这样做。他甚至对自己做出这样的要求: "未经内省的生命不值得存在。"

在计算及编程中，内省是指这样一种能力: 检查某些事物以确定它是什么，它知道什么以及它能做什么。内省向程序员提供了极大的灵活性和控制力。一旦你使用支持内省的编程语言，就会产生类似的感觉: "未经检查的对象不值得实例化。"

本文介绍了 Python 编程语言的内省能力。整个 Python 语言对内省提供了深入而广泛的支持。实际上，很难想象假如 Python 语言没有内省特征的样子。 在读完本文的时候你应该能够非常轻松地观察到自己 Python 对象的“灵魂”。

在深入研究更高级的技术之前，我们会更可能用最普通的方式来研究 Python 内省。有些读者甚至可能会争论说： 我们开始时所讨论的特征不应该称之为”内省“。我们必须承认，他们是否属于内省的范畴还有待讨论。但从本文的主旨出发，我们所关心的只是找出有趣问题的答案。

现在让我们以交互式使用 Python 来开始研究。当我们从命令行启动 Python 时，就进入了 Python shell，在这里可以输入 Python 代码，而且立刻会从 Python 解释器获得响应。(本文中列出的命令可以使用 Python 3.6.3  正确执行)

代码段一: 交互式启动 Python 解释器

    copie@copie  ~  python
    Python 3.6.3 (default, Oct 24 2017, 14:48:20)
    [GCC 7.2.0] on linux
    Type "help", "copyright", "credits" or "license" for more information.
    >>>

在让 Python 运行起来，并看到 Python 提示符（ >>> ）之后，您可能想知道 Python 能识别什么字。大多数编程语言都有保留字或关键字，这些字在该语言中有特殊的意义，Python 也不例外。您可能还注意到，Python 建议我们输入 help 以获取更多信息。也许我们可以向 Python 寻求一些关于关键字的帮助。

## Python 的联机帮助实用程序

让我们按照建议那样，通过输入 help 来开始讨论，并观察它是否会向我们提供任何关于关键字的线索：

代码段二: 向 Python 寻求帮助

    >>> help
    Type help() for interactive help, or help(object) for help about object.

因为我们不知道那些对象可能包含关键字，所以不指定任何对象来尝试 help():

代码段三: 启动帮助实用程序

    >>> help()

    Welcome to Python 3.6's help utility!

    If this is your first time using Python, you should definitely check out
    the tutorial on the Internet at http://docs.python.org/3.6/tutorial/.

    Enter the name of any module, keyword, or topic to get help on writing
    Python programs and using Python modules.  To quit this help utility and
    return to the interpreter, just type "quit".

    To get a list of available modules, keywords, symbols, or topics, type
    "modules", "keywords", "symbols", or "topics".  Each module also comes
    with a one-line summary of what it does; to list the modules whose name
    or summary contain a given string such as "spam", type "modules spam".

    help>

现在，我们对此理解似乎深入了些。让我们在 help 提示符下输入 keywords:

代码段四: 用 keywords 寻求帮助

    help> keywords

    Here is a list of the Python keywords.  Enter any keyword to get more help.

    False               def                 if                  raise
    None                del                 import              return
    True                elif                in                  try
    and                 else                is                  while
    as                  except              lambda              with
    assert              finally             nonlocal            yield
    break               for                 not
    class               from                or
    continue            global              pass

    help> quit

    You are now leaving help and returning to the Python interpreter.
    If you want to ask for help on a particular object directly from the
    interpreter, you can type "help(object)".  Executing "help('string')"
    has the same effect as typing a particular string at the help> prompt.
    >>>

输入 help() 后，会看到一条欢迎消息和一些提示信息，接着是 help 提示符。在提示符下 输入 keywords，则会看到一个 Python 关键字列表。我们已经获得了问题的答案，于是退出帮助实用程序，这时会看到一条简短的告别消息，并返回到 Python 提示符下。

正如你从这个示例可以看到的，Python 的联机帮助实用程序会显示关于各种主题或特定对象的信息。帮助实用程序很有用，并确实利用了 Python 的内省能力。但仅仅使用帮助不会揭示帮助是如何获取其信息的。而且，因为文本的目的是揭示 Python 内省的所有秘密，所以我们必须迅速地跳出对帮助实用程序的讨论。

在结束关于帮助的讨论之前，让我们用它来获得一个可用的模块的列表。模块只是包含 Python 代码的文本文件，其后缀是 .py。 如果在 Python 提示符下输入 help('modules'),或在 help 提示符下输入modules，则会看到很长一列可用模块，类似于下面所示的部分列表。自己尝试并观察你的系统中有那些可用的模块，并了解为什么会认为 Python 是“自带电池”的。

代码段五: 部分可用模块的列表

    >>> help("modules")

    Please wait a moment while I gather a list of all available modules...

    /usr/lib/python3.6/site-packages/IPython/kernel/__init__.py:13: ShimWarning: The `IPython.kernel` package has been deprecated since IPython 4.0.You should import from ipykernel or jupyter_client instead.
    "You should import from ipykernel or jupyter_client instead.", ShimWarning)
    IPython             asyncio             importlib           sched
    __future__          asyncore            inspect             secrets
    _ast                atexit              io                  select
    _asyncio            audioop             ipaddress           selectors
    _bisect             autopep8            ipython_genutils    setuptools
    <.......中间还有很多......>
    _yaml               hmac                random              xxsubtype
    abc                 html                re                  yaml
    aifc                http                readline            zipapp
    antigravity         idlelib             reprlib             zipfile
    appdirs             idna                requests            zipimport
    argparse            imaplib             resource            zlib
    array               imghdr              rlcompleter
    ast                 imobiledevice       rmagic
    asynchat            imp                 runpy

    Enter any module name to get more help.  Or, type "modules spam" to search
    for modules whose name or summary contain the string "spam".

    >>>

## sys 模块

sys 模块是提供关于 Python 本身的详尽信息所在的模块。通过导入模块并用点 (.) 符号引用其内容(如变量，函数和类) 来使用模块。