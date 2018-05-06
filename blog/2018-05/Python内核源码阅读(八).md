# Python内核源码阅读(八)

## 大整数的处理方法

在 Python3 中并没有和 Python2的

```C
#define BLOCK_SIZE 1000 /* 1K less typical malloc overhead */
#define BHEAD_SIZE 8 /* Enough for a 64-bit pointer */
#define N_INTOBJECTS ((BLOCK_SIZE - BHEAD_SIZE) / sizeof(PyIntObject))
```
对应的宏.所以在 Python3 中 对于大数的没有采用和 Python2 一样的缓存机制(通过跟踪代码Python很有可能用的是一种全局的缓存机制)

在 PyObject *PyLong_FromLong(long ival) 函数中,返回一个新的整数对象是使用 
PyLongObject *_PyLong_New(Py_ssize_t size) 函数, 这个函数接受一个 Py_ssize_t 类型的整数, 然后返回具有适当大小的 PyLongObject 对象.

其中适当大小的表述是这样的:

    offsetof(PyLongObject, ob_digit) + size*sizeof(digit)

offsetof 宏定义:

    #define offsetof(s,m) ((size_t)&(((s*)0)->m))

offsetof宏确定结构体s中的成员m的偏移量，也就是结构体中m之前所有成员的大小。

再加上 PyLongObject 本身的柔性数组实现的最终确定的结构体中的 digit 数组正好包含该对象所需要的 digit 的数量.

## 整数对象的数值操作

我们知道 整数保存在 ob_digit[] 中加减都是从低位起同小学加减法.乘法是Karatsuba算法.

### 整数加法
```C
static PyObject *
long_add(PyLongObject *a, PyLongObject *b)
{
    PyLongObject *z;

    CHECK_BINOP(a, b);

    if (Py_ABS(Py_SIZE(a)) <= 1 && Py_ABS(Py_SIZE(b)) <= 1) {
        // 如果是比较小的数(小于2^30或2^15),直接简单加法
        return PyLong_FromLong(MEDIUM_VALUE(a) + MEDIUM_VALUE(b));
    }
    if (Py_SIZE(a) < 0) {
        if (Py_SIZE(b) < 0) {
            // a,b 都是负数 直接相加,符号为 负
            z = x_add(a, b);
            if (z != NULL) {
                /* x_add received at least one multiple-digit int,
                   and thus z must be a multiple-digit int.
                   That also means z is not an element of
                   small_ints, so negating it in-place is safe. */
                assert(Py_REFCNT(z) == 1);
                Py_SIZE(z) = -(Py_SIZE(z));
            }
        }
        else
            // a + b 等于 b-(-a) 其中 a < 0 
            z = x_sub(b, a);
    }
    else {
        if (Py_SIZE(b) < 0)
            z = x_sub(a, b);
        else
            z = x_add(a, b);
    }
    return (PyObject *)z;
}
```

x_add(a, b) 和 x_sub(a, b) 只是用来计算, long_add 根据 a,b 的不同情况,调用不同的运算方法.

```C
static PyLongObject *
x_add(PyLongObject *a, PyLongObject *b)
{
    Py_ssize_t size_a = Py_ABS(Py_SIZE(a)), size_b = Py_ABS(Py_SIZE(b));
    PyLongObject *z;
    Py_ssize_t i;
    digit carry = 0;

    /* Ensure a is the larger of the two: */
    // 确保 a > b 成立
    if (size_a < size_b) {
        { PyLongObject *temp = a; a = b; b = temp; }
        { Py_ssize_t size_temp = size_a;
            size_a = size_b;
            size_b = size_temp; }
    }
    // 创建一个 ob_digit 的长度是 size_a + 1 的 PyLongObject
    // 两个整数相加结果位数肯定不会超过 较大那个数的位数 +1 
    z = _PyLong_New(size_a+1);
    if (z == NULL)
        return NULL;
    for (i = 0; i < size_b; ++i) {
        carry += a->ob_digit[i] + b->ob_digit[i];
        // carry 保存每一位的和(2^30进制的位)
        z->ob_digit[i] = carry & PyLong_MASK;
        // 将非进位部分保存到 z->ob_digit[i]
        carry >>= PyLong_SHIFT;
        // 去除非进位部分 carry 保存的就是进位部分
    }
    for (; i < size_a; ++i) {  //处理 a 中比 b 多出来的位
        carry += a->ob_digit[i];
        z->ob_digit[i] = carry & PyLong_MASK;
        carry >>= PyLong_SHIFT;
    }
    z->ob_digit[i] = carry;
    // 把 carry 放到最高位
    return long_normalize(z);  // 整理元素个数
}
```

计算结果保存在变量 z 中,但是我们申请了 a_size + 1 的 ob_digit 的空间, 所以需要整理. long_normalize(z); 

```C
/* Normalize (remove leading zeros from) an int object.
   Doesn't attempt to free the storage--in most cases, due to the nature
   of the algorithms used, this could save at most be one word anyway. */

static PyLongObject *
long_normalize(PyLongObject *v)
{
    Py_ssize_t j = Py_ABS(Py_SIZE(v));
    Py_ssize_t i = j;

    while (i > 0 && v->ob_digit[i-1] == 0)
        --i;
    if (i != j)
        Py_SIZE(v) = (Py_SIZE(v) < 0) ? -(i) : i;
    return v;
}
```
这里注释说的很明白 只是调整了 (((PyVarObject*)(ob))->ob_size) 的大小 而释放不需要的内存,他说由于算法原因这个只有一个 ob_digit 位(unsigned short),不太在意.保证ob_digit[abs(ob_size)-1]不为零。

### 整数乘法

```C
static PyObject *
long_mul(PyLongObject *a, PyLongObject *b)
{
    PyLongObject *z;

    CHECK_BINOP(a, b);

    /* fast path for single-digit multiplication */
    if (Py_ABS(Py_SIZE(a)) <= 1 && Py_ABS(Py_SIZE(b)) <= 1) {
        // 快速计算,简单乘法
        stwodigits v = (stwodigits)(MEDIUM_VALUE(a)) * MEDIUM_VALUE(b);
        // 调整计算结果
        return PyLong_FromLongLong((long long)v);
    }

    // Karatsuba Multiplication 乘法 复杂度 约等于 n^1.585
    z = k_mul(a, b);
    /* Negate if exactly one of the inputs is negative. */
    // 如果其中一个是负数 那么这个结果就是负数
    if (((Py_SIZE(a) ^ Py_SIZE(b)) < 0) && z) {
        _PyLong_Negate(&z);
        if (z == NULL)
            return NULL;
    }
    return (PyObject *)z;
}

```

[Karatsuba Multiplication](https://en.wikipedia.org/wiki/Karatsuba_algorithm)