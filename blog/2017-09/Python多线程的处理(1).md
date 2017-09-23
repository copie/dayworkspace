# Python 下多线程的处理(1)

由于　Python 下的多线程的东西比较多。我呢就总结一些比较常用的一些方法。其他的可以去查官方文档。

## 两种实现方法

### 继承Thread类

第一种实现方法是 继承 Thread 类，并重写 run() 对象

    from threading import Thread, RLock

    count = 0

    class mythread(Thread):

        def __init__(self, lock, threadName):
            super(mythread, self).__init__(name=threadName)
            self.lock = lock
        def myp(self,count):
            self.lock.acquire()
            print(count)
            self.lock.release()

        def run(self):
            global count
            for _ in range(5):
                self.lock.acquire()
                print(self.getName())
                # 输出当前线程的名字
                count += 1
                self.myp(count)
                self.lock.release()

    lock = RLock()
    for i in range(5):
        mythread(lock, '线程-' + str(i)).start()

注意我这里用的是 RLock 进行线程的同步， 如果 Lock 这样写的话会造成 死锁。下面会有对比

### 另一种方法

直接生成 Thread 的对象

    from threading import Thread, RLock

    def sayHello(lock,hello):
        rlock.acquire()
        print(hello)
        rlock.release()

    if __name__ == "__main__":

        rlock = RLock()
        th_List = [Thread(target=sayHello,args=(rlock,"Hello World!",)) for _ in range(10)]
        list(map(lambda x:x.start(),th_List))

这里我新建了 10 个线程，然后通过 start() 方法启动他。

## Lock() 与 RLock() 的区别

先看代码 然后讲解 可以将示例一的代码吧 RLock 改成 Lock 体验一下。

    from threading import Thread, Lock

    def sayhello0(lock,hello):
        lock.acquire()
        print(hello)
        sayhello1(lock,"你好，世界!")
        lock.release()

    def sayhello1(lock,hello):
        lock.acquire()
        print(hello)
        lock.release()

    if __name__ == "__main__":
        lock = Lock()
        t = Thread(target=sayhello0, args=(lock,"Hello World!",))
        t.start()
输出:

    Hello World!

并且已经出现了死锁 程序已经被锁死了

现在我们将 Lock 改为 RLock 看一下输出

    Hello World!
    你好，世界!

这样的话就和我们想的一样了

这两种锁的不同之处在于：

RLock 允许同一个线程中被多次acquire。而 Lock 不允许这种情况。如果使用 RLock ,那么 acquire 和 release 必须是成对出现的。

## 线程间的通信

将数据从一个线程发往另一个线程 最安全的方法也许就是用 queue 模块中的 Queue(队列)了。

    from threading import Thread
    from queue import Queue

    def producer(out_q):
        # 一个生产数据的线程
        for i in range(100):
            print("我制造了%d"%(i))
            out_q.put(i)

    def consumer(in_q):
        # 一个消费数据的线程
        for _ in range(100):
            print(in_q.get())

    if __name__ == "__main__":
        q = Queue()
        t1 = Thread(target=consumer, args=(q,))
        t2 = Thread(target=producer, args=(q,))
        t1.start()
        t2.start()
---

多线程的东西很多我平时用到的也就这些。还有别的用到再说。
