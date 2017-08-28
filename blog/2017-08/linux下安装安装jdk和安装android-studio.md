# linux下安装安装jdk和安装android studio

## 闲聊

**今天尝试在ubuntu16.04lts安装jdk-8u5-linux-x64.tar.gz，并配置环境变量，献给新手，或者纠结想用ubuntu编程，不会安装的朋友。亲测有效**

### JDK安装
1. 下载JDK

http://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html
![1](http://copie.cn/wp-content/uploads/2016/05/1-1.png)

2. 找到你下载文件的目录，使用下面的命令我的是用firefox下载的，在下载文件夹敲命令
> sudo tar zxvf ./jdk-8u5-linux-x64.tar.gz  -C ../../../usr/lib/jvm

如图

![2](http://copie.cn/wp-content/uploads/2016/05/2.png)

3. 进入到该目录下

> cd usr/lib/jvm

4. 重命名
> sudo mv jdk1.8.0_05/ java-8u5-sun

结果如下图，此时已经安装成功

![3](http://copie.cn/wp-content/uploads/2016/05/3.png)

5. 配置环境变量

使用vim ~/.bashrc命令编辑

在底部加入一下命令

    export JAVA_HOME=/usr/lib/jvm/java-8u5-sun
    export JRE_HOME=${JAVA_HOME}/jre
    export CLASSPATH=.:${JAVA_HOME}/lib:${JRE_HOME}/lib
    export PATH=${JAVA_HOME}/bin:$PATH

**如图**

![4](http://copie.cn/wp-content/uploads/2016/05/5.png)

6. 刷新环境变量

> source ~/.bashrc

7. 配置软连接，修改默认JDK 执行代码为：

> sudo update-alternatives --install /usr/bin/java java /usr/lib/jvm/java-8u5-sun/bin/java 300   
> sudo update-alternatives --install /usr/bin/javac javac /usr/lib/jvm/java-8u5-sun/bin/javac 300

8.  打开 命令提示行 验证一下

> java -version
> java
> java

**结果如图**

![5](http://copie.cn/wp-content/uploads/2016/05/6.png)


_____
### Android studio安装

下载android studio包（下载链接http://www.android-studio.org/ 或http://tools.android-studio.org/自己选择合适的下载）

**这里我就不贴出具体的链接了**
解压：

解压后文件夹名为android-studio。

移动：
> sudo mv android-studio /opt/

打开文件夹:
> cd /opt/android-studio/bin/

运行
> sudo ./studio.sh

OK，打开了。

新建一个test工程试试。

第一次新建工程后会提示下载gradle，这是android studio 必须的部分，耗时很长，慢慢等吧。终端提示如下：

Downloadinghttp://services.gradle.org/distributions/gradle-1.9-all.zip

插上手机运行一下 发现可以使用

以后想要直接运行android studio 可以在命令提示符里面直接输入

> sudo /opt/android-studio/bin/studio.sh

**SDK下载遇到的问题：**

Question: Unable to run mksdcard SDK tool.

![6](http://copie.cn/wp-content/uploads/2016/05/20160327170454075.png)

解决方案：

> sudo apt-get install lib32z1 lib32ncurses5  lib32stdc++6

ubuntu的快捷方式都在/usr/share/applications/路径下有很多*.desktop（eclipse的快捷方式也可以类似设置）

下面就建立我们的studio

> sudo gedit  /usr/share/applications/Studio.desktop

    [Desktop Entry]
    Name = Studio
    Comment= android studio
    Exec=/opt/android-studio/bin/studio.sh
    Icon=/opt/android-studio/bin/studio.png
    Terminal=false
    Type=Application

Exec 和  Icon 就是上面准备工作,查到的执行命令路径,和图片的路径.

每行后面不能有空格并且每行紧靠左侧不许有空格,否则无效.

不止androidstudio.如果我们想其他应用程序可以左侧快捷启动. 方式一样

**如果出现以下错误**

> Error:Execution failed for task ':app:validateDebugSigning'.
> Unable to recreate missing debug keystore.

**解决方法**

> sudo chmod -R 777 in .android, see that is a directory not visible located in ~/.

BY：COPYIST






