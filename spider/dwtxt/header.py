'''一个生成请求头的模块,这个请求头会自动随机UA 自定义其他选项可以自己写
    In [1]: from header import header
    In [2]: head = header()
    In [3]: head("www.baidu.com")
    Out[3]:
    {'accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',
    'accept-encoding': 'gzip, deflate',
    'accept-language': 'zh-CN,zh;q=0.9,en;q=0.8',
    'cache-control': 'no-cache',
    'connection': 'keep-alive',
    'host': 'www.baidu.com',
    'upgrade-insecure-requests': '1',
    'user-agent': 'Mozilla/4.0 (compatible; MSIE 5.5; Windows NT 4.0; H010818)'}
    In [17]: head.headers["cookie"] = "BAIDUID=BD7EFE017419912ADC91815DD9EB4E49:FG=1;"
    In [19]: head("www.baidu.com")
    Out[19]:
    {'accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',
    'accept-encoding': 'gzip, deflate',
    'accept-language': 'zh-CN,zh;q=0.9,en;q=0.8',
    'cache-control': 'no-cache',
    'connection': 'keep-alive',
    'cookie': 'BAIDUID=BD7EFE017419912ADC91815DD9EB4E49:FG=1;',
    'host': 'www.baidu.com',
    'upgrade-insecure-requests': '1',
    'user-agent': 'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 1.1.4322; MSN 9.0;MSN 9.1; MSNbMSNI; MSNmen-us; MSNcIA)'}
'''
from random_line import randomline
from copy import deepcopy


class header:
    def __init__(self):
        self.headers = {
            'host': "",
            'connection': "keep-alive",
            'cache-control': "no-cache",
            'user-agent': "",
            'upgrade-insecure-requests': "1",
            'accept': "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8",
            'accept-encoding': "gzip, deflate",
            'accept-language': "zh-CN,zh;q=0.9,en;q=0.8"
        }
        self.ua = randomline("./user_agent.txt")

    def wwwqiushucc(self, host):
        '''www.qiushu.cc 的专用请求头'''
        header = deepcopy(self.headers)
        header['user-agent'] = self.ua.line
        header['host'] = host
        return header

    def default(self, host):
        '''如果没有定义一个网站专用的头的话这里提供了一个默认的头'''
        header = deepcopy(self.headers)
        header['user-agent'] = self.ua.line
        header['host'] = host
        return header

    def __call__(self, host):
        return self.get(host)

    def get(self, host):
        """获取UA,如果有这个网站的UA定义的话会用这个否则的话使用默认"""
        host = host.replace(":", "")
        return getattr(self, host)(host) if hasattr(self, host) else getattr(self, "default")(host)
