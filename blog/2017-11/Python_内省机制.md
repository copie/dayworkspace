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

sys 模块是提供关于 Python 本身的详尽信息所在的模块。通过导入模块并用点 (.) 符号引用其内容(如变量，函数和类) 来使用模块。sys 模块包含各种变量和函数，它揭示了当前Python 解释器有趣的详细信息。让我们研究其中的一部分。我们要再次以交互方式运行 Python，并在 Python 命令提示符下输入命令。首先，我们将导入 sys 模块。然后，我们会输入 sys.executable 变量，它包含到 Python 解释器的路径：

代码段六: 导入 sys 模块

    copie@copie  ~/dayworkspace   master  python
    Python 3.6.3 (default, Oct 24 2017, 14:48:20)
    [GCC 7.2.0] on linux
    Type "help", "copyright", "credits" or "license" for more information.
    >>> import sys
    >>> sys.executable
    '/usr/bin/python'

当输入一行只包含对象名称的代码时，Python 通过显示该对象的表示进行响应，对于简单对象，往往显示对象的值。在本例中，因为所显示的值是用引号括起来的，所以我们得到一条线索： sys.executable 可能是字符串对象。稍后，我们将研究确定对象类型的其它更精确的方法，但只在 Python 提示符下输入对象名称是一种迅速而又方便的自省形式。

让我们研究 sys 模块其它一些有用的属性。

platform 变量告诉我们现在处于什么操作系统上：

sys.platform 属性

    >>> sys.platform
    'linux

在当前的 Python 中，版本以字符串和元组（元组包含对象序列）来表示：

代码段八：sys.version 和 sys.version_info 属性

    >>> sys.version
    '3.6.3 (default, Oct 24 2017, 14:48:20) \n[GCC 7.2.0]'
    >>> sys.version_info
    sys.version_info(major=3, minor=6, micro=3, releaselevel='final', serial=0)

maxsize: An integer giving the maximum value a variable of type Py_ssize_t can take. It’s usually 2**31 - 1 on a 32-bit platform and 2**63 - 1 on a 64-bit platform.

sys.maxsize 属性

    >>> sys.maxsize
    9223372036854775807

argv 变量是一个包含命令行参数的列表（如果参数被指定的话）。第一项 argv[0] 是所运行脚本的路径。当我们以交互方式运行 Python 时，这个值是空字符串：

代码段十: sys.argv 属性

    >>> sys.argv
    ['']

当运行其它 Python shell 时，如 Ipython 会看到类似于下面的信息：

代码段十一: 使用 Ipython 时的 sys.argv 属性

    In [2]: sys.argv
    Out[2]: ['/usr/bin/ipython']

path 变量是模块搜索路径，Python 在导入期间将在其中的目录列表中寻找模块。最前面的空字符串 '' 是指当前目录：

    >>> sys.path
    ['', '/usr/lib/python36.zip', '/usr/lib/python3.6', '/usr/lib/python3.6/lib-dynload', '/usr/lib/python3.6/site-packages']

modules 变量是一个字典，它将当前已装入的所有模块的名称映射到模块对象。如您所见，缺省情况下，Python 装入一些特定的模块：

