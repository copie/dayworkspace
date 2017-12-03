import json
import requests


class wordutil:
    def __init__(self):
        self.url = "http://fanyi.youdao.com/openapi.do?keyfrom=youdaomini&key=1877956118&type=data&doctype=json&version=1.1&q="
        self.errorCode = {
            "101": "缺少必填的参数，出现这个情况还可能是et的值和实际加密方式不对应",
            '102': '不支持的语言类型',
            '103': '翻译文本过长',
            '104': '不支持的API类型',
            '105': '不支持的签名类型',
            '106': '不支持的响应类型',
            '107': '不支持的传输加密类型',
            '108': 'appKey无效，注册账号， 登录后台创建应用和实例并完成绑定， 可获得应用ID和密钥等信息，其中应用ID就是appKey（ 注意不是应用密钥）',
            '109': 'batchLog格式不正确',
            '110': '无相关服务的有效实例',
            '111': '开发者账号无效，可能是账号为欠费状态',
            '201': '解密失败，可能为DES,BASE64,URLDecode的错误',
            '202': '签名检验失败',
            '203': '访问IP地址不在可访问IP列表',
            '301': '辞典查询失败',
            '302': '翻译查询失败',
            '303': '服务端的其它异常',
            '401': '账户已经欠费停',
        }
        self.result = ''

    def execfind(self, var):
        req = requests.get(self.url + var)
        text = req.json()
        if text['errorCode'] in self.errorCode:
            self.addword(self.errorCode[text['errorCode']], "red")
            result, self.result = self.result, ''
            return result

        self.addword("[原文]: ", 'blue')
        self.addword(text['query'], 'green')
        self.addbr()
        self.addword("[译文]: ", 'green')
        try:
            self.addword(",".join(text['translation']), 'blue')
            self.addbr()
        except KeyError as e:
            self.addword("翻译失败",'red')
        if "web" in text:
            self.addword('[网络翻译]:',"#CC00FF")
            self.addbr()
            self.addword("翻译内容: ","#4682B4")
            self.addword(text['web'][0]['key'],"#0000CD")
            self.addbr()
            self.addword("翻译结果: ",'#00FFFF')
            self.addword(','.join(text['web'][0]['value']),"#008080")
            self.addbr()
        result, self.result = self.result, ''
        return result    

    def addbr(self):
        self.result += '<br>'

    def addword(self, word, color):
        self.result += f'<font color="{color}">{word}</font>'
