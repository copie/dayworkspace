# 在Ubuntu中安装Eclipse与Helloworld和Pydev(python的插件)安装

## 闲聊

在Ubuntu中安装Eclipse之前，必须先如同《linux下安装安装jdk》现在Ubuntu中装好JDK1.7，整个安装过程甚至比Debian的还要简单，安装的过程中，活用好把文件拖进终端，这样就不用输入这么长的路径。Ubuntu与Debian唯一的区别，就是执行命令你通通在前面补个sudo就对了，表示以root用户执行这个命令。

## 一、Eclipse的与安装

1. 首先，在Eclipse的官网中下载最新版的Luna SR2http://www.eclipse.org/downloads/packages/release/Luna/SR2（点击打开链接）
直接下载最新版的Eclipse for javaEE Linux 32bit/64bit，Eclipse各个版本其实差别不多，而Eclipse for JavaEE同时包含JavaEE与Java的内容。方便以后写Java EE就无须再另外下插件了。

![1](http://copie.cn/wp-content/uploads/2016/05/1-2.png)

2. 下好之后，还是把eclipse-jee-luna-SR2-linux-gtk.tar.gz扔到那个，机器重启内容就会消失的/tmp文件夹，免得安装完还要自己删除安装文件

![2](http://copie.cn/wp-content/uploads/2016/05/2-1.png)

3. 打开终端，直接输入如下指令：

> sudo tar zxvf '/tmp/eclipse-jee-luna-SR2-linux-gtk.tar.gz' -C /usr/lib

![3](http://copie.cn/wp-content/uploads/2016/05/3-1.png)

等待完一轮解压

到这里，实质上Eclipse已经安装好了。Eclipse在任何系统都是绿色版，这一点必须为Eclipse点赞！

但是，为了更方便我们使用，我们还是要输入如下指令，为Eclipse创建桌面快捷方式，首先要为Eclipse在 /usr/share/applications/目录下配置好快捷方式。

4. 在终端输入：

> sudo gedit /usr/share/applications/eclipse.desktop


终端的警告不用理会，在弹出的文本编辑器输入：

    [Desktop Entry]
    Type=Application
    Name=Eclipse
    Comment=Eclipse Integrated Development Environment
    Icon=/usr/lib/eclipse/icon.xpm
    Exec=/usr/lib/eclipse/eclipse -vm /usr/lib/jvm/jdk1.8u92-sun/bin/java
    Terminal=false
    Categories=Development;IDE;Java;

之后保存退出。

5. 之后我们再打开文件系统，来到如下的/usr/share/applications/找到Eclipse图标，右击，复制到->桌面，此时，Eclipse的快捷方式就创建完毕了。
![4](http://copie.cn/wp-content/uploads/2016/05/4.png)

_____

## 二、Eclipse的使用与Helloworld

1. 直接点开桌面的Eclipse，完全跟Windows是一个样子的。
![5](http://copie.cn/wp-content/uploads/2016/05/5-1.png)

2. 初次启动它会让你设置工作目录，那就设定吧，按照默认的工作目录就可以了。你让我选择其它目录我还不会选。然后勾选，设置其为默认的工作目录，不再提示。

![6](http://copie.cn/wp-content/uploads/2016/05/6-1.png)

3. 之后你就可以在文件系统的主文件夹找到这个工作目录。你创建的Java工程都在此处。

![7](http://copie.cn/wp-content/uploads/2016/05/7.png)

4. 关闭欢迎页之后，虽然提示这是JavaEE的工作环境，但无须理会。右键工作区，新建一个工程，如下图：

![8](http://copie.cn/wp-content/uploads/2016/05/9.png)

5. 选择Java工程

![9](http://copie.cn/wp-content/uploads/2016/05/10.png)

6. 输入名字之后，记住选好我们刚刚装好的JDK1.7，不要使用默认的JDK，免得出现这样那样的问题。

![10](http://copie.cn/wp-content/uploads/2016/05/11.png)

7. 再点下一步，不要急着点完成，在Order and Export的一项，也把刚刚安装的JDK1.7选上，再点完成。

![11](http://copie.cn/wp-content/uploads/2016/05/12.png)

8. 右键刚刚建立的Java工程新建一个类，也就是Java文件。

![12](http://copie.cn/wp-content/uploads/2016/05/13.png)

9. 写好名字之后，同时把创建主函数勾上，不用我们自己写了。

![13](http://copie.cn/wp-content/uploads/2016/05/14.png)

10. 通过与Windows一样的快捷键Ctrl+空格设出Linux的输入法，再补一句打印“你好，世界”的System.out.println的Java语句，点击上方的运行，你就会看到运行结果。这分明就跟Windows下的Eclipse一模一样。

![14](http://copie.cn/wp-content/uploads/2016/05/15.png)

## 在Eclipse中安装pydev插件

### pydev插件介绍

pydev插件的官方网站: http://www.pydev.org/（不需要下载）


启动Eclipse, 点击Help->Install New Software... 在弹出的对话框中，点Add 按钮。 Name中填:Pydev, Location中填http://pydev.org/updates

然后一步一步装下去。 如果装的过程中，报错了。 就重新装。

### 配置pydev解释器

安装好pydev后， 需要配置Python解释器。

在Eclipse菜单栏中，点击Windows ->Preferences.

在对话框中，点击pyDev->Interpreter - Python. 点击New按钮， 选择python.exe的路径, 打开后显示出一个包含很多复选框的窗口. 点OK



