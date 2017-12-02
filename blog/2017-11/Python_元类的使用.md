# Python 元类的使用
以下示例代码全部能正常的运行在Python3.6.3上.
## 使用原来创建ORM的实例

我们通过创建一个类似Django中的ORM来熟悉一下元类的使用，通常元类用来创建API是非常好的选择，使用元类的编写很复杂但使用者可以非常简洁的调用API。

    # 我们想创建一个类似Django的ORM，只要定义字段就可以实现对数据库表和字段的操作。

    class User(Model):
        # 定义类的属性到列的映射：
        id = IntegerField('id')
        name = StringField('username')
        email = StringField('email')
        password = StringField('password')

例如:

    # 创建一个实例：
    u = User(id=12345, name='Michael', email='test@orm.org', password='my-pwd')
    # 保存到数据库：
    u.save()

下面来创建一个类似于上面所说的这个功能(修改了别人的代码)


    # coding:utf-8
    # 一、首先来定义Field类，它负责保存数据库表的字段名和字段类型：
    class Field:
        def __init__(self, name, column_type):
            self.name = name
            self.column_type = column_type

        def __str__(self):
            return '<%s:%s>' % (self.__class__.__name__, self.name)


    class StringField(Field):
        def __init__(self, name):
            super(StringField, self).__init__(name, 'varchar(100)')


    class IntegerField(Field):
        def __init__(self, name):
            super(IntegerField, self).__init__(name, 'bigint')

    # 二、定义元类，控制Model对象的创建


    class ModelMetaclass(type):
        '''定义元类'''
        def __new__(cls, name, bases, attrs):
            if name == 'Model':
                return super(ModelMetaclass, cls).__new__(cls, name, bases, attrs)
            mappings = dict()
            for k, v in attrs.items():
                # 保存类属性和列的映射关系到mappings字典
                if isinstance(v, Field):
                    print('Found mapping: %s==>%s' % (k, v))
                    mappings[k] = v
            for k in mappings.keys():
                # 将类属性移除，使定义的类字段不污染User类属性，只在实例中可以访问这些key
                attrs.pop(k)
            attrs['__table__'] = name.lower()  # 假设表名和为类名的小写,创建类时添加一个__table__类属性
            attrs['__mappings__'] = mappings  # 保存属性和列的映射关系，创建类时添加一个__mappings__类属性
            return super(ModelMetaclass, cls).__new__(cls, name, bases, attrs)

    # 三、编写Model基类


    class Model(dict, metaclass=ModelMetaclass):
        def __init__(self, **kw):
            super(Model, self).__init__(**kw)

        def __getattr__(self, key):
            try:
                return self[key]
            except KeyError:
                raise AttributeError(r"'Model' object has no attribute '%s'" % key)

        def __setattr__(self, key, value):
            self[key] = value

        def save(self):
            fields = []
            params = []
            args = []
            for k, v in self.__mappings__.items():
                fields.append(v.name)
                params.append(str(getattr(self, k)))
                args.append(getattr(self, k))
            sql = 'insert into %s (%s) values (%s)' % (
                self.__table__, ','.join(fields), ','.join(params))
            print('SQL: %s' % sql)
            print('ARGS: %s' % str(args))

    # 最后，我们使用定义好的ORM接口，使用起来非常的简单。


    class User(Model):
        # 定义类的属性到列的映射：
        id = IntegerField('id')
        name = StringField('username')
        email = StringField('email')
        password = StringField('password')

    # 创建一个实例：
    u = User(id=12345, name='Michael', email='test@orm.org', password='my-pwd')
    # 保存到数据库：
    u.save()

输出:

    Found mapping: id==><IntegerField:id>
    Found mapping: name==><StringField:username>
    Found mapping: email==><StringField:email>
    Found mapping: password==><StringField:password>
    SQL: insert into user (id,username,email,password) values (12345,Michael,test@orm.org,my-pwd)
    ARGS: [12345, 'Michael', 'test@orm.org', 'my-pwd']

## 实现单例模式

**单例模式(Singleton Pattern)** 是一种常见的软件设计模式,该模式的主要目的是确保**某一个类只有一个实例存在**. 当你希望在真整个系统中,某个类只能存在一个实例时,单例对象就能派上用场.

比如,某个服务器的配置信息存放在一个文件中,客户端通过一个AppConfig的类来读取配置文件的信息.如果在程序运行期间,有很多地方都需要使用配置文件的内容,也就是说,很多地方都需要创建 AppConfig 对象的实例,这就会导致系统中存在多个AppConfig 的实例对象,而这样会严重的浪费内存资源,尤其是在配置文件内容很多的情况下.事实上,类似AppConfig这样的类,我们希望在程序运行期间只存在一个实例对象.

在 Python 中,我们可以用很多方法来实现单例模式:

1. 使用模块
3. 使用装饰器(decorator)
4. 使用元类

### __nwe__,__init__,__call__的介绍
在讲到使用元类创建单例模式之前,必须了解__new__这个内置方法的作用,在上面讲元类的时候我们用到了__new__方法实现类的创建.然而我在之前还是对__new__这个方法和__init__方法有一定的疑惑.因此在这里发点时间对其概念做一次了解和区分.

__new__方法负责创建一个实例对象,在对象被创建的时候调用该方法它是一个类方法.__new__方法在返回一个实例后,会调用__init__方法,对实例进行初始化.如果__new__方法不返回值,或者返回的不是实例,那么他就不会自动调用__init__方法.
__init__ 方法负责将实例化对象进行初始化,在对象被创建之后调用该方法,在__new__方法创建出一个实例后对实例进行初始化.__init__方法没有返回值.
__call__方法其实和类的创建和实例化过程没有多大关系,定义了__call__方法才能被使用函数的方式执行.

例如:

    class A:
        def __call__(self):
            print("我被调用了")

    a = A()
    a()

输出:

    我被调用了

下面是一个简单的例子:

    class A(type):
        def __new__(cls, name, bases, attrs):
            print("调用了A new")
            return super(A, cls).__new__(cls, name, bases, attrs)

    class B(metaclass=A):
        def __init__(self):
            print("调用了B init")
    class C(B):
        def __call__(self):
            print("调用了call")
    print("创建完成")
    def main():
        x = C()
        x()
        pass
    if __name__ == '__main__':
        main()


输出:

    调用了A new
    调用了A new
    创建完成
    调用了B init
    调用了call

这里不难看出__new__和__init__方法的关系
这里我还有一点不明白(如果我重写了B,的__new__,就会出现莫名奇妙的结果,还要继续学习)

### 使用模块

其实,**Python 的模块就是天然的单例模式**,因为模块在第一次导入时,会生成 .pyc 文件,当第二次导入时,就会直接加载 .pyc 文件.而不会再次执行模块代码.因此,我们只需要把此把相关的函数和数据定义在一个模块中,就可以获得单例对象了.如果我们真的想要一个单例类,可以考虑这样做:

    class My_Singleton:
        def foo(self):
            pass

    my_singleton = My_Singleton()

将上面的代码保存在文件 mysingleton.py 中,然后这样使用:

    from mysingleton import my_singleton
    
    my_singleton.foo()

### 使用元类

    class Singleton(type):
        def __call__(cls, *args, **kwargs):
            if not hasattr(cls, '_instance'):
                cls._instance = super(Singleton, cls).__call__(*args, **kwargs)
            return cls._instance


    class Foo(metaclass=Singleton):
        pass


    foo1 = Foo()
    foo2 = Foo()

    print(foo1 is foo2)  # True

ps: 这个blog写不下去了   待我充电以后再战
