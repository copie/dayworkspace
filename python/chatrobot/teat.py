# -*- coding: utf-8 -*-
import urllib
import json


def getHtml(url):
    page = urllib.urlopen(url)
    html = page.read()
    return html


if __name__ == '__main__':

    key = '638533d6f5803fa7d49e8a391961cbbc'
    api = 'http://www.tuling123.com/openapi/api?key=' + key + '&info='
    x = 0
    while True:
        # info = input('我: ')
        if x == 0:
            info = '你是不是傻'
        else:
            info = dic_json['text'].encode("utf-8")
        request = api + info

        response = getHtml(request)
        dic_json = json.loads(response)
        print('机器人: ' .decode('utf-8') + dic_json['text'])
        x+=1
        # page = urllib.urlopen(
        #     "http://api.map.baidu.com/location/ip?ak=KrmZxHHwvLnl4Xfyt0FMM\
        #     VzgGLaaxU2j&ip=" + "211.69.16.1" + "&coor=bd09ll")
        # html = page.read()
        # abc = json.loads(html)
        # print abc["address"]
        # print abc["content"]["address"]
        # print abc["content"]["address_detail"]["city"]
        # print abc["content"]["address_detail"]["city_code"]
        # print abc["content"]["address_detail"]["district"]
        # print abc["content"]["address_detail"]["province"]
        # print abc["content"]["point"]["x"]
        # print abc["content"]["point"]["y"]
