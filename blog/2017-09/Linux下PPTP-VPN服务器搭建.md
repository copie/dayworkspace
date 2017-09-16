# Linux下PPTP-VPN服务器搭建

学校的网络环境太差了， 多人不允许用一个路由器，而且有一些网站不能够访问，比如说在我们学校网页的qq快捷登录是不能用的。有时候特别麻烦。刚好自己手里有一台阿里云的服务器，虽然网速不快但是，不会有一些网站不能访问的尴尬了(由于我的服务器在国内所以......)

## 安装pptp软件

    yum install -y ppp pptpd # 这里用的就是个软件 不同发行版命令不同但是包名相同

## 更改配置文件

修改 /etc/pptpd.conf 其中一下的两行

    localip 192.168.0.1    # vpn 的网关地址
    remoteip 192.168.0.234-238,192.168.0.245    #  vpn 拨号获取地址段

修改 /etc/ppp/options.pptpd 添加 DNS 服务器

    ms-dns 119.29.29.29
    ms-dns 182.254.116.116 # 可以修改为自己想要的DNS服务器
    logfile /var/log/pptpd.log # log文件位置

修改 /etc/ppp/chap-secrets 用来设置 pptpd 的用户和密码

    # Secrets for authentication using CHAP
    # client        server      secret                  IP addresses
    yonghuming      pptpd       mima                       *

## 内核修改

修改 /etc/sysctl.conf 将 net.ipv4.ip_forward=0 改成 net.ipv4.ip_forward=1 如果没有就添加一个

    net.ipv4.ip_forward=1
然后执行命令

    sysctl -p

使修改后的参数

添加 iptables 转发规则:


    iptables -t nat -A POSTROUTING -s 192.168.0.0/24 -o eth0 -j MASQUERADE
    # 这样你就可以访问远程的内网了 但是我还要访问外网 这里的192.168.0.0/24和ech0 按需修改
    iptables -t nat -A POSTROUTING -s 192.168.0.0/24 -j SNAT --to-source 106.14.222.191
    # 这样的话就可以访问远程的外网了 我们的目的也就达成了。106.14.222.191 是我的服务器的公网IP

## 修改防火墙

由于我用的是阿里云的服务器 所以我只要在服务器控制台添加规则就可以了。如果你是实体机的话想办法打开1723端口就可以了。

    入方向
    允许	自定义 TCP	1723/1723	地址段访问	0.0.0.0/0
    出方向
    允许	自定义 TCP	1723/1723	地址段访问	0.0.0.0/0


## 系统自动启动pptp的vpn server

    systemctl start pptpd
    systemctl enable pptpd

## 查看log文件

    Connect: ppp1 <--> /dev/pts/2
    peer from calling number 218.28.63.101 authorized
    MPPE 128-bit stateless compression enabled
    Cannot determine ethernet address for proxy ARP
    local  IP address 192.168.0.1
    remote IP address 192.168.0.235
    Modem hangup
    Connect time 1.0 minutes.
    Sent 3144847 bytes, received 539804 bytes.
    MPPE disabled
    Connection terminated.

大概就是这样的