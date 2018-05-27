# Python设计模式-工厂方法

工厂一般分为两种: 一种是工厂方法,还有一种是抽象工厂

## 工厂方法
所谓的工厂方法就是,通过调用这个函数,由于参数不相同,会创建不同的对象.(当然这里有人会认为调用后返回一个对象的不是类吗?其实没毛病,不过在Python 里函数是一等公民怎么理解都可以),这些对象有相同的接口.
```Python
import xml.etree.ElementTree as etree
import json
from typing import Union


class JSONConnector:

    def __init__(self, filepath: str) -> None:
        self.data = dict()
        with open(filepath, mode="r", encoding='utf-8') as f:
            self.data = json.load(f)

    @property
    def parsed_data(self):
        return self.data


class XMLConnector:
    def __init__(self, filepath: str) -> None:
        self.tree = etree.parse(filepath)

    @property
    def parsed_data(self):
        return self.tree


def connector_factory(filepath: str) -> Union[JSONConnector, XMLConnector]:
    if filepath.endswith("json"):
        connector = JSONConnector
    elif filepath.endswith("xml"):
        connector = XMLConnector
    else:
        raise ValueError(f"不能连接到{filepath}")
    return connector(filepath)


def connect_to(filepath: str) -> Union[JSONConnector, XMLConnector, None]:
    factory = None
    try:
        factory = connector_factory(filepath)
    except ValueError as ve:
        print(ve)
    return factory


def main():
    sql_factory = connect_to("person.sq3")
    print(sql_factory)

    xml_factory = connect_to("person.xml")
    xml_data = xml_factory.parsed_data
    print(xml_data)

    json_factory = connect_to("person.json")
    json_data = json_factory.parsed_data
    print(json_data)


if __name__ == '__main__':
    main()

```
定义一个 特性工厂函数
```Python
def quantity(storage_name: str) -> property:

    def qty_getter(instance: property) -> float:
        return instance.__dict__[storage_name]

    def qty_setter(instance: property, value: float) -> None:
        if value > 0:
            instance.__dict__[storage_name] = value
        else:
            raise ValueError("value must be > 0")
    return property(qty_getter, qty_setter)


class LineItem:
    weight = quantity('weight')
    price = quantity('price')

    def __init__(self, description: str, weight: float, price: float) -> None:
        self.description = description
        self.weight = weight
        self.price = price

    def subtotal(self) -> float:
        return self.weight * self.price

```

