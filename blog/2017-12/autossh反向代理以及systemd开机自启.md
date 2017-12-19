# autossh 反向代理以及 systemd 开机自启

前几天想着用反向代理我自己使用的笔记本,不要问我问什么.闲的.尴尬

之前我翻遍里百度的所有的搜索结果一直都没有成功,差点就要放弃了.今天刚好使用的国外的代理可以用了直接找到一篇很好用的blog一下就可以了好烦.

这里记录一下我自己如何用autossh 进行反向代理的.

## Systemd Unit File

创建autossh的 Systemd Unit File

    sudo vim /lib/systemd/system/autossh.service

将下面的文本写入文件

    [Unit]
    Description=autossh
    Wants=network-online.target
    After=network-online.target

    [Service]
    Type=simple
    User=用户
    EnvironmentFile=/etc/default/autossh
    ExecStart=
    ExecStart=/usr/bin/autossh $SSH_OPTIONS
    Restart=always
    RestartSec=60

    [Install]
    WantedBy=multi-user.target

## Environment File

创建一个环境变量文件

    sudo vim /etc/default/autossh

讲下面的文本按照自己的需求写入文件

    AUTOSSH_POLL=60
    AUTOSSH_FIRST_POLL=30
    AUTOSSH_GATETIME=0
    AUTOSSH_PORT=22000
    SSH_OPTIONS="-N -R 2222:localhost:22 example.com -i /home/autossh/.ssh/id_rsa"

这个是将本地的22端口映射到远程的2222端口不要弄错了

/home/autossh/.ssh/id_rsa 这个文件是什么 可以去搜一下 ssh 免密登录自行了解

## Start the Service

创建开机自启的文件

    sudo systemctl daemon-reload

重新加载一下 Systemd Unit File

    sudo systemctl start autossh

现在就可以启动autossh了

    sudo systemctl status autossh

查看 autossh 的启动的状态

    ● autossh.service - autossh
    Loaded: loaded (/usr/lib/systemd/system/autossh.service; enabled; vendor preset: disabled)
    Active: active (running) since Tue 2017-12-19 19:11:42 CST; 1h 2min ago
    Main PID: 1600 (autossh)
        Tasks: 2 (limit: 4915)
    CGroup: /system.slice/autossh.service                                                                                                 
            ├─1600 /usr/bin/autossh -N -R 6000:127.0.0.1:200 test@copie.cn -i /home/test/.autossh/id_rsa                                   
            └─2337 /usr/bin/ssh -L 22000:127.0.0.1:22000 -R 22000:127.0.0.1:22001 -N -R 6000:127.0.0.1:200 -i /home/test/.autossh/id_rsa root@copie.cn                                                                                                         
    12月 19 19:22:10 copie autossh[1600]: starting ssh (count 30)                                                     
    12月 19 19:22:10 copie autossh[1600]: ssh child pid is 2256                                                                           
    12月 19 19:22:10 copie autossh[1600]: ssh: Could not resolve hostname copie.cn: Name or service not known                       
    12月 19 19:22:10 copie autossh[1600]: ssh exited with error status 255; restarting ssh                                
    12月 19 19:22:13 copie autossh[1600]: starting ssh (count 31)                              
    12月 19 19:22:13 copie autossh[1600]: ssh child pid is 2257
    12月 19 19:22:13 copie autossh[1600]: ssh: Could not resolve hostname copie.cn: Name or service not known
    12月 19 19:22:13 copie autossh[1600]: ssh exited with error status 255; restarting ssh
    12月 19 19:22:18 copie autossh[1600]: starting ssh (count 32)                                                                         

这样的话就已经代理成功了.

你可以远程登录到自己的远程服务器访问一下 127.0.0.1:200 具体端口看一下自己的需求. 是不是已经可以了
在我的服务器上面这样还是不可以使用公网IP进行访问.然后在公网服务器上进行正向代理就可以了
由于我的服务器N多年也不关机所以我就直接运行下面这个命令进行了临时的一个代理如果你想开机自启的话也可以仿照上面的方法自己写一个就可以了

    ssh -fCNL *:2000:127.0.0.1:200 127.0.0.1

这个将200 端口正向代理到了 2000

这样就可以美滋滋的使用了.

## 注意

1. 如果不嫌麻烦的换可以新建一个用户进行反向代理.毕竟安全点
2. 我这里只是写了具体的怎么操作使用,如果不了解 什么是 systemd, ssh 和 autossh自己去了解一下.
3. 我这里自己是成功了而且是开机可以自启(我在百度上面看别人写的都是一个套路然后一直开机自启失败)
4. 我这里是对一篇英语的博文进行了简单的翻译如果你想看[原文](http://logan.tw/posts/2015/11/15/autossh-and-systemd-service/)
5. 现在国内的技术blog很多都是一样的.完全没有新意.要出问题都出问题.很尴尬.

