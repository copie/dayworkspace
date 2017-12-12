from concurrent.futures import ThreadPoolExecutor
from concurrent.futures import ProcessPoolExecutor
from multiprocessing.connection import Listener, Client
import multiprocessing


class thread():
    def __init__(self, pro_max=1, th_max=1, func=None):
        self.client = Client(('127.0.0.1', 8888), authkey=b"Hello World!")
        self.pro_pool = multiprocessing.Pool(pro_max)
        self.pro_max = pro_max
        self.th_max = th_max
        if func is None or callable(func) is False:
            raise TypeError("'{}' object is not callable".format(type(func)))
        self.func = func

    def run(self):
        for _ in range(self.pro_max):
            print(_)
            self.pro_pool.apply(self.process)
            self.pro_pool.close()
            self.pro_pool.join()

    def process(self):
        print("hello")
        th_pool = ThreadPoolExecutor(self.th_max)
        while True:
            self.client.send({"status": "get", 'data': None})
            tmp_data = self.client.recv()
            if tmp_data['status'] == 'put':
                args = tmp_data['data']
                th_pool.submit(self.func, *args)