代码段十三: sys.modules

    >>> sys.modules
    {'builtins': <module 'builtins' (built-in)>, 'sys': <module 'sys' (built-in)>, '_frozen_importlib': <module '_frozen_importlib' (frozen)>, '_imp': <module '_imp'(built-in)>, '_warnings': <module '_warnings' (built-in)>, '_thread': <module '_thread' (built-in)>, '_weakref': <module '_weakref' (built-in)>, '_frozen_importlib_external': <module '_frozen_importlib_external' (frozen)>, '_io': <module 'io' (built-in)>, 'marshal': <module 'marshal' (built-in)>, 'posix': <module 'posix' (built-in)>, 'zipimport': <module 'zipimport' (built-in)>, 'encodings': <module 'encodings' from '/usr/lib/python3.6/encodings/__init__.py'>, 'codecs': <module 'codecs' from '/usr/lib/python3.6/codecs.py'>, '_codecs': <module '_codecs' (built-in)>, 'encodings.aliases': <module 'encodings.aliases' from '/usr/lib/python3.6/encodings/aliases.py'>, 'encodings.utf_8': <module 'encodings.utf_8' from '/usr/lib/python3.6/encodings/utf_8.py'>, '_signal': <module '_signal' (built-in)>, '__main__': <module '__main__' (built-in)>, 'encodings.latin_1': <module 'encodings.latin_1' from '/usr/lib/python3.6/encodings/latin_1.py'>, 'io': <module 'io' from '/usr/lib/python3.6/io.py'>, 'abc': <module 'abc' from '/usr/lib/python3.6/abc.py'>, '_weakrefset': <module '_weakrefset' from '/usr/lib/python3.6/_weakrefset.py'>, 'site': <module 'site' from '/usr/lib/python3.6/site.py'>, 'os': <module 'os' from '/usr/lib/python3.6/os.py'>, 'errno': <module 'errno' (built-in)>, 'stat': <module 'stat' from '/usr/lib/python3.6/stat.py'>, '_stat': <module '_stat' (built-in)>, 'posixpath': <module 'posixpath' from '/usr/lib/python3.6/posixpath.py'>, 'genericpath': <module 'genericpath' from '/usr/lib/python3.6/genericpath.py'>, 'os.path': <module 'posixpath' from '/usr/lib/python3.6/posixpath.py'>, '_collections_abc': <module '_collections_abc' from '/usr/lib/python3.6/_collections_abc.py'>, '_sitebuiltins': <module '_sitebuiltins' from '/usr/lib/python3.6/_sitebuiltins.py'>, 'sysconfig': <module 'sysconfig' from '/usr/lib/python3.6/sysconfig.py'>, '_sysconfigdata_m_linux_x86_64-linux-gnu': <module '_sysconfigdata_m_linux_x86_64-linux-gnu' from '/usr/lib/python3.6/_sysconfigdata_m_linux_x86_64-linux-gnu.py'>, 'readline': <module 'readline' from '/usr/lib/python3.6/lib-dynload/readline.cpython-36m-x86_64-linux-gnu.so'>, 'atexit': <module 'atexit' (built-in)>, 'rlcompleter': <module 'rlcompleter' from '/usr/lib/python3.6/rlcompleter.py'>, 're': <module 're' from '/usr/lib/python3.6/re.py'>, 'enum': <module 'enum' from '/usr/lib/python3.6/enum.py'>, 'types': <module 'types' from '/usr/lib/python3.6/types.py'>, 'functools': <module 'functools' from '/usr/lib/python3.6/functools.py'>, '_functools': <module '_functools' (built-in)>, 'collections': <module 'collections'from '/usr/lib/python3.6/collections/__init__.py'>, 'operator': <module 'operator' from '/usr/lib/python3.6/operator.py'>, '_operator': <module '_operator' (built-in)>, 'keyword': <module 'keyword' from '/usr/lib/python3.6/keyword.py'>, 'heapq': <module 'heapq' from '/usr/lib/python3.6/heapq.py'>, '_heapq': <module '_heapq' from '/usr/lib/python3.6/lib-dynload/_heapq.cpython-36m-x86_64-linux-gnu.so'>, 'itertools': <module 'itertools' (built-in)>, 'reprlib': <module 'reprlib' from '/usr/lib/python3.6/reprlib.py'>, '_collections': <module '_collections' (built-in)>, 'weakref': <module 'weakref' from '/usr/lib/python3.6/weakref.py'>, 'collections.abc': <module 'collections.abc' from '/usr/lib/python3.6/collections/abc.py'>, 'sre_compile': <module 'sre_compile' from '/usr/lib/python3.6/sre_compile.py'>, '_sre': <module '_sre' (built-in)>, 'sre_parse': <module 'sre_parse' from '/usr/lib/python3.6/sre_parse.py'>, 'sre_constants': <module 'sre_constants' from '/usr/lib/python3.6/sre_constants.py'>, '_locale': <module '_locale' (built-in)>, 'copyreg': <module 'copyreg' from '/usr/lib/python3.6/copyreg.py'>}

## keyword 模块

让我们返回到关于 Python 关键字的问题。尽管帮助向我们显示了关键字列表，但事实证明一些帮助信息是硬编码的。关键字列表恰好是硬编码的，但毕竟它的自省程度不深。让我们研究一下，能否直接从 Python 标准库的某个模块中获取这个信息。如果在 Python 提示符下输入 help('modules keywords') ，则会看到如下信息：

代码段十四：同时使用 modules 和 keywords 寻求帮助

    >>> help('modules keywords')

    Here is a list of modules whose name or summary contains 'keywords'.
    If there are any, enter a module name to get more help.

    keyword - Keywords (from "graminit.c")
    jedi.api.keywords

