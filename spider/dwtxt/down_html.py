import requests
from header import header
import re
from queue import Queue
import chardet


class down_html:
    def __init__(self, url):
        self.url = url
        self.host = re.search(
            '^(http[s]?:\/\/)?((www.)?[\w]+(\.\w*)+)', self.url).groups()[1]
        self.header = header()(self.host)
        self.proxies = {}
        self.status = True

    def __call__(self):
        try:
            req = requests.get(self.url, headers=self.header,
                               timeout=10, proxies=self.proxies)
        except requests.ConnectTimeout or requests.exceptions.ReadTimeout as e:
            print(f"链接{self.url}已经超时")
            self.status = False
            return {"status": self.status, 'html': ''}
        try:
            encodeing = chardet.detect(req.content)['encoding']
            html = req.content.decode(encodeing, errors='replace')
        except Exception as e:
            print(e)
            print("编码时错误,具体错误不定......")
            self.status = False
            return {"status": self.status, 'html': ''}
        return {"status": self.status, 'html': html}
