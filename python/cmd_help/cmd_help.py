import requests
import re
import sys

headers = {
    'Host': 'linux.51yip.com',
    'Connection': 'keep-alive',
    'Cache-Control': 'max-age=0',
    'Upgrade-Insecure-Requests': '1',
    'User-Agent': 'Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/62.0.3202.62 Mobile Safari/537.36',
    'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',
    'Referer': 'http://linux.51yip.com/search/cd',
    'Accept-Encoding': 'gzip, deflate',
    'Accept-Language': 'zh-CN,zh;q=0.9'
}
try:
    key = sys.argv[1]
except IndexError:
    key = input("请输入需要查询的命令: ")

text = requests.get("http://linux.51yip.com/search/"+key)
x = text.content.decode('utf-8').replace('&nbsp;', ' ').replace("&quot;",
                                                                '\"').replace("&amp;", "&").replace('&lt;', '<').replace('&gt;', '>')
com = re.compile(r"<pre>.*<\/pre>")

tmp = com.findall(x)[0]
tmp = tmp.replace("<p>", '\n')
tmp = tmp.replace("</p>", '\n')
tmp = tmp.replace("<pre>", '')
tmp = tmp.replace("</pre>", '')
tmp = tmp.replace('<pre class="back_ground">', '')
tmp = tmp.replace('<br />', '\n')
print(tmp)