看起来， keyword 模块好象包含关键字。在文本编辑器中打开 keyword.py 文件，我们可以看到，Python 确实可以把关键字列表显式地用作 keyword 模块的 kwlist 属性。在 keyword 模块的注释中，我们还可以看到，该模块是根据 Python 本身的源代码自动生成的，这可以保证其关键字列表是准确而完整的：

代码段十五：keyword 模块的关键字列表

    >>> keyword.kwlist
    ['False', 'None', 'True', 'and', 'as', 'assert', 'break', 'class', 'continue', 'def', 'del', 'elif', 'else', 'except', 'finally', 'for', 'from', 'global', 'if', 'import', 'in', 'is', 'lambda', 'nonlocal', 'not', 'or', 'pass', 'raise', 'return', 'try', 'while', 'with', 'yield']

## dir() 函数

尽管查找和导入模块相对容易，但要记住每个模块包含什么却不是这么简单。您并不希望总是必须查看源代码来找出答案。幸运的是，Python 提供了一种方法，可以使用内置的 dir() 函数来检查模块（以及其它对象）的内容。

dir() 函数可能是 Python 自省机制中最著名的部分了。它返回传递给它的任何对象的属性名称经过排序的列表。如果不指定对象，则 dir() 返回当前作用域中的名称。让我们将 dir() 函数应用于 keyword 模块，并观察它揭示了什么：

代码段十六：keyword 模块的属性

    >>> dir(keyword)
    ['__all__', '__builtins__', '__cached__', '__doc__', '__file__', '__loader__', '__name__', '__package__', '__spec__', 'iskeyword', 'kwlist', 'main']

那么将它应用于我们先前讨论的 sys 模块会怎么样呢？

代码段十七：sys 模块的属性

    >>> dir(sys)
    ['__displayhook__', '__doc__', '__excepthook__', '__interactivehook__', '__loader__', '__name__', '__package__', '__spec__', '__stderr__', '__stdin__', '__stdout__', '_clear_type_cache', '_current_frames', '_debugmallocstats', '_getframe', '_git', '_home', '_xoptions', 'abiflags', 'api_version', 'argv', 'base_exec_prefix', 'base_prefix', 'builtin_module_names', 'byteorder', 'call_tracing', 'callstats', 'copyright', 'displayhook', 'dont_write_bytecode', 'exc_info', 'excepthook', 'exec_prefix', 'executable', 'exit', 'flags', 'float_info', 'float_repr_style', 'get_asyncgen_hooks', 'get_coroutine_wrapper', 'getallocatedblocks', 'getcheckinterval', 'getdefaultencoding', 'getdlopenflags', 'getfilesystemencodeerrors', 'getfilesystemencoding', 'getprofile', 'getrecursionlimit', 'getrefcount', 'getsizeof', 'getswitchinterval', 'gettrace', 'hash_info', 'hexversion', 'implementation', 'int_info', 'intern', 'is_finalizing', 'maxsize', 'maxunicode', 'meta_path', 'modules', 'path', 'path_hooks', 'path_importer_cache', 'platform', 'prefix', 'ps1', 'ps2', 'set_asyncgen_hooks', 'set_coroutine_wrapper', 'setcheckinterval', 'setdlopenflags', 'setprofile', 'setrecursionlimit', 'setswitchinterval', 'settrace', 'stderr', 'stdin', 'stdout', 'thread_info', 'version', 'version_info', 'warnoptions']

如果不带任何参数，则 dir() 返回当前作用域中的名称。请注意，因为我们先前导入了 keyword 和 sys ，所以它们出现在列表中。导入模块将把该模块的名称添加到当前作用域：

代码段十八：当前作用域中的名称

    >>> dir()
    ['__annotations__', '__builtins__', '__doc__', '__loader__', '__name__', '__package__', '__spec__', 'keyword', 'sys']

我们曾经提到 dir() 函数是内置函数，这意味着我们不必为了使用该函数而导入模块。不必做任何操作，Python 就可识别内置函数。现在，我们看到调用 dir() 后返回了这个名称 __builtins__ 。也许此处有连接。让我们在 Python 提示符下输入名称 __builtins__ ，并观察 Python 是否会告诉我们关于它的任何有趣的事情：

代码段十九： __builtins__ 是什么？

    >>> __builtins__
    <module 'builtins' (built-in)>

