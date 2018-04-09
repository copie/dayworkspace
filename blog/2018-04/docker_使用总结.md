# docker  使用总结

## doker 基础命令

1. **docker build**

    > 通过 dockerfile 新建一个镜像

    >> 主要可选的参数有
    >>> -f 指定dockerfile</br>
    >>> -c 与CPU相关</br>
    >>> -m 与内存相关</br>
    >>> -t 名称列表和标签 'name：tag'</br>

    >> 简单的例子
    >>> docker build -f dockerfile -t test:test .

    >> 注意在最后指定 PATH 也就是 最后的那个 .

2. **docker ps**

    > 列出正在运行的容器

    >> 它有几个简单的参数这里就不多说了详情看 docker ps --help

    >> 简单的例子
    >>> docker ps -n -1

3. **docker commit**

    > 提交一个新的 image 由于容器在下一次开启的时候不会保存上一次运行产生的修改所以这个提交还是很有必要的

    >> docker commit 3a43df2d7059 test:test

4. **docker pull**

    > 从仓库里面拉取一个镜像
    >> 简单的例子
    >>> docker pull hello-world

5. **docker run**

    > 运行一个容器
    >>> -d 后台运行一个容器，并返回容器的ID</br>
    >>> -i 以交互模式运行容器，通常与 -t 同时使用</br>
    >>> -t 为容器重新分配一个伪输入终端，通常与 -i 同时使用</br>
    >>> -p 手动端口映射</br>
    >>> -P 自动随机端口映射</br>
    >>> -v 挂载本地目录到容器(填写绝对路径)</br>
    >>> --net="bridge" 指定容器的网络连接类型，支持 bridge/host/none/container: 四种类型</br>
    >>> --link=[]: 添加链接到另一个容器</br>

    >> 简单的例子
    >>> docker run -it c712034 /bin/bash</br>
    >>> docker run -d c71</br>
    >>> docker run -Pd c71</br>
    >>> docker run -d -p 8000:80 -p 2222:22 06a # -p 宿主机端口:容器端口</br>
    >>> docker run -d -v /home/copie/Desktop/sample:/app 06a</br>

6. **docker stop**

    > 关闭一个容器
    >> 简单的例子
    >>> docker stop d5f19

7. **dicker exec**

    > 在运行的容器中执行命令(解决如何进入在后台运行的容器)
    >> 简单的例子
    >>> docker exec -it d5 /bin/bash

8. **docker rmi**

    > 删除一个或多个镜像
    >>> -f 强制删除

    >> 简单的例子
    >>> docker rmi 06a -f

**这里是我最常用的一些命令**


## dockerfile 编写

Docker 可以通过 Dockerfile 的内容来自动构建镜像。

Dockerfile 是一个包含创建镜像所有命令的文本文件，通过docker build命令可以根据 Dockerfile 的内容构建镜像，在介绍如何构建之前先介绍下 Dockerfile 的基本语法结构。

Dockerfile 有以下指令选项:

+ FROM
+ MAINTAINER
+ RUN
+ CMD
+ EXPOSE
+ ENV
+ ADD
+ COPY
+ ENTRYPOINT
+ VOLUME
+ USER
+ WORKDIR
+ ONBUILD

Dockerfile文件的格式如下
```
# Comment
INSTRUCTION arguments
```
\#井号开头的表示注释行;<br>
INSTRUCTION指令是不区分大小写的，但是为了便于区分建议使用全大写格式。

### FROM

```FROM <image>```

+ FROM指定构建镜像的基础源镜像，如果本地没有指定的镜像，则会自动从 Docker 的公共库 pull 镜像下来。
+ FROM必须是 Dockerfile 中非注释行的第一个指令，即一个 Dockerfile 从FROM语句开始。
+ FROM可以在一个 Dockerfile 中出现多次，如果有需求在一个 Dockerfile 中创建多个镜像。
+ 如果FROM语句没有指定镜像标签，则默认使用latest标签。

```FROME hello-world```

### MAINTAINER

```MAINTAINER <name>```

指定镜像的维护者

```MAINTAINER copie```

### RUN

```RUN  command parameter```

+ 每条RUN指令将在当前镜像基础上执行指定命令，并提交为新的镜像，后续的RUN都在之前RUN提交后的镜像为基础，镜像是分层的，可以通过一个镜像的任何一个历史提交点来创建，类似源码的版本控制。
+ RUN产生的缓存在下一次构建的时候是不会失效的，会被重用，可以使用--no-cache选项，即docker build --no-cache，如此便不会缓存。

```RUN apt-get install apache```

### CMD

```CMD command parameter```

+ CMD指定在 Dockerfile 中只能使用一次，如果有多个，则只有最后一个会生效。
+ CMD的目的是为了在启动容器时提供一个默认的命令执行选项。如果用户启动容器时指定了运行的命令，则会覆盖掉CMD指定的命令。

**CMD会在启动容器的时候执行，build 时不执行，而RUN只是在构建镜像的时候执行，后续镜像构建完成之后，启动容器就与RUN无关了，这个初学者容易弄混这个概念，这里简单注解一下。**

```CMD["echo","hello world"]```

### EXPOSE

```EXPOSE <port> [<port>...]```

+ 告诉 Docker 服务端容器对外映射的本地端口，需要在 docker run 的时候使用-p或者-P选项生效。

```EXPOSE 80```

### ENV

```
ENV <key> <value>       # 只能设置一个变量
ENV <key>=<value> ...   # 允许一次设置多个变量
```

指定一个环节变量，会被后续RUN指令使用，并在容器运行时保留。

例如:

```
ENV myName="John Doe" myDog=Rex\ The\ Dog \
    myCat=fluffy
```
等同于:

```
ENV myName John Doe
ENV myDog Rex The Dog
ENV myCat fluffy
```

### ADD

```ADD <src>... <dest>```

+ ADD复制本地主机文件、目录或者远程文件 URLS 从 并且添加到容器指定路径中 。
+ 支持通过 Go 的正则模糊匹配，具体规则可参见 [Go filepath.Match](http://golang.org/pkg/path/filepath/#Match)

```
ADD hom* /mydir/        # adds all files starting with "hom"
ADD hom?.txt /mydir/    # ? is replaced with any single character
```

+ 路径必须是绝对路径，如果 不存在，会自动创建对应目录
+ 如果是一个目录，只会复制目录下的内容，而目录本身则不会被复制

### COPY

```COPY <src>... <dest>```

+ COPY复制新文件或者目录从 并且添加到容器指定路径中 。用法同ADD，唯一的不同是不能指定远程文件 URLS。

### ENTRYPOINT

和 RUN 类似 还有区别(自我感觉RUN就可以了这个就了解一下)

### VOLUME

```VOLUME ["/data"]```

创建一个可以从本地主机或其他容器挂载的挂载点

### WORKDIR

```WORKDIR /path/to/workdir```

为后续的RUN、CMD、ENTRYPOINT指令配置工作目录。可以使用多个WORKDIR指令，后续命令如果参数是相对路径，则会基于之前命令指定的路径。

```
WORKDIR /a
WORKDIR b
WORKDIR c
RUN pwd
```
最终路径是/a/b/c。

WORKDIR指令可以在ENV设置变量之后调用环境变量:

```
ENV DIRPATH /path
WORKDIR $DIRPATH/$DIRNAME
```
最终路径则为 /path/$DIRNAME。

### ONBUILD

```ONBUILD [INSTRUCTION]```

配置当所创建的镜像作为其它新创建镜像的基础镜像时，所执行的操作指令。

## dockerfile 其他

+ 使用.dockerignore文件

为了在docker build过程中更快上传和更加高效，应该使用一个.dockerignore文件用来排除构建镜像时不需要的文件或目录。例如,除非.Git在构建过程中需要用到，否则你应该将它添加到.dockerignore文件中，这样可以节省很多时间。

+ 避免安装不必要的软件包

为了降低复杂性、依赖性、文件大小以及构建时间，应该避免安装额外的或不必要的包。例如，不需要在一个数据库镜像中安装一个文本编辑器。

+ 每个容器都跑一个进程

在大多数情况下，一个容器应该只单独跑一个程序。解耦应用到多个容器使其更容易横向扩展和重用。如果一个服务依赖另外一个服务，可以参考 [Linking Containers Together](https://docs.docker.com/userguide/dockerlinks/)

+ 最小化层

我们知道每执行一个指令，都会有一次镜像的提交，镜像是分层的结构，对于Dockerfile，应该找到可读性和最小化层之间的平衡。

+ 多行参数排序

如果可能，通过字母顺序来排序，这样可以避免安装包的重复并且更容易更新列表，另外可读性也会更强，添加一个空行使用\换行:

```
RUN apt-get update && apt-get install -y \
  bzr \
  cvs \
  git \
  mercurial \
  subversion
  ```

+ 创建缓存

镜像构建过程中会按照Dockerfile的顺序依次执行，每执行一次指令 Docker 会寻找是否有存在的镜像缓存可复用，如果没有则创建新的镜像。如果不想使用缓存，则可以在docker build时添加--no-cache=true选项。

从基础镜像开始就已经在缓存中了，下一个指令会对比所有的子镜像寻找是否执行相同的指令，如果没有则缓存失效。在大多数情况下只对比Dockerfile指令和子镜像就足够了。ADD和COPY指令除外，执行ADD和COPY时存放到镜像的文件也是需要检查的，完成一个文件的校验之后再利用这个校验在缓存中查找，如果检测的文件改变则缓存失效。RUN apt-get -y update命令只检查命令是否匹配，如果匹配就不会再执行更新了。

**为了有效地利用缓存，你需要保持你的 Dockerfile 一致，并且尽量在末尾修改。**

