# Python_弱引用_总结

+ 弱引用不会增加对象的引用数量
+ 弱引用在缓存应用中很有用保存缓存对象。
+ **Python 控制台会自动把 _ 变量绑定到结果不为 None 的表达式结果上**
+ 不明显的隐式赋值会为对象创建新引用
+ 可以用 weakref.ref(a_set) 为 a_set 创建一个弱引用
+ 不建议使用 weakref.ref 来创建一个对象的弱引用

## WeakValueDictionary 使用

+ WeakValueDictionary 类是一种可变映射, 值是对象的弱引用.
+ 被引用的对象被回收后也会在对应的键也会从 WeakValueDictionary 中删除
+ 在 for 循环中的临时变量在没有显式的删除的情况下会一直存在 是全局变量
+ WeakKeyDictionary(对键的弱引用)ps 对其作用不太理解
+ WeakSet 一个弱引用组成的集合(一般会用在一个类想要知道自己有多少实例的时候)

## 弱引用的局限

+ 不是所有的 Python 都可以做弱引用的目标
+ 用Python（但不是C）写的函数，实例方法，sets ，frozensets，一些file objects，generator ，套接字，数组，deques，正则表达式模式对象和代码对象, thread.lock, threading.Lock
+ 一些内建类型，如list和dict不直接支持弱引用，但可以通过子类化添加支持
+ 其他内建类型如tuple和int即使在子类化时也不支持弱引用（这是一个实现细节，可能在不同的Python实现中是不同的。）
+ 扩展类型可以很容易地支持弱引用 更多请查看(Defining New Types)[https://yiyibooks.cn/xx/python_352/extending/newtypes.html#weakref-support]


