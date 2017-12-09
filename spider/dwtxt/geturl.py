import requests
from lxml import etree


class getpageurls:
    def __init__(self,url):
        self.url = url
        self.pageurls = {}
        self._xpath = '//*[@id="yulan"]/li/a'
    def __call__(self):
        req = requests.get(self.url)
        html = req.content.decode('utf-8')
        print(html)
        selector = etree.HTML(html)
        content = selector.xpath(self._xpath)
        return {i.attrib:i.text for i in content}