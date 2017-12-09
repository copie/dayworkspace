import requests
from lxml import etree
from down_html import down_html
from find4xpath import find4xpath
import logging
from concurrent.futures import ThreadPoolExecutor

# req = requests.get('http://www.80txt.com/txtml_57058.html')
# html = req.content.decode('utf-8')
# selector = etree.HTML(html)
# content = selector.xpath('//*[@id="yulan"]/li/a')
# print(content[0].attrib)
# print(content[0].text)

# req = requests.get("http://www.qiushu.cc/t/57058/15303428.html")
# html = req.content.decode('gb2312',errors='replace')
# html = down_html('http://www.qiushu.cc/t/57058/15303428.html')()
# selector = etree.HTML(html['html'])
# content = selector.xpath('//*[@id="content"]/text()')
# print("\n".join(content).rstrip())
def xia(url):
    xpath = '//*[@id="content"]/text()'
    logging.error(url.text)
    print(url.text)
    down_status = down_html(url.attrib['href'])()
    status, html = down_status['status'],down_status['html']
    if status is True:
        content = find4xpath(html,xpath)
        print("\n".join(content).rstrip())

def main():
    down_status = down_html('http://www.80txt.com/txtml_57058.html')()
    status, html = down_status['status'],down_status['html']
    xpath = '//*[@id="yulan"]/li/a'
    pool = ThreadPoolExecutor(400)
    if status is True:
        anslist = find4xpath(html,xpath)
        l = []
        for url in anslist:
            l.append(pool.submit(xia,url))
        for i in l:
            i.result()
    else:
        print("下载失败可以以后尝试......")

if __name__ == '__main__':
    main()