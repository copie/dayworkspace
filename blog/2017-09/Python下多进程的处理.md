# Python 下多进程的处理(1)

multiprocessing 是一个多进程的模块。 multiprocessing 提供本地和远程并发。通过子进程而不是线程，来有效的突破 Global Interpreter Lock(全局解释锁)也就是传说中的GIL。由此，这个模块允许，我们充分利用机器上的多个处理器，它运行在 *nix 和 Windows上面。

# Process 类

在 multiprocessing 中，进程通过 创建一个 Process 对象，然后调用 start() 来产生。和 threading.Thread 用法差不多。下面是一个例子：

    from multiprocessing import Process
    import os
    def f(hello):
        print("我是子进程(%s),俺老爹是(%s)"%(os.getpid(),os.getppid()))
    if __name__ == '__main__':
        p = Process(target=f, args=('hello',))
        p.start()
        print("我是老爹(%s),俺孩子是(%s)" % (os.getpid(),p.pid))
        p.join()

## 进程间的通信(同一程序)

### Queue

Queue 克隆至 queue.Queue

    from multiprocessing import Process, Queue

    def f(q):
        q.put(["hello", 88, b"World!"])

    if __name__ == "__main__":
        q = Queue()
        p = Process(target = f,args= (q,))
        p.start()
        print(q.get())
        p.join()

### Pipes

Pipe() 函数返回一对管道连接的对象，默认情况下是双工的。

    from multiprocessing import Process, Pipe

    def f(conn):
        conn.send(["hello",45,b"World!"])
        conn.close()
    if __name__ == '__main__':
        parent_conn, child_conn = Pipe()
        p = Process(target = f, args = (child_conn,))
        p.start()
        print(parent_conn.recv())
        p.join()


## 进程间的同步

多进程有和多线程一样的同步原语，下面是一个用锁来确保一个时间只有一个进程打印到标准输出。


    from multiprocessing import Process, Lock
    def f(hello,lock):
        lock.acquire()
        print(hello)
        lock.release()

    if __name__ == "__main__":
        lock = Lock()
        for num in range(100):
            Process(target=f, args=("Hello World!",lock)).start()

## 进程间的通信(非同一程序)

不是同一程序的通信，我们以前了解到可以用 TCP 协议进行通信 比如 我们的聊天室。程序里面如何进行不同程序间的通信。下面是一个例子(在不同的Python 解释器之间进行通信),这里和低级的 socket 不同的地方在于所有的消息是无损的。

### Server.py

    from multiprocessing.connection import Listener,Client
    import traceback

    def echo_client(conn):
        try:
            while True:
                msg = conn.recv()
                conn.send(msg)
        except EOFError:
            print("连接关闭")
    def echo_server(address,authkey):
        serv = Listener(address,authkey=authkey)
        while True:
            try:
                client = serv.accept()
                echo_client(client)
            except Exception:
                traceback.print_exc()
    if __name__ == "__main__":
        echo_server(('',8888),authkey=b"Hello World!")

### Client.py

    from multiprocessing.connection import Client

    c = Client(('Lenovo', 8888), authkey=b"Hello World!")

    c.send(['Hello World',100,'你好'.encode('utf-8')])
    print(c.recv())


