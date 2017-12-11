from concurrent.futures import ThreadPoolExecutor
from concurrent.futures import ProcessPoolExecutor
import multiprocessing


class thread():
    def __init__(self, pro_max = 1, th_max = 1, args_queue = None,func=None):
        self.pro_pool = ProcessPoolExecutor(pro_max)
        self.kill_flag = False
        self.pro_max = pro_max
        self.th_max = th_max
        if isinstance(args_queue,multiprocessing.Manager.Queue) is True:
            self.queue = args_queue
        else:
             raise ValueError("invalid literal for {}() with \"{}\"".format(self.__class__.__name__,str(queue)))
        if func is None or callable(func) is False:
            raise TypeError("'{}' object is not callable".format(type(func)))
        self.pro_pool.submit(self.process)
        
    # def run(self):
    #     for _ in range(self.pro_max):
    #         self.pro_pool.submit(self.process)

    def process(self):
        print("hello")
        # th_pool = ThreadPoolExecutor(self.th_max)
        # while True:
        #     if self.kill_flag is True:
        #         return
        #     args = self.queue.get()
        #     print(args)
        #     if isinstance(args,tuple):
        #         args,kwages = args
        #     else:
        #         kwages = {}
        #     th_pool.submit(self.func,*args,**kwages)

