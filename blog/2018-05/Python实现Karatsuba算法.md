# Python实现Karatsuba算法

Karatsuba算法是一种快速相乘算法，它由Anatolii Alexeevitch Karatsuba于1960年提出并于1962年发表.经典的乘法要 n^2 次个位数乘法而此算法只需要 3n^1.585

Karatsuba的算法主要是用于两个大数的乘法，极大提高了运算效率，相较于普通乘法降低了复杂度，并在其中运用了递归的思想。基本的原理和做法是将位数很多的两个大数 x 和 y 分成位数较少的数，每个数都是原来 x 和 y位数的一半。这样处理之后，简化为做三次乘法，并附带少量的加法操作和移位操作。一种典型的分治思想.

## 分析

因为:

    x = x1 * 10^m + x0
    y = y1 * 10^m + y0

那么:

    xy = (x1 * 10^m + x0)(y1 * 10^m + y0)

令:

    z0 = x0 * y0
    z1 = x1 * y0 + x0 * y1
    z2 = x1 * y1

于是有:
     
     xy = z2 * 10^2*m + z1 * 10^m + z0

而 z1 的计算显然又要两个乘法, 而其实他可以用 z0 和 z2 表示:

    z1 = (x1 + x0)*(y1 + y0) - z2 - z0

这样 z1 用一次乘法就可以了

## 实现代码

    def karatsuba(x, y):
        if len(str(x)) == 1 or len(str(y)) == 1:
            return x*y
        else:
            n = max(len(str(x)), len(str(y)))
            nby2 = int(n // 2)
            a = int(x // 10**(nby2))
            b = int(x % 10**(nby2))
            c = int(y // 10**(nby2))
            d = int(y % 10 ** (nby2))
            ac = karatsuba(a, c)
            bd = karatsuba(b, d)
            ad_plus_bc = karatsuba(a+b, c+d) - ac - bd
            prod = ac * 10**(2*nby2) + (ad_plus_bc * 10**nby2) + bd
            return prod
