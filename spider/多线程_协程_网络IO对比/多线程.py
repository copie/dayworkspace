#耗费的时间:  68.68158459663391
import requests
import time
import threading
import queue
import atexit
now = time.time()
print(now)
querystring = {"pid": "1000"}
url = "http://acm.hdu.edu.cn/showproblem.php"
headers = {
    'host': "acm.hdu.edu.cn",
    'connection': "keep-alive",
    'cache-control': "no-cache",
    'user-agent': "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/62.0.3202.75 Safari/537.36",
    'upgrade-insecure-requests': "1",
    'accept': "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8",
    'referer': "http://acm.hdu.edu.cn/listproblem.php?vol=1",
    'accept-encoding': "gzip, deflate",
    'accept-language': "zh-CN,zh;q=0.9,en;q=0.8",
}
qq = queue.Queue()


def ss():
    while True:
        if qq.empty() is False:
            i = qq.get()
            querystring["pid"] = str(i)
            try:
                response = requests.request(
                    "GET", url, headers=headers, params=querystring, timeout=2)
                x = response.text
                if response.status_code == 200:
                    print(i)
                    if i % 1000 == 0:
                        print(x)
            except:

                print(f'第{i}个URL超时了从新加入下载队列   还有{qq.qsize()}')
                qq.put(i)
        else:
            break


def func(now):
    now2 = time.time()
    print(now2 - now)


atexit.register(func, now)
for i in range(1000, 6217):
    qq.put(i)
for _ in range(150):
    x = threading.Thread(target=ss, args=())
    x.start()