因此 __builtins__ 看起来象是当前作用域中绑定到名为 __builtin__ 的模块对象的名称。（因为模块不是只有多个单一值的简单对象，所以 Python 改在尖括号中显示关于模块的信息。）注：如果您在磁盘上寻找 __builtin__.py 文件，将空手而归。这个特殊的模块对象是 Python 解释器凭空创建的，因为它包含着解释器始终可用的项。尽管看不到物理文件，但我们仍可以将 dir() 函数应用于这个对象，以观察所有内置函数、错误对象以及它所包含的几个杂项属性。

代码段二十：__builtins__ 模块的属性

    >>> dir(__builtins__)
    ['ArithmeticError', 'AssertionError', 'AttributeError', 'BaseException', 'BlockingIOError', 'BrokenPipeError', 'BufferError', 'BytesWarning', 'ChildProcessError', 'ConnectionAbortedError', 'ConnectionError', 'ConnectionRefusedError', 'ConnectionResetError', 'DeprecationWarning', 'EOFError', 'Ellipsis', 'EnvironmentError','Exception', 'False', 'FileExistsError', 'FileNotFoundError', 'FloatingPointError', 'FutureWarning', 'GeneratorExit', 'IOError', 'ImportError', 'ImportWarning', 'IndentationError', 'IndexError', 'InterruptedError', 'IsADirectoryError', 'KeyError', 'KeyboardInterrupt', 'LookupError', 'MemoryError', 'ModuleNotFoundError', 'NameError', 'None', 'NotADirectoryError', 'NotImplemented', 'NotImplementedError', 'OSError', 'OverflowError', 'PendingDeprecationWarning', 'PermissionError', 'ProcessLookupError', 'RecursionError', 'ReferenceError', 'ResourceWarning', 'RuntimeError', 'RuntimeWarning', 'StopAsyncIteration', 'StopIteration', 'SyntaxError', 'SyntaxWarning', 'SystemError', 'SystemExit', 'TabError', 'TimeoutError', 'True', 'TypeError', 'UnboundLocalError', 'UnicodeDecodeError', 'UnicodeEncodeError', 'UnicodeError', 'UnicodeTranslateError', 'UnicodeWarning', 'UserWarning', 'ValueError', 'Warning', 'ZeroDivisionError', '_', '__build_class__', '__debug__', '__doc__', '__import__', '__loader__', '__name__', '__package__', '__spec__', 'abs', 'all', 'any', 'ascii', 'bin', 'bool', 'bytearray', 'bytes', 'callable', 'chr', 'classmethod', 'compile', 'complex', 'copyright', 'credits', 'delattr', 'dict', 'dir', 'divmod', 'enumerate', 'eval', 'exec', 'exit', 'filter', 'float', 'format', 'frozenset', 'getattr', 'globals', 'hasattr', 'hash', 'help', 'hex', 'id', 'input', 'int', 'isinstance', 'issubclass', 'iter', 'len', 'license', 'list', 'locals', 'map', 'max', 'memoryview', 'min', 'next', 'object', 'oct', 'open', 'ord', 'pow', 'print', 'property', 'quit', 'range', 'repr', 'reversed', 'round', 'set', 'setattr', 'slice', 'sorted', 'staticmethod', 'str', 'sum', 'super', 'tuple', 'type', 'vars', 'zip']

dir() 函数适用于所有对象类型，包括字符串、整数、列表、元组、字典、函数、定制类、类实例和类方法。让我们将 dir() 应用于字符串对象，并观察 Python 返回什么。如您所见，即使简单的 Python 字符串也有许多属性：

代码段二十一： 字符串属性

    >>> dir("Hello world!")
    ['__add__', '__class__', '__contains__', '__delattr__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__getitem__', '__getnewargs__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__iter__', '__le__', '__len__', '__lt__', '__mod__', '__mul__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__rmod__', '__rmul__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', 'capitalize', 'casefold', 'center', 'count', 'encode', 'endswith', 'expandtabs', 'find', 'format', 'format_map', 'index', 'isalnum', 'isalpha', 'isdecimal', 'isdigit', 'isidentifier', 'islower', 'isnumeric', 'isprintable', 'isspace', 'istitle', 'isupper', 'join', 'ljust', 'lower', 'lstrip', 'maketrans', 'partition', 'replace', 'rfind', 'rindex', 'rjust', 'rpartition', 'rsplit', 'rstrip', 'split', 'splitlines', 'startswith', 'strip', 'swapcase', 'title', 'translate', 'upper', 'zfill']

