def series(x):
    return x * (x + 1) // 2


def max(a, b):
    # print(type(a))
    return a if a > b else b


m, b = map(int, input().split())
mymax = 0
for y in range(0, b + 1):
    x = m * (b - y)
    # t = 0
    t = (x + 1) * series(y) + (y + 1) * series(x)
    mymax = int(max(mymax, t))

print((mymax))
