from test1 import thread
import multiprocessing
from queueserver import server
from multiprocessing.connection import Client


client = Client(('127.0.0.1', 8888), authkey=b"Hello World!")

client.send({"status": 'put', 'data': 100})
client.send({"status": 'put', 'data': 18})
client.send({"status": 'put', 'data': 99})
client.send({"status": 'put', 'data': 88})
client.send({"status": 'put', 'data': 77})


def fun(x):
    print(x)
    for _ in range(x):
        pass
    print(x)


th = thread(2, 1, fun)
th.run()