自己尝试下列示例以观察它们返回什么。注： # 字符标记注释的开始。Python 将忽略从注释开始部分到该行结束之间的所有内容：

代码段二十二: 将 dir() 运用于其它对象

    dir(42)   # Integer (and the meaning of life)
    dir([])   # List (an empty list, actually)
    dir(())   # Tuple (also empty)
    dir({})   # Dictionary (ditto)
    dir(dir)  # Function (functions are also objects)


为了说明 Python 自省能力的动态本质，让我们研究将 dir() 运用于定制类和一些类实例的示例。我们将以交互方式定义自己的类，创建一些类的实例，仅向其中一个实例添加唯一的属性，并观察 Python 能否一直保存所有这些。以下是结果：

代码段二十三:  将 dir() 运用于定制类、类实例和属性

    In [1]: class Person():
    ...:     '''一个 Person 类'''
    ...: 
    ...:     def __init__(self, name, age):
    ...:         self.name = name
    ...:         self.age = age
    ...:     def intro(self):
    ...:         '''一个人的自我介绍'''
    ...:         return f"hello ,my name is {self.name} and I'm {self.age}"
    ...: 

    In [2]: xu = Person("xu",22)

    In [3]: copie = Person("copie",21)

    In [4]: copie.sport = "codeing"

    In [5]: dir(Person)
    Out[5]: 
    ['__class__',
    '__delattr__',
    '__dict__',
    '__dir__',
    '__doc__',
    '__eq__',
    '__format__',
    '__ge__',
    '__getattribute__',
    '__gt__',
    '__hash__',
    '__init__',
    '__init_subclass__',
    '__le__',
    '__lt__',
    '__module__',
    '__ne__',
    '__new__',
    '__reduce__',
    '__reduce_ex__',
    '__repr__',
    '__setattr__',
    '__sizeof__',
    '__str__',
    '__subclasshook__',
    '__weakref__',
    'intro']

    In [6]: dir(xu)
    Out[6]: 
    ['__class__',
    '__delattr__',
    '__dict__',
    '__dir__',
    '__doc__',
    '__eq__',
    '__format__',
    '__ge__',
    '__getattribute__',
    '__gt__',
    '__hash__',
    '__init__',
    '__init_subclass__',
    '__le__',
    '__lt__',
    '__module__',
    '__ne__',
    '__new__',
    '__reduce__',
    '__reduce_ex__',
    '__repr__',
    '__setattr__',
    '__sizeof__',
    '__str__',
    '__subclasshook__',
    '__weakref__',
    'age',
    'intro',
    'name']

    In [7]: dir(copie)
    Out[7]: 
    ['__class__',
    '__delattr__',
    '__dict__',
    '__dir__',
    '__doc__',
    '__eq__',
    '__format__',
    '__ge__',
    '__getattribute__',
    '__gt__',
    '__hash__',
    '__init__',
    '__init_subclass__',
    '__le__',
    '__lt__',
    '__module__',
    '__ne__',
    '__new__',
    '__reduce__',
    '__reduce_ex__',
    '__repr__',
    '__setattr__',
    '__sizeof__',
    '__str__',
    '__subclasshook__',
    '__weakref__',
    'age',
    'intro',
    'name',
    'sport']

    In [8]: xu.intro()
    Out[8]: "hello ,my name is xu and I'm 22"

    In [9]: dir(xu.intro)
    Out[9]: 
    ['__call__',
    '__class__',
    '__delattr__',
    '__dir__',
    '__doc__',
    '__eq__',
    '__format__',
    '__func__',
    '__ge__',
    '__get__',
    '__getattribute__',
    '__gt__',
    '__hash__',
    '__init__',
    '__init_subclass__',
    '__le__',
    '__lt__',
    '__ne__',
    '__new__',
    '__reduce__',
    '__reduce_ex__',
    '__repr__',
    '__self__',
    '__setattr__',
    '__sizeof__',
    '__str__',
    '__subclasshook__']

## 文档字符串

在许多 dir() 示例中，您可能会注意到的一个属性是 __doc__ 属性。这个属性是一个字符串，它包含了描述对象的注释。Python 称之为文档字符串或 docstring，以下是其工作原理。如果模块、类、方法或函数定义的第一条语句是字符串，那么该字符串会作为对象的 __doc__ 属性与该对象关联起来。例如，看一下 __builtins__ 对象的文档字符串。因为文档字符串通常包含嵌入的换行 \n ，我们将使用 Python 的 print 语句，以便输出更易于阅读：

