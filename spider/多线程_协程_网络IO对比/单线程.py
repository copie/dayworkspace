# 耗费的时间: 1104.5710740089417
import requests
import time
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
for i in range(1000, 6217):
    querystring["pid"] = str(i)
    response = requests.request(
        "GET", url, headers=headers, params=querystring)
    x = response.text
    if response.status_code == 200:
        print(i)
now2 = time.time()
print(now2 - now)
