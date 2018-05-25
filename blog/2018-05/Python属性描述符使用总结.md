# Python 属性描述符简单使用总结
描述符是对多个属性运用相同的存储逻辑的一种方式.描述符是实现了特定协议的类, 这些协议包括 __get__, __set__, __delete__ 方法.

## 描述符简单使用

```Python
class Quantity:
    __counter = 0

    def __init__(self):
        cls = self.__class__
        prefix = cls.__name__
        index = cls.__counter
        self.storage_name = f"_{prefix}#{index}"
        cls.__counter += 1
    
    def __get__(self, instance, owner):
        if instance is None:
            return self
        return getattr(instance,self.storage_name)
    
    def __set__(self, instance, value):
        if value > 0:
            setattr(instance, self.storage_name, value)
        else:
            raise ValueError("value must be > 0")
    
class LineItem:
    weight = Quantity()
    price = Quantity()

    def __init__(self, description, wright, price):
        self.description = description
        self.weight = wright
        self.price = price
    def subtotal(self):
        return self.weight * self.price
```
我们这里看到 weight 和 price 采取的存储逻辑是相同的.

```Python
import abc

class AutoStorage:
    __counter = 0

    def __init__(self):
        cls = self.__class__
        prifix = cls.__name__
        index = cls.__counter
        self.storage_name = f"_{prifix}#{index}"
        cls.__counter += 1
    
    def __get__(self, instance, owner):
        if instance is None:
            return self
        return getattr(instance,self.storage_name)

    def __set__(self, instance, value):
        setattr(instance, self.storage_name, value)

class Validated(abc.ABC, AutoStorage):
    def __set__(self, instance, value):
        value = self.validate(instance, value)
        super().__set__(instance, value)

    @abc.abstractmethod
    def validate(self, instance, value):
        """return validated value or ValueError"""

class Quantity(Validated):
    """a number greater then zero"""
    def validate(self, instance, value):
        if value <= 0:
            raise ValueError("value must be > 0")
        return value
class NoBlank(Validated):
    """长度的大于 0 的非空格字符串"""
    def validate(self, instance, value):
        value = value.strip()
        if len(value) == 0:
            raise ValueError("value cannot be empty or blank")
        return value

class LineItem:
    weight = Quantity()
    price = Quantity()
    description = NoBlank()

    def __init__(self, description, wright, price):
        self.description = description
        self.weight = wright
        self.price = price

    def subtotal(self):
        return self.weight * self.price
```
我们这样使用 LineItem 就不会去关心对与属性的验证了.隐藏了所有的细节