代码段二十四: 模块文档字符串

    In [10]: print(__builtins__.__doc__)
    Built-in functions, exceptions, and other objects.

    Noteworthy: None is the `nil' object; Ellipsis represents `...' in slices.

Python 甚至再次维持了在 Python shell 中以交互方式定义的类和方法上的文档字符串。让我们研究 Person 类及其 intro 方法的文档字符串：

代码段二十五: 类和方法文档字符串

    In [11]: Person.__doc__
    Out[11]: '一个 Person 类'

    In [12]: copie.__doc__
    Out[12]: '一个 Person 类'

    In [13]: copie.intro.__doc__
    Out[13]: '一个人的自我介绍'

因为文档字符串提供了如此有价值的信息，所以许多 Python 开发环境都有自动显示对象的文档字符串的方法。让我们再看一个 dir() 函数的文档字符串：

代码段二十六: 函数文档字符串

    In [14]: print(dir.__doc__)
    dir([object]) -> list of strings

    If called without an argument, return the names in the current scope.
    Else, return an alphabetized list of names comprising (some of) the attributes
    of the given object, and of attributes reachable from it.
    If the object supplies a method named __dir__, it will be used; otherwise
    the default dir() logic is used and returns:
    for a module object: the module's attributes.
    for a class object:  its attributes, and recursively the attributes
        of its bases.
    for any other object: its attributes, its class's attributes, and
        recursively the attributes of its class's base classes.


检查 Python 对象

我们好几次提到了“对象（object）”这个词，但一直没有真正定义它。编程环境中的对象很象现实世界中的对象。实际的对象有一定的形状、大小、重量和其它特征。实际的对象还能够对其环境进行响应、与其它对象交互或执行任务。计算机中的对象试图模拟我们身边现实世界中的对象，包括象文档、日程表和业务过程这样的抽象对象。

类似于实际的对象，几个计算机对象可能共享共同的特征，同时保持它们自己相对较小的变异特征。想一想您在书店中看到的书籍。书籍的每个物理副本都可能有污迹、几张破损的书页或唯一的标识号。尽管每本书都是唯一的对象，但都拥有相同标题的每本书都只是原始模板的实例，并保留了原始模板的大多数特征。
对于面向对象的类和类实例也是如此。例如，可以看到每个 Python 字符串都被赋予了一些属性， dir() 函数揭示了这些属性。在前一个示例中，我们定义了自己的 Person 类，它担任创建个别 Person 实例的模板，每个实例都有自己的 name 和 age 值，同时共享自我介绍的能力。这就是面向对象。

于是在计算机术语中，对象是拥有标识和值的事物，属于特定类型、具有特定特征和以特定方式执行操作。并且，对象从一个或多个父类继承了它们的许多属性。除了关键字和特殊符号（象运算符，如 + 、 - 、 * 、 ** 、 / 、 % 、 < 、 > 等）外，Python 中的所有东西都是对象。Python 具有一组丰富的对象类型：字符串、整数、浮点、列表、元组、字典、函数、类、类实例、模块、文件等。
当您有一个任意的对象（也许是一个作为参数传递给函数的对象）时，可能希望知道一些关于该对象的情况。在本节中，我们将向您展示如何让 Python 对象回答如下问题：

1. 对象的名称是什么？
2. 这是哪种类型的对象？
3. 对象知道些什么？
4. 对象能做些什么？
5. 对象的父对象是谁？

### 名称
并非所有对象都有名称，但那些有名称的对象都将名称存储在其 __name__ 属性中。注：名称是从对象而不是引用该对象的变量中派生的。下面这个示例着重说明了这种区别：

代码段二十七: 名称中有什么

    >>> dir()
    ['__annotations__', '__builtins__', '__doc__', '__loader__', '__name__', '__package__', '__spec__']
    >>> directory = dir
    >>> directory()
    ['__annotations__', '__builtins__', '__doc__', '__loader__', '__name__', '__package__', '__spec__', 'directory']
    >>> dir.__name__
    'dir'
    >>> directory.__name__
    'dir'
    >>> __name__
    '__main__'

