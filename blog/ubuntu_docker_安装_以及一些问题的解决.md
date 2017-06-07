# ubuntu_docker_安装_以及一些问题的解决

## docker安装

我是在ubuntu16.04上面安装的

先决条件1,添加Docker源

    sudo apt-get update

增加CA证书
    
    sudo apt-get install apt-transport-https ca-certificates

添加GPG Key(一种加密手段)

sudo apt-key adv --keyserver hkp://p80.pool.sks-keyservers.net:80 --recv-keys 58118E89F3A912897C070ADBF76221572C52609D

创建docker.list文件

    sudo vim /etc/apt/sources.list.d/docker.list

    #添加Ubuntu16.04LST的入口
    deb https://apt.dockerproject.org/repo ubuntu-xenial main

再次更新源

sudo apt-get update

以防万一，清除过时的源

    sudo apt-get purge lxc-docker

验证下APT是从正确的库源下载应用的

    apt-cache policy docker-engine

至此，可见已经配置好了Docker的源

# 安装aufs驱动linux-image-extra

官方文档如是说：
    For Ubuntu Trusty, Wily, and Xenial, it’s recommended to install the Linux-image-extra kernel package. The linux-image-extra package allows you use the aufs storage driver可以实现容器间可执行文件和运行库的共享。

    sudo apt-get update
    sudo apt-get install linux-image-extra-$(uname -r)
    # 一般都是已经安装好的
# 安装docker
    
    sudo apt-get update
    sudo apt-get install docker-engine

    sudo service docker start

到此已经按装好le
你可以安装一个hello word
关于每一次都用sudo运行docker我感觉没有必要折腾le

# docker 里面的系统网速特别慢

关于docker里面的系统网速特别慢，我开始是以为是我docker里面系统的软件源的问题最后我才发现是DNS的锅只要修改DNS就可以了

关于修改DNS网上比较容易找到答案 我这里就不说了。

由于我最开始用的 pull 的ubuntu 里面没有什么软件 我是通过挂载解决没有软件修改文档的问题

# docker 的基本操作

    sudo docker images
    # 查看已经安装的docker镜像
    sudo docker run -it b863c38e2c29 
    # 运行一个IMAGE ID 为 b863c38e2c29 的一个docker镜像 -it 我也忘了是什么意思了  好像就是什么终端的忘了
    sudo docker run -it b863c38e2c29 bash
    # 启动镜像并且运行bash
    sudo docker run -p 8888:8888 b863c38e2c29 
    # -p 是一个端口的映射 吧docker里面的机器的8888端口映射到宿主机
    # -P 这个是把docker里面的机器的所有端口随机映射到宿主机
    sudo docker run -v ~/:/mnt b863c38e2c29
    # -v  就是一个把宿主机的一个文件夹挂载到docker里的机器里面去 用起来十分方便
    sudo docker commit b863c38e2c29 ubuntu:test
    # commit 一个docker镜像 我们知道docker运行镜像关机以后我们做的一些修改都会不见所以我们就要保存自己的状态了
    sudo docker pull ubuntu
    # 从远程pull一个ubuntu的一个镜像
    # 还要一些命令不是很常用 我这里就没有写出来
    # 如果你感觉pull的速度太慢 你可以找一些中国的docker hub 来用 进行加速  ali的 网易的都不错
# docker 安装ubuntu后

不得不说安装这个ubuntu以后什么都没有啊啊啊 软件什么都没 vi ，nona 都没有 修改源和DNS还浪费了我一些时间
解决文本编辑器的问题我发现中文的文档是乱码的  啊啊啊 不能忍啊 
我们要添加一个软件 locales 这个软件(如果我没有拼错的话)
然后[archlinux安装](http://copie.cn/index.php/archives/archlinuxkde5uefi%E5%AE%89%E8%A3%85%E4%BB%A5%E5%8F%8A%E5%BF%AB%E9%80%9F%E5%AE%89%E8%A3%85.html)
里面有说就是修改/etc/locale.gen文件就可以了按着做就可以了
