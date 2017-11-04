#耗费的时间:  37.70709681510925
import asyncio
import requests
import time
import random
from aiohttp import ClientSession
xxxxx = 0
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


async def xxx(id):
    global xxxxx
    try:
        async with ClientSession() as session:
            async with session.get('http://acm.hdu.edu.cn/listproblem.php?vol=' + str(id)) as response:
                response = await response.read()
                print(id)
                await asyncio.sleep(1)
    except Exception as e:
        xxxxx += 1
        print(f'失败了{xxxxx}')


def main():
    now1 = time.time()
    print(now1)
    loop = asyncio.get_event_loop()
    tasks = []
    for i in range(1000, 6217):
        tasks.append(asyncio.ensure_future(xxx(i)))
    loop.run_until_complete(asyncio.wait(tasks))
    loop.close()
    now2 = time.time()
    print(now2 - now1)
    print(xxxxx)


if __name__ == '__main__':
    main()