模块拥有名称，Python 解释器本身被认为是顶级模块或主模块。当以交互的方式运行 Python 时，局部 __name__ 变量被赋予值 '__main__' 。同样地，当从命令行执行 Python 模块，而不是将其导入另一个模块时，其 __name__ 属性被赋予值 '__main__' ，而不是该模块的实际名称。这样，模块可以查看其自身的 __name__ 值来自行确定它们自己正被如何使用，是作为另一个程序的支持，还是作为从命令行执行的主应用程序。因此，下面这条惯用的语句在 Python 模块中是很常见的：

代码段二十八: 用于执行或者导入的测试

    In [2]: if __name__ == "__main__":
    ...:     # 做一些事情在这里比如调用一个main() 它被定义在其他地方
    ...:     pass
    ...: else:
    ...:     # 什么事情也不做.当这个模块被其他的模块导入的时候,想要用这个模块的函数,类还有
    ...: 其他
    ...:     pass
    ...: 

### 类型

type() 函数有助于我们确定对象是字符串还是整数，或是其它类型的对象。它通过返回类型对象来做到这一点，可以将这个类型对象与 types 模块中定义的类型相比较：

    In [3]: import types

    In [4]: print(types.__doc__)

    Define names for built-in types that aren't directly accessible as a builtin.

    In [11]: x = lambda x:x
    In [14]: type(x) == types.LambdaType
    Out[14]: True
    In [15]: type(42)
    Out[15]: int

    In [16]: type(x)
    Out[16]: function

    In [17]: type([])
    Out[17]: list

    In [18]: type(())
    Out[18]: tuple

    In [19]: type({})
    Out[19]: dict

    In [20]: type(dir)
    Out[20]: builtin_function_or_method

### 标识

先前我们说过，每个对象都有标识、类型和值。值得注意的是，可能有多个变量引用同一对象，同样地，变量可以引用看起来相似（有相同的类型和值），但拥有截然不同标识的多个对象。当更改对象时（如将某一项添加到列表），这种关于对象标识的概念尤其重要，如在下面的示例中， blist 和 clist 变量引用同一个列表对象。正如您在示例中所见， id() 函数给任何给定对象返回唯一的标识符：

代码段三十: 目的地

    In [2]: alist = [1,2,3]

    In [3]: blist = [1,2,3]

    In [4]: clist = blist

    In [5]: clist
    Out[5]: [1, 2, 3]

    In [6]: clist
    Out[6]: [1, 2, 3]

    In [7]: alist
    Out[7]: [1, 2, 3]

    In [8]: id(alist)
    Out[8]: 140170172530184

    In [9]: id(blist)
    Out[9]: 140170172738632

    In [10]: id(clist)
    Out[10]: 140170172738632

    In [11]: alist is blist
    Out[11]: False

    In [12]: blist is clist
    Out[12]: True

    In [13]: clist.append(4)
    In [15]: clist
    Out[15]: [1, 2, 3, 4]

    In [16]: blist
    Out[16]: [1, 2, 3, 4]

    In [17]: alist
    Out[17]: [1, 2, 3]

### 属性

我们已经看到对象拥有属性，并且 dir() 函数会返回这些属性的列表。但是，有时我们只想测试一个或多个属性是否存在。如果对象具有我们正在考虑的属性，那么通常希望只检索该属性。这个任务可以由 hasattr() 和 getattr() 函数来完成，如本例所示：

