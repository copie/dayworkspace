# 使用目录树/文件名时的紧凑bash提示

## 问题描述

我在刷题的时候每一次比赛,我就会新建一个目录 但是有些时候我的比赛的名字比较长我编译运行的时候发现我的终端特别的丑，所以我就修改  ~/.bashrc 文件来实现我要解决的问题我参考了[使用目录树/文件名时的紧凑bash提示](https://gxnotes.com/article/104078.html)
这个发现他的最佳答案有一些问题会出现一些BUG我修改了一下然后发出来我的修改。

在 ubutnu16.04 中 bash PS1以一下结尾

    \u@\h:\w\$
有些 blog 说把 w 替换 成W 就可以了 但是遇到有些目录本身就比较长的也是无能为力了

比如：

    /home/copie/dayworkspace/ACM/jixun/2017Multi-UniversityTrainingContest-Team2

显示的还是特别长的没有办法换方法网上有一个人的 blog 有一点问题我修改了一下然后发出来 废话不多说先看效果咯

![图片](http://copie.cn/usr/uploads/2017/07/1089034350.png)

在**~/.bashrc**最后面添加如下代码：

    get_PS1(){
            limit=${1:-10}
            left="${PWD:0:5}"
            right="${PWD:$((${#PWD}-$limit)):${#PWD}}"
            len="$[${#right}+${#left}+3]"
            if [[ "${#PWD}" -ge "$len" ]]; then
                    PS1="\[\033[01;33m\]\u@\h\[\033[01;34m\]:${left}...${right}\$\[\033[00m\]"
            else
                    PS1="\[\033[01;33m\]\u@\h\[\033[01;34m\]:\w\$\[\033[00m\]"
            fi
    }
    PROMPT_COMMAND=get_PS1

通过我的简单修改效果会好的多