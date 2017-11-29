class UpperAttrMetaClass(type):
    def __new__(cls, name, bases, dct):
        attrs = ((name, value) for name, value in dct.items()
                 if not name.startswith('__'))
        uppercase_attr = {name.upper(): value for name, value in attrs}
        return type.__new__(cls, name, bases, uppercase_attr)


class Foo(metaclass=UpperAttrMetaClass):
    bar = "bip"
