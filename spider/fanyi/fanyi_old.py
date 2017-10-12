#coding=utf8
import urllib.request
import urllib.parse
import json
xuyaofanyide=input()
url='http://fanyi.youdao.com/translate?smartresult=dict&smartresult=rule&smartresult=ugc&sessionFrom=http://www.youdao.com/'
head={}
head['User-Agent']='Mozilla/5.0 (Windows NT 10.0; WOW64)AppleWebKit/537.36 (KHTML, like Gecko) Chrome/47.0.2526.80 Safari/537.36'
head['']
data ={}
data['type']='AUTO'
data['i']= xuyaofanyide
data['doctype']='json'
data['xmlVersion']='1.8'
data['keyfrom']='fanyi.web'
data['ue']='UTF-8'
data['action']='FY_BY_ENTER'
data['typoResult']='true'
data=urllib.parse.urlencode(data).encode('utf-8')
req = urllib.request.Request(url,data,head)
respomse = urllib.request.urlopen(req)
html = respomse.read().decode('utf-8')
target = json.loads(html)

print(target['translateResult'][0][0]['tgt'])
