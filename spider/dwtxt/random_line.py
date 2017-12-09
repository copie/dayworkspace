''' 这个模块是实现随机获取文件一行
    这个模块将文件全部加载到了内存所以要注意文件的大小
    In [1]: from random_line import randomline
    In [3]: x = randomline("./user_agent.txt")
    In [4]: x.line
    Out[4]: 'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; FunWebProducts; GTB5; SIMBAR={57CBC72A-E249-4AF8-959B-FEF1064F0
    CD6}; .NET CLR 1.0.3705; .NET CLR 1.1.4322; Media Center PC 4.0)\n'
    In [5]: x.line
    Out[5]: 'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.0; snprtz|T16614000000594|2195#Service Pack 4#2#5#0; .NET CLR 1.1.4322; .NET CLR 2.0.50727)\n'
'''
import os
import random


class randomline:
    def __init__(self,file_name):
        self.file_name = file_name
        self.file = open(self.file_name,'r',encoding='utf-8',errors='ignore')
        self.lines = self.file.readlines()
    @property
    def line(self):
        return random.choice(self.lines).strip()

