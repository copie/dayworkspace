from test1 import thread
import multiprocessing  

manager = multiprocessing.Manager()

Q = manager.Queue()

Q.put(100)
Q.put(100)
Q.put(100)
Q.put(100)
Q.put(100)


def fun(x):
    print(x)
    for _ in range(x):
        pass
    print(x)
th = thread(2,1,Q,fun)
# th.run()

