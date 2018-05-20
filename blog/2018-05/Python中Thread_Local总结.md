# Python 中 Thread Local 总结
有时候在多线程程序中,我们需要保存专属于当前运行线程的状态.为了做到这一点,可以通过 threading.local() 来创建一个线程本地存储对象,在这个对象上保存和读取的属性对当前运行的线程可见, 其他线程无法感知.

## Thread Local

```Python
import threading
from functools import partial
from socket import AF_INET, SOCK_STREAM, socket


class LazyConnection:
    def __init__(self,address):
        self.address = address
        self.family = AF_INET
        self.type = SOCK_STREAM
        self.local = threading.local()

    def __enter__(self):
        if hasattr(self.local, 'sock'):
            raise RuntimeError("已经连接成功了")
        self.local.sock = socket(self.family, self.type)
        self.local.sock.connect(self.address)
        return self.local.sock
    
    def __exit__(self, exc_ty, exc_val, tb):
        self.local.sock.close()
        del self.local.sock


def test(conn):
    with conn as s:
        s.send(b"GET /index.html HTTP/1.0\r\n")
        s.send(b"Host: www.python.org\r\n")
        s.send(b"\r\n")
        resp = b"".join(iter(partial(s.recv, 8192),b""))
    
    print(f"GOT {len(resp)} bytes")



if __name__ == '__main__':
    conn = LazyConnection(("www.python.org", 80))
    t1 = threading.Thread(target=test,args=(conn,))
    t2 = threading.Thread(target=test,args=(conn,))
    t1.start()
    t2.start()
    t1.join()
    t2.join()   
```

这样能够正常工作的原因在于每个线程实际上是创建了自己专属的 socket 连接(以 self.local.sock 的形式保存). 因此,当不同的线程在 socket 上执行操作时,他们并不会产生相互影响,因为他们在不同的socket 上完成操作.

## 讨论

在大部分程序中, 创建和操作线程专有的状态都不会出现问题. 但是万一出现问题了, 通常使用为多个线程使用同一个对象,而这个对象操作某种系统资源, 比如说 socket 或者文件. 我们不能让一个单独的 socket 对象被所有线程共享, 因为如果有多个线程同时对 socket 进行读写, 那么就会出现混乱. 线程专属存储通过让这种专属资源只对一个线程可见,解决了这个问题.

在底层, threading.local() 实例为每个线程维护着一个单独的实例字典. 所有对示例的常见操作比如获取,设定以及删除都只是作用于每个线程专属的字典上.每个线程使用一个单独的字典真是这一事实使得不同线程的数据得到隔离. 