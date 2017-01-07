from selenium import webdriver


def writetofile(filename, cookies):

    with open(filename, 'w') as file:
        file.writelines(str(cookies))
    file.close()


browser = webdriver.Chrome()
browser.get('https://www.adidas.com.cn/customer/account/login/')
# set_page_load_time()
elem = browser.find_element_by_xpath('//*[@id="email"]')
elem.send_keys('copie')
# 查找用户名输入栏并输入用户名
elem = browser.find_element_by_xpath('//*[@id="pass"]')
elem.send_keys('copyist')
elem = browser.find_element_by_xpath('//*[@id="send2"]')
elem.click()
# 点击登录按钮
elem = browser.find_element_by_xpath('/html/body/div[7]/div/div[2]/div[2]/div/div/a')
elem.click()
elem = browser.find_element_by_xpath('//*[@id="product_addtocart_form"]/div[1]/div[1]/div[1]/div[2]')
elem.click()
elem = browser.find_element_by_xpath('//*[@id="product_addtocart_form"]/div[1]/div[1]/div[2]/div/span[3]')
elem.click()
elem = browser.find_element_by_xpath('//*[@id="product_addtocart_form"]/div[1]/div[2]/div[1]/div[2]')
elem.click()
elem = browser.find_element_by_xpath('//*[@id="buy_now"]')
elem.click()

cookies = browser.get_cookies()

writetofile('cookie.txt', cookies)
