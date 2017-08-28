# python 堆队列(优先队列)算法

## python源码

Source code: [Lib/heapq.py](https://github.com/python/cpython/blob/3.6/Lib/heapq.py)

---

这个模块提供了堆队列算法也就是堆队列算法

Heaps(堆) 就是一个二叉树，他的每一个父亲节点都小于或等于他的任意一个儿子节点，对于所有的 从零开始的 K 我们可以用数组实现就是 heap[k] <= heap[2*k+1] and heap[k] <= heap[2*k+2]，堆的特点就是堆中的最小元素总是根节点也就是 heap[0];

这个 API 与书上的 堆队列算法 有两点不同 ：(a) 从零开始索引，使得索引和子叶节点之间关系不是特别的明显，但是对于 Python 来说是特别方便的。(b) 我们 pop 的是最小值而不是最大的(也就是书上说的min heap)

以上两个特点使得我们可以 用一个 list 来保存 然后 通过 sort 进行维护 就可以了

建立一个堆 可以初始化一个[] ,也可以通过 heapify() 将一个list 初始化成为一个堆

### 他有一下的方法：

> heapq.heappush(heap, item)

将 item 的值 push 到 heap 中

> heapq.heappop(heap)
pop and return  这个堆中 最小的元素 如果堆是一个空堆的化 他会 抛出 IndexError 由于没有 top 这样的方法 如果只想查看的话 用 head[0] 

> heapq.heappushpop(heap, item)

先 push 进去一个 item 然后再 push 出来 一个最小的值 。这是一个组合操作。相当于 heappush() 然后 再 heappop()

> heapq.heapify(x)

转换 list 为 heap ，就地的，线性时间

> heapq.heapreplace(heap, item)

先 pop 出一个值 然后再 push 进去一个 堆的大小不变，如果heap 为空 会抛出 IndexError。

### 这个模块还提供了基于堆的三个通用的功能

> heapq.merge(*iterables,key=None,reverse=False)

将多个列表进行合并，进行堆调整 相当于 sorted(itertools.chain(*iterbles)) 我们知道sorted的返回值是一个可迭代的对象，而 此方法的返回值是一个迭代器。并且这里我们是假设所有的 输入的迭代器都是已经排好序的。
**在3.5的版本里面加入了 key 和 reverse**

> heapq.nlargest(n,iterable,key=None)

这个就是返回 n 大的值 的一个序列

> heapq.nsmallest(n,iterable,key=None)

返回第 n 小的值 的一个序列

## 简单的例子

    >>> def heapsort(iterable):
    ...     h = []
    ...     for value in iterable:
    ...         heappush(h, value)
    ...     return [heappop(h) for i in range(len(h))]
    ...
    >>> heapsort([1, 3, 5, 7, 9, 2, 4, 6, 8, 0])
    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
---
    >>> h = []
    >>> heappush(h, (5, 'write code'))
    >>> heappush(h, (7, 'release product'))
    >>> heappush(h, (1, 'write spec'))
    >>> heappush(h, (3, 'create tests'))
    >>> heappop(h)
    (1, 'write spec')

---


## 理论

                                    0

                    1                                 2

            3               4                5               6

        7       8       9       10      11      12      13      14

    15  16  17    18 19   20  21   22 23   24 25   26  27   28 29  30

