# 安装和配置FTP服务器在REDHAT或centos等linux

FTP 代表文件传输协议。他是由 Abhay Bhushan 撰写，并于1971年发布的。FTP 支持所有的操作系统和浏览器。

他是基于客户端-服务器协议。

## FTP 如何工作

步骤 A: 客户端连接到服务器的 21 端口。
步骤 B: 服务器响应并请求验证。
步骤 C: 客户端决定如何连接主动或者被动并且使用凭据进行身份验证(用户名和密码)。
步骤 D: 如果是主动连接，则服务器打开20端口进行数据传输，并在验证成功后提供FTP提示。
步骤 E: 客服端调用文件，并且服务器启动文件传输。

下图显示了通过FTP传输数据的简单方式。

![FTP传输示意图](https://copie.cn/usr/uploads/2017/09/1925632249.gif)

Before setting up FTP server we have to clear our self about active and passive ftp(这句话不太好理解)

## 为什么 FTP 使用两个端口

正如我们上面说的，FTP使用21端口进行控制，20是进行数据传输的，这是因为很多原因。

1. 分离数据传输路径，使你在文件传输的过程中仍然可以通过控制端口与服务器进行一些通信。
2. 可以启动多个数据连接，而无需中断控制。
3. 服务器决定何时发送数据，这将最大限度的减少服务器的负载增加。

## 主动 FTP 和 被动 FTP 服务之间的区别

Port模式(主动模式)：涉及到的端口号有21和20,当客户端C向服务器端S通过端口21发送请求链接时，服务器端接收连接，并打开一条命令链路。当客户端需要传输数据时，便会通过命令链路向服务器端发送PORT命令请求：我打开了xxx端口，你连接我吧。服务器端接受请求，通过端口号为21向客户端xxx端口建立一条数据传输链路发送数据。

passiv模式(被动模式)：客户端C向服务器端（端口21）发送请求连接，服务器端接收并打开一条命令链路。当客户端需要传输数据时，会通过命令链路像服务器端发送passiv命令：我打开了XXX端口，你连接我吧，服务器端接受请求，从端口1024-5000中随机选择一个端口与客户端建立链接，并发送命令：我打开了XXX端口，你过来链接吧，客户端接受后就向该端口发送数据。

由此可知，port模式是客户端打开一个本地端口，等待服务器端进行数据连接，而passiv模式是由服务器打开一个端口，等待客户端进行数据连接。

我们将在CentOS 7中设置和配置ftp服务器。对于所有基于Redhat的发行版本，如Centos，Fedora，Scientific Linux，Oracle Linux等，此过程是相同的。

## 安装 FTP 到 centos 并 配置
### 安装
    # yum install vsftpd ftp
    # service vsftpd start # 启动FTP 服务
    # chkconfig vsftpd on  # 检查配置文件

----
### 配置

    #vi /etc/vsftpd/vsftpd.conf

    anonymous_enable=NO #不允许匿名登录 
    local_enable=YES    # 允许/etc/passwd 用户登录
    write_enable=YES    # 允许用户写文件 NO 表示只读
----
先运行一下命令在本地：
    $ ftp copie.cn
如果提示
如果想用 root登录 你会遇到以下错误

    ftp: connect: Connection timed out

如果你保证你的 ftp 服务已经开启了，这个时候就有可能是你的防火墙的问题了如果你和我一样是云服务器的话 添加如下安全组(就是开启20和21)

入方向

    允许	自定义TCP	20/21	地址段访问	0.0.0.0/0

出方向

    允许	自定义TCP	20/21	地址段访问	0.0.0.0/0

自己对应着填写在相应的位置

解决上面的问题以后假设你和我一样就想用root登录好吧你又遇到了下面的错误

    530 Permission denied
或
    vsftpd 530 Login incorrect 

好吧这里root被屏蔽了你需要删除以下两个文件里面的root就可以了

    /etc/vsftpd/user_list
    /etc/vsftpd/ftpusers

这样再试发现一切OK

    Connected to copie.cn.
    220 (vsFTPd 3.0.2)
    Name (copie.cn:copie): root
    331 Please specify the password.
    Password:
    230 Login successful.
    Remote system type is UNIX.
    Using binary mode to transfer files.
    ftp> 

现在就成功的以root用户远程登录了

## FTP 常用命令

    > ftp <host> [port]
    > pwd  # 查看当前目录
    > dir  # 查看FTP服务器中的文件及目录
    > mkdir <dirname>
    > cd <dirname>
    > bin # 采用二进制传输，会加快上传和下载速度
    > lcd <local dirname>
    > !dir # 查看本地文件夹的文件和目录
    > !ls  # 查看本地文件夹的文件和目录
    > put <filename> # 上传文件， 文件要在上面设置的目录下面
    > get <filename> # 下载文件
    > delete *.*  # 删除当前目录的所有文件
    > byte # 退出FTP服务器
    > ? # 获取更多命令帮助











