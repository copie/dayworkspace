from concurrent.futures import ThreadPoolExecutor
from concurrent.futures import ProcessPoolExecutor
from queue import Queue

pool = ProcessPoolExecutor(4)
Q = Queue()
def thr():
    pool = ThreadPoolExecutor(100)
    while True:
        if Q.empty() is False:
            x = Q.get()
            pool.submit(pao,x)
        else:
            return

def pao(url):
    for i in range(url):
        pass
    print(url)


for i in range(100000):
    Q.put(i)
for i in range(4):
    pool.submit(thr)