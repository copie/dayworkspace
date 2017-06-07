# map中的key为结构体

## 闲聊
今天有学到一招
## 代码

    #include <map>
    #include <iostream>

    struct  Test
    {
        int x;
        int y;

        bool operator < (const Test &o) const
        {
            return x < o.x || y < o.y;
        }
    };

    int main()
    {
        std::map<Test, std::string> mapTest;
        Test test = { 1, 2 };
        mapTest[test] = "Test1";
        
        for (auto it = mapTest.begin(); it != mapTest.end();it++)
        {
            std::cout << it->first.x << " " << it->first.y << " " << it->second.c_str() << std::endl;
        }

        return 0;
    }

##　作者语

        bool operator < (const Test &o) const
        {
            return x < o.x || y < o.y;
        }
        
> 要定义你想要排序的规则，如果x和ｙ相等如果有其它变量不同map也会人为是同一个键值