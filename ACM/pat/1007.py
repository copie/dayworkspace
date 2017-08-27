def _odd_iter():
    n = 1
    while True:
        n = n + 2
        yield n


def _not_divisible(n):
    return lambda x: x % n > 0


def primes():
    yield 2
    it = _odd_iter()  # 初始序列
    while True:
        n = next(it)  # 返回序列的第一个数
        yield n
        it = filter(_not_divisible(n), it)  # 构造新序列

for x in range(100000):
    s = primes()
    ans = 0
    tmp1 = next(s)
    tmp2 = next(s)
    while x >= tmp2:

        if tmp2 - tmp1 == 2:
            ans += 1
        tmp1, tmp2 = tmp2, next(s)
    print(ans,end=',')
