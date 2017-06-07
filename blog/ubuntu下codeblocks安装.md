# ubuntu下安装codebocks
## 闲扯

开始ＡＣＭ刷题一直用的就是vc++6.0,各种各样的无端的错误，只能说我也是醉了。然后接触到了codeblocks,首先界面特别漂亮，虽然没有vs2015那样的强大，但是我等小白用起来还是蛮爽的。但是自从我爱上了使用linux 的时候发现一切都变了编辑器有vim,编译器有GCC,等等，小白的我用起来只能说能用，不太的的心应手。于是就想到了ＩＤＥ，我试过的有很多比如ATOM，GEANY,Eclipse.用着都还可以就是有时候会出现一些莫名其妙的问题。
codeblocks 我现在才发现linux下有
*** 多个版本
> 我坑在上面很多次啊
## 正式教程
    sudo add-apt-repository ppa:damien-moore/codeblocks-stable

    sudo apt update

    sudo apt-get install codeblocks codeblocks-contrib 


以上是ubuntu的debian的就比较麻烦一点了

由于debian我安装的时候是没有c语言环境的先安装GCC，G++，gdb，等

然后在codeblocks官网下载那个解压包里面有很多.deb的包是不是一脸懵逼，他们之间是有依赖关系的这里我就不多说了主要就是先装lib然后在装主程序就可以了，具体的依赖关系自己摸索一下就可以发现了。他尽然没有readme文件好尴尬。

其他的和ubuntu都是一样的。

这样就安装好了最新版的bockblocks 不要高兴的太早接下来一不小心你又会遇到莫名其妙的问题比如

是不是发现可以用了。这还没完是不是感觉ｈｅｌｌｏｗｏｒｄ那个终端特别丑

我们换一个Settings->Environment settings->Terminal to launch console programs  把xterm-T $TITLE -e 改为gonme-terminal-t $TIYLE  -x 就可以了。
## 作者语
* codeblocks一定要安装PPA的stable版的不然会出现卡死的情况还不知道为什么会出现这个问题