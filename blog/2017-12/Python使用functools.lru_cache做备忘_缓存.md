# Python使用functools.lru_cache做备忘(缓存)

记得上一次我写关于装饰器的blog的时候我就留下了一点疑问就是别人说的用装饰器进行缓存到底是什么意思啊.经过那么长时间的充电感觉自己学到了很多.这里呢就和大家分享一下我对于 Python 做缓存的理解.

functools.lru_cache 是非常实用的装饰器,它实现了备忘录(memoization)功能.这是一项优化技术,他把耗时的函数的结果保存起来,避免传入相同的参数时重复计算,LRU 三个字母是"Least Recently Used"的缩写,表明缓存不会无限制的增长,一段时间不用缓存条目会被扔掉.

生成第 N 个 斐波那契数这种慢速递归函数适合用 lru_cache, 如下代码所示:

> 生成第N个斐波那契数,递归方式非常耗时

    # clockedeco.py
    import time
    import functools
    def clock(func):
        @functools.wraps(func)
        def clocked(*args):
            t0 = time.time()
            result = func(*args)
            elapsed = time.time() - t0
            name = func.__name__
            arg_lst = []
            arg_str = ', '.join(arg_lst)
            print('[%0.8fs] %s(%s) -> %r ' % (elapsed, name, arg_str, result))
            return result
        return clocked

---
    # test.py

    from clockdeco import clock

    @clock
    def fibonacci(n):
        if n < 2:
            return n
        return fibonacci(n-2)+fibonacci(n-1)

    def main():
        print(fibonacci(6))

    if __name__ == '__main__':
        main()

除了最后一行都是clock输出的

    [0.00000048s] fibonacci() -> 0
    [0.00001073s] fibonacci() -> 1
    [0.00003815s] fibonacci() -> 1
    [0.00000024s] fibonacci() -> 1
    [0.00000072s] fibonacci() -> 0
    [0.00000048s] fibonacci() -> 1
    [0.00001359s] fibonacci() -> 1
    [0.00002670s] fibonacci() -> 2
    [0.00007582s] fibonacci() -> 3
    [0.00000024s] fibonacci() -> 1
    [0.00000048s] fibonacci() -> 0
    [0.00000024s] fibonacci() -> 1
    [0.00001001s] fibonacci() -> 1
    [0.00002003s] fibonacci() -> 2
    [0.00000024s] fibonacci() -> 0
    [0.00000024s] fibonacci() -> 1
    [0.00000954s] fibonacci() -> 1
    [0.00000048s] fibonacci() -> 1
    [0.00000048s] fibonacci() -> 0
    [0.00000024s] fibonacci() -> 1
    [0.00000954s] fibonacci() -> 1
    [0.00001907s] fibonacci() -> 2
    [0.00003815s] fibonacci() -> 3
    [0.00006866s] fibonacci() -> 5
    [0.00015855s] fibonacci() -> 8
    8

浪费时间的地方很明显: fibonacci(1) 调用了八次,fibonacci(2) 调用了五次....但是如果增加两行代码,使用 lru_cache,性能会显著改善,如下面的代码:

    from clockdeco import clock
    import functools

    @functools.lru_cache()
    @clock
    def fibonacci(n):
        if n < 2:
            return n
        return fibonacci(n-2)+fibonacci(n-1)

    def main():
        print(fibonacci(6))

    if __name__ == '__main__':
        main()

1. 注意这里必须像常规函数那样调用lru_cache.这一行中有一对括号: @functools.lru_cache().这么做是因为 lru_cache 可以接受配置参数.稍后说明
2.  这里叠放了装饰器:@lru_cache() 应用到 @clock 返回的函数上.

这样一来,执行时间减少了,而且 n 的每个值只调用一次函数:

    [0.00000072s] fibonacci() -> 0
    [0.00000072s] fibonacci() -> 1
    [0.00005722s] fibonacci() -> 1
    [0.00000119s] fibonacci() -> 2
    [0.00007224s] fibonacci() -> 3
    [0.00000072s] fibonacci() -> 5
    [0.00008965s] fibonacci() -> 8
    8

在计算 fibonacci(30) 的另一个测试中 代码段二 中的版本在 0.0005秒内调用了 31 次 fibonacci 函数,而示例 代码段一 中未缓存的版本调用fibonacci 函数 2 692 537 次,在使用 Intel Core i7 处理器的笔记本电脑中耗时 17.7 秒。ps(其实我的i5更快一点)

除了优化递归算法之外,lru_cache 在从 Web 中获取信息的应用中也能发挥巨大作用。

特别要注意,lru_cache是:
可以使用两个可选的参数来配置。它的签名

    functools.lru_cache(maxsize=128, typed=False)

maxsize 参数指定存储多少个调用的结果。缓存满了之后,旧的结果会被扔掉,腾出空间。为了得到最佳性能,maxsize 应该设为 2 的幂。typed 参数如果设为 True,把不同参数类型得到的结果分开保存,即把通常认为相等的浮点数和整数参数(如 1 和 1.0)区分开。顺
便说一下,因为 lru_cache 使用字典存储结果,而且键根据调用时传入的定位参数和关键字参数创建,所以被 lru_cache 装饰的函数,它的所有参数都必须是可散列的。
