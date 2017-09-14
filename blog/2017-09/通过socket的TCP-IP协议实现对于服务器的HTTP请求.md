# 通过socket的TCP-IP协议实现对于服务器的HTTP请求

以前一直没有搞懂 http 协议到底是一个什么玩意。并且认为 socket tcp/ip 以及 http 他们没有关系的，今天刚刚好写了一个简单的程序好像一下就懂了好多东西。

这个代码就是通过 创建一个 tcp 的套接字 然后通过这个套接字 向服务器发起 http GET 请求 得到的结果和用requests.get() 获取的结果一样.~~不过还有一些乱码我现在还不能解决~~。

## 代码

    from socket import *

    HOST = "www.omgubuntu.co.uk"
    PORT = 80
    ADDR = (HOST,PORT)

    cli = socket(AF_INET,SOCK_STREAM)
    cli.connect(ADDR)

    get_str ='''GET / HTTP/1.1
    Host: www.omgubuntu.co.uk
    Connection: keep-alive
    Cache-Control: max-age=0
    User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.79 Safari/537.36
    Upgrade-Insecure-Requests: 1
    Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8
    Referer: https://www.baidu.com/s?tn=59046333_1_dg&isource=infinity&wd=omgubuntu
    Accept-Encoding: deflate
    Accept-Language: zh-CN,zh;q=0.8,en;q=0.6

    '''
    cli.settimeout(0.3)
    cli.send(get_str.encode("utf-8"))
    buf=cli.recv(1024)
    while len(buf):
        try:
            buf += cli.recv(1024)
        except:
            with open('1.txt','wb') as file:
                print(buf)
                file.write(buf)
                break


## 返回结果

    HTTP/1.1 200 OK
    Server: nginx
    Date: Thu, 14 Sep 2017 06:11:41 GMT
    Content-Type: text/html
    Transfer-Encoding: chunked
    Connection: keep-alive
    Vary: Accept-Encoding
    Set-Cookie: w3tc_referrer=https%3A%2F%2Fwww.baidu.com%2Fs%3Ftn%3D59046333_1_dg%26isource%3Dinfinity%26wd%3Domgubuntu; path=/
    Set-Cookie: w3tc_referrer=https%3A%2F%2Fwww.baidu.com%2Fs%3Ftn%3D59046333_1_dg%26isource%3Dinfinity%26wd%3Domgubuntu; path=/
    Last-Modified: Thu, 01 Jan 1970 00:00:00 GMT
    Expires: Thu, 14 Sep 2017 07:11:41 GMT
    Pragma: public
    Cache-Control: max-age=3600, public, must-revalidate, proxy-revalidate
    ETag: "c4aa3c5d2f7e7b29123febf007f20094"

    be00
...

    <!DOCTYPE html>
    <html lang="en-US" prefix="og: http://ogp.me/ns#">
    <head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="chrome=1">
    <title>OMG! Ubuntu! - Ubuntu Linux News, Apps and Reviews</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="theme-color" content="#f15d22">
    <link rel="alternate" href="android-app://com.ohso.omgubuntu/omg-ubuntu/index">
    <meta property="fb:app_id" content="272768256180082">
    <link rel="shortcut icon" href="http://www.omgubuntu.co.uk/wp-content/themes/omgubuntu-theme-3.6.1/images/favicon.ico">
    <link rel="apple-touch-icon-precomposed" href="http://www.omgubuntu.co.uk/wp-content/themes/omgubuntu-theme-3.6.1/images/appicons/57.png"><!--60X60-->

我们看到了服务器给我们的返回值，这个和我们通过浏览器获得的一样

还有就是为什么我开始的时候会出现乱码通过我分析我的请求的时候用到了gzip的压缩(Accept-Encoding: gzip, deflate, br
)所以我直接打开的时候就会出现乱码了

通过这个例子可以让人更好的理解socket，TCP/IP与HTPP的关系