# Python下swig基础知识总结整理(1)

SWIG 是个帮助使用 C 或者 C++ 编写的软件能与其他各种高级编程语言进行嵌入联接的开发工具。所以我就整理一些关于 Python 下使用 SWIG 的一些简单的使用方法。


先看一下简单的一个示例然后在进行一行一行的讲解

## 示例代码
### test.cpp

    #include <iostream>
    #include <vector>
    #include <algorithm>
    #include <string.h>

    #include "test.h"
    std::string helloWorld()
    {
        return "hello World";
    }

    long long sum(std::vector<int> v)
    {
        long long sum = 0;
        for (auto i : v)
        {
            sum += i;
        }
        return sum;
    }
    void printHello()
    {
        std::cout << "hello world" << std::endl;
    }
    std::vector<int> sort(std::vector<int> v)
    {
        sort(v.begin(), v.end());
        return v;
    }
    struct node st(int a, std::string str)
    {
        node tmp;
        tmp.a = a;
        tmp.str = str;
        return tmp;
    }

    Box::Box(double l, double b, double h)
    {
        Box::length = l;
        Box::breadth = b;
        Box::height = h;
    }
    double Box::tiji()
    {
        return Box::length * Box::breadth * Box::height;
    }

### test.h

    struct node
    {
        int a;
        std::string str;
    };
    std::string helloWorld();
    long long sum(std::vector<int> v);
    void printHello();
    std::vector<int> sort(std::vector<int> v);
    struct node st(int a, std::string str);
    class Box
    {
    public:
        double length;  // 盒子的长度
        double breadth; // 盒子的宽度
        double height;  // 盒子的高度
        Box(double l, double b, double h);
        double tiji();
    };

### test.i

    %module test
    %include "std_string.i"
    %include "std_vector.i"
    %include "carrays.i"
    namespace std
    {
        %template(IntVector) vector<int>;
    }

    %array_class(int, intArray);

    %{
    /* Includes the header in the wrapper code */
    #include "test.h"
    %}

    /* Parse the header file to generate wrappers */
    %include "test.h"

## 示例编译命令

    swig -c++ -python test.i
    g++ -c -fPIC --std=c++11  test.cpp test_wrap.cxx -I /usr/include/python3.5
    g++ -shared -fPIC --std=c++11 test.o test_wrap.o -o _test.so

通过上面的编译命令我们就可以获得 _test.so 的一个动态链接库文件

## 示例使用

    In [1]: import test
    In [2]: print(test.helloWorld())
    hello World

    In [3]: print(test.sum([i for i in range(101)]))
    5050

    In [4]: test.printHello()
    hello world

    In [6]: import random

    In [10]: print(test.sort(list(map(lambda x:random.randint(x,100),range(10)))    ))
    (7, 12, 14, 15, 38, 47, 53, 59, 75, 81)

    In [11]: list(map(lambda x:random.randint(x,100),range(10)))
    Out[11]: [2, 8, 38, 20, 74, 36, 94, 98, 88, 84]

    In [12]: x = test.Box(11.34,123,23.9)
    In [13]: x.breadth
    Out[13]: 123.0

    In [14]: x.length
    Out[14]: 11.34

    In [15]: x.height
    Out[15]: 23.9

    In [16]: x.tiji()
    Out[16]: 33336.198

    In [17]: y = test.st(100,"你好")

    In [19]: y.a
    Out[19]: 100

    In [20]: y.str
    Out[20]: '你好'


下一篇blog详细讲解
