# python小项目之可以发声的翻译软件

网上有不少的基于 python 的翻译小软件，我这一次写的是一个用有道词典和百度语音完成的一个小小的翻译软件．昨天写的开头语我也不知道为什么忘了保存，我真的也是够了．

废话不多说先来看看代码．

就这些都东西特别的简单

yuyinhechen.py

    #! /usr/bin/python3
    #coding=utf8
    from urllib.request import *
    from urllib.parse import *
    import subprocess
    import json
    import os
    def fayin(tex):
        url="http://tsn.baidu.com/text2audio?"
        grant_type="client_credentials&amp;"
        client_id="hHDSHWjtksGKWSKafN6lcWLc"
        client_secret= "ed83d45b264f79161f78276fbf05aaf9"
        urltok="https://openapi.baidu.com/oauth/2.0/token?"
        urltok=urltok+"grant_type="+grant_type+"&amp;client_id="+client_id+"&amp;client_secret="+client_secret
        ff=urlopen(urltok).read().decode("utf8")
        #print(ff)
        tok=json.loads(ff)['access_token']
        #tex=u'你好呀'
        tex = quote(tex, encoding='utf8')
        lan='zh'
        ctp='1'
        cuid="D0:7E:35:17:B4:C5"
        url=url+'tex='+tex+'&amp;lan='+lan+'&amp;cuid='+cuid+'&amp;ctp='+ctp+'&amp;tok='+tok
        #print(url)
        #subprocess.call (["mpg123"+'-q'+url],shell=True)
        os.system('mpg123 -q "%s"'%(url))
        #print(url)
    if __name__ =="__main__":
        fayin("通往互联网的小船说翻就翻......")


fanyi.py

    #! /usr/bin/python3
    #coding=utf-8

    from urllib.request import*
    from urllib.parse import *
    from urllib.error import *
    import sys
    import json
    import yuyinghecheng
    import os
    def fanyi(n) :

        n = quote(n, encoding='utf8')
        url = u"http://fanyi.youdao.com/openapi.do?keyfrom=pythonfankjjkj1&amp;key=1288254626&amp;type=data&amp;doctype=json&amp;version=1.1&amp;q=" + n
        try:
            fp = urlopen(url)
        except  URLError:
            print("通往互联网的小船说翻就翻......")
            os.system('mpg123 -q "联网失败.mp3"')

            exit(0)
        ff = fp.read().decode("utf8")
        json_lode = json.loads(ff)
        return json_lode['translation'][0]


    if __name__ =="__main__":
        n=''
        if len(sys.argv) &gt; 1:
            for i in range(1,len(sys.argv)):
                n+=" "+sys.argv[i]
            m=fanyi(n)
            print(m)
            yuyinghecheng.fayin(m+"    我们下次再见")
        else:
            print('\n输入q结束翻译\n')
            while 1:
                n=input("请输入：\n")

                if n=='q' and len(n)==1:
                    yuyinghecheng.fayin("拜拜   我还会回来的")
                    exit(0)
                m = fanyi(n)
                print(m)
                yuyinghecheng.fayin(m)


setup.py

    #! /usr/bin/python3
    #coding=utf-8
    from distutils.core import setup

    setup(
        name="fanyi",
        version="1.0",
        py_modules=['fanyi','yuyinghecheng'],
    )

其中的api key 最好换成自己的我的你用的也不方便

联网失败.mp3

http://copie.cn/wp-content/uploads/2016/10/联网失败.mp3