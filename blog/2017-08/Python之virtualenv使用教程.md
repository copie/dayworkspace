# Python之virtualenv使用教程

Python 的第三方的包太多了。我们 Python 用的时间越长我们的电脑上面会出现一些我们忘了为什么会用到这些包。还会出现一些包的依赖问题。所以我们有了virtualenv， 可以搭建一个虚拟的而且独立的Python 环境。这样以来我们的每一个项目都是很离开来的很是方便。**虽然是独立的但是这个打包出来是不能跨平台的** 

## 安装pip

使用pip安装 virtualenv，如果你的python环境没有pip的话需要安装pip比如debian系列用一下命令

    sudo apt install python3-pip

当然你还可以通过源码包来安装pip的

    # 下载源码
    wget --no-check-certificate https://github.com/pypa/pip/archive/9.0.1.tar.gz

    # 解压文件
    tar -zvxf 9.0.1 -C pip-9.0.1

    cd pip-9.0.1

    # 使用python3 安装pip3

    python3 setup.py install


创建链接：

    sudo ln -s /usr/local/python3/bin/pip /usr/bin/pip3

升级pip

    pip install --upgrade pip

## 安装Virtualenv

    sudo pip3 install virtualenv

## virtualenv基本使用

    virtualenv mypython # 创建一个虚拟环境
        
        Using base prefix '/usr'
        New python executable in /home/copie/mypython/bin/python3
        Also creating executable in /home/copie/mypython/bin/python
        Installing setuptools, pip, wheel...done.

    cd mypython
    ll

        总用量 24
        drwxrwxr-x  5 copie copie 4096 8月  20 22:35 ./
        drwxr-xr-x 31 copie copie 4096 8月  20 22:35 ../
        drwxrwxr-x  2 copie copie 4096 8月  20 22:35 bin/
        drwxrwxr-x  2 copie copie 4096 8月  20 22:35 include/
        drwxrwxr-x  3 copie copie 4096 8月  20 22:35 lib/
        -rw-rw-r--  1 copie copie   60 8月  20 22:35 pip-selfcheck.json

## 激活virtualenv

    # 假设我们已经在mypython的虚拟环境里了
    source ./bin/activate
    # 然后我们会注意到我们的终端出现了变化如下的样子
    (mypython) copie@Lenovo:~/mypython$ 
    # 在用户名前出现(mypython)表示环境已经激活了
    pip list

        pip (9.0.1)
        setuptools (36.2.7)
        wheel (0.29.0)

## 关闭virtualenv

    deactivate

## 指定python环境

可以使用-p PYTHON_EXE选项在创建虚拟环境的时候指定python版本
这里就不写示例了
## 打包环境用

    virtualenv -relocatable
    # 我打包以后出现了一些问题 就是这个虚拟环境中还会出现对与我外部环境的链接有点问题？？？
## 最后

    virtualenv -h
    # 这是神器