代码段三十一: 具有一个属性;获得一个属性

    In [18]: print(hasattr.__doc__)
    Return whether the object has an attribute with the given name.

    This is done by calling getattr(obj, name) and catching AttributeError.

    In [19]: print(getattr.__doc__)
    getattr(object, name[, default]) -> value

    Get a named attribute from an object; getattr(x, 'y') is equivalent to x.y.
    When a default argument is given, it is returned when the attribute doesn't
    exist; without it, an exception is raised in that case.

    In [20]: hasattr(id,"__doc__")
    Out[20]: True

    In [21]: print(getattr(id,"__doc__"))
    Return the identity of an object.

    This is guaranteed to be unique among simultaneously existing objects.
    (CPython uses the object's memory address.)

### 可调用性

可以调用表示潜在行为（函数和方法）的对象。可以用 callable() 函数测试对象的可调用性：

    In [23]: callable("一个字符串")
    Out[23]: False

    In [24]: callable(dir)
    Out[24]: True
    In [31]: class test:
    ...:     def __call__(self):
    ...:         print("哈哈对象可以直接调用了")
    ...:
    In [32]: x = test()
    In [33]: x()
    哈哈对象可以直接调用了


### 实例

在 type() 函数提供对象的类型时，还可以使用 isinstance() 函数测试对象，以确定它是否是某个特定类型或定制类的实例：

代码段三十三: 你是那些实例中的一个吗?

    In [34]: print(isinstance.__doc__)
    Return whether an object is an instance of a class or of a subclass thereof.

    A tuple, as in ``isinstance(x, (A, B, ...))``, may be given as the target to
    check against. This is equivalent to ``isinstance(x, A) or isinstance(x, B)
    or ...`` etc.

    In [35]: isinstance(42,str)
    Out[35]: False

    In [36]: isinstance("hello",str)
    Out[36]: True

    In [37]: isinstance(42,int)
    Out[37]: True

    In [38]: isinstance("hello",int)
    Out[38]: False

### 子类

我们先前提到过，定制类的实例从该类继承了属性。在类这一级别，可以根据一个类来定义另一个类，同样地，这个新类会按照层次化的方式继承属性。Python 甚至支持多重继承，多重继承意味着可以用多个父类来定义一个类，这个新类继承了多个父类。 issubclass() 函数使我们可以查看一个类是不是继承了另一个类：

代码三十四: 你是我母亲吗?

    In [1]: class Person():
    ...:     '''一个 Person 类'''
    ...: 
    ...:     def __init__(self, name, age):
    ...:         self.name = name
    ...:         self.age = age
    ...:     def intro(self):
    ...:         '''一个人的自我介绍'''
    ...:         return f"hello ,my name is {self.name} and I'm {self.age}"
    ...: 
    ...: class SuperHero(Person):
    ...:     def intro(self):
    ...:         '''一个人的自我介绍'''
    ...:         return f'Hello, I\'m SuperHero {self.name} and I\'m {self.age}'
    ...:     

    In [2]: issubclass(SuperHero,Person)
    Out[2]: True

    In [3]: issubclass(Person,SuperHero)
    Out[3]: False

## 检查时间

让我们将上一节中讨论的几种检查技术结合起来。为了做到这一点，要定义自己的函数 — interrogate() ，它打印有关传递给它的任何对象的各种信息。以下是代码，后面是其用法的几个示例：

代码段三十五: 谁也没料到它

    In [4]: def interrogate(item):
    ...:     """Print useful information about item."""
    ...:     if hasattr(item,"__name__"):
    ...:         print("NAME:        ",item.__name__)
    ...:     if hasattr(item,"__class__"):
    ...:         print("CLASS:       ",item.__class__.__name__)
    ...:     print("ID       ",id(item))
    ...:     print("TYPE:        ",type(item))
    ...:     print("VALUE:       ",str(item))
    ...:     print("CALLABLE:        ","YES" if callable(item) else "NO")
    ...:     if hasattr(item,"__doc__"):
    ...:         doc = getattr(item,"__doc__")
    ...:         doc = doc.strip()
    ...:         firstline = doc.split("\n")[0]
    ...:         print("DOC:     ",firstline)
    ...:         

    In [5]: interrogate("我是字符串")
    CLASS:        str
    ID        140599610351312
    TYPE:         <class 'str'>
    VALUE:        我是字符串
    CALLABLE:         NO
    DOC:      str(object='') -> str

    In [6]: interrogate(42)
    CLASS:        int
    ID        140599733153824
    TYPE:         <class 'int'>
    VALUE:        42
    CALLABLE:         NO
    DOC:      int(x=0) -> integer

    In [7]: interrogate(interrogate)
    NAME:         interrogate
    CLASS:        function
    ID        140599610533816
    TYPE:         <class 'function'>
    VALUE:        <function interrogate at 0x7fdfe5d767b8>
    CALLABLE:         YES
    DOC:      Print useful information about item.

正如您在最后一个示例中所看到的， interrogate() 函数甚至可以应用于它本身。您没有再比它更具“自省性”的工具了。

## 结束语

谁知道自省可以变得这么简单而又如此有价值？可是，我在结束时必须提出警告：不要将自省的结果误认为是万能的。有经验的 Python 程序员知道：他们不知道的东西总是比已知的更多，因此根本不可能是万能的。编程行为产生的问题多于答案。关于 Python 的唯一优点（正如我们今天在本文中所见）是它确实回答了人们的问题。至于我本人，觉得您不必因为我帮助您了解了这些 Python 必须提供的内容而酬谢我。用 Python 编程自有回报。我从爱好 Python 的同伴处获得的帮助也是不计报酬的。
