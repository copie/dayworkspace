'''本模块是为了解决获取百家号url并且从这个url里面获取我们想要的新闻'''
import re
import time

import bs4
import requests
from selenium import webdriver


class sobaidu():
    '''sobaidu类实现通过百度搜索获取真实的url并且把url写入数据库'''

    def __init__(self):
        self.KEYFILENAME = "keylist.txt"
        self.URLFILENAME = "urllist.txt"
        self.KEYLIST = set()
        self.URLLIST = set()
        self.URLFILE = open(self.URLFILENAME, 'w')
    def _readkey(self):
        '''读取百度搜索所需要的所有关键词'''
        with open(self.KEYFILENAME) as keyklistfile:
            for i in keyklistfile.readlines():
                self.KEYLIST.add(i)
    def _changeurl(self,url):
        '''百度搜索结果url转换为真实的url'''
        try:
            req = requests.get(url+'&wd=')
            # time.sleep(1)
            # print(req.text)
            regx = r'http[s]*://baijiahao.baidu.com/[\S]*id=[0-9]*'
            pattern = re.compile(regx)
            match = re.findall(pattern, req.text)
            return match[0]
        except Exception as e:
            print(e)
    def _writetomysql(self):
        '''将真实url写入数据库'''
        pass
    def _writetofile(self,url):
        self.URLFILE.write(url)
        self.URLFILE.write('\n')

    def sobaidu(self):
        '''调用以上函数解决我们的问题'''
        # browser = webdriver.Chrome()
        browser = webdriver.PhantomJS()
        num = 0
        for key in self.KEYLIST:
            ''''doc'''
            num += 1
            now_num = 0
            browser.implicitly_wait(30)
            browser.get('https://www.baidu.com/s?wd=site:(baijiahao.baidu.com) '+ key )
            
            while True:
                if now_num == 1:
                    try:
                        browser.find_element_by_xpath('//*[@id="page"]/a[10]').click()
                        time.sleep(2)
                    except Exception as e:
                        print(e)
                        print("有问题")
                        break
                now_num += 1
                print(now_num)
                source = browser.page_source
                soup=bs4.BeautifulSoup(source,'lxml')
                print('next_page')
                for i in soup.findAll(class_='result c-container '):
                    url=i.find(class_='t').find('a').get('href')
                    # print(url)
                    # self.URLLIST.add(self._changeurl(url))
                    self._writetofile(self._changeurl(url))
                time.sleep(1)
                if now_num > 1:
                    try:
                        browser.find_element_by_xpath('//*[@id="page"]/a[11]').click()
                        time.sleep(1)
                    except:
                        print('not find next_button may be for the page end!!!')
                        break
def main():
    dsfsd = sobaidu()    
    # strings = dsfsd._changeurl('https://www.baidu.com/link?url=w8wWEQMyVf0cD3TsKcn_pTQZ92cIqLqxVZKWFtT4rYJcESE_qfhKlPJg5B7OM2mXhZoSM1H0ogmCIgi4G2EkP_&wd=&eqid=aa2c3db90000bf4c0000000458831761') 
    # print(strings)
    # # ###################### 奇怪的分割线 ###############
    dsfsd._readkey()
    print(len(dsfsd.KEYLIST))
    #########################  有点傻的分割线 #############
    dsfsd.sobaidu()
    # print(len(dsfsd.URLLIST))
    # for i in dsfsd.URLLIST:
    #     print(i)
    dsfsd.URLFILE.close()
if __name__ == '__main__':
    main()