# Linux 下搭建 MASM 汇编环境

这个学期学习微机原理,学习到了汇编。突然发现汇编也那么有意思。Linux 下原生的 NASM 的话伪指令和上课学得不太一样,我自己也懒得去看 NASM 的一些东西。所以喽自己在Linux 下搭建了一个学习的环境。方便验证在自己的想法。

## 工具的简单的介绍

MASM 是 Microsoft Macro Assembler 的缩写，它是微软为 X86 微处理器家族编写的一套宏编译器

dosbox 是一款 X86/DOS环境模拟器，可以很好的模拟dos环境，方便我们运行DOS程序

## 安装dosbox

    sudo pacman -S dosbox

## 下载 MASM 软件包

我这里给出链接[MASM下载](https://copie.cn/usr/uploads/2017/11/3972734073.zip)
这个里面是没有 DEBUG.EXE 的 需要自己去下载一个然后放到 MASM 的解压目录里面[DEBUG.EXE下载](https://copie.cn/usr/uploads/2017/11/3386747647.zip)

解压两个压缩包然后把 DEBUG 中的debug.exe 放到 MASM文件夹里面。然后你可以把 MASM 文件夹放到你想放到的地方比如我把他们放到了 ~/.dosbox/ 文件夹里面


## 修改配置文件

我们要修改 /home/copie/.dosbox/dosbox-0.74.conf 这个文件

在:

    [autoexec]
    # Lines in this section will be run at startup.
    # You can put your MOUNT lines here.

下面添加如下配置

    MOUNT c /home/copie/.dosbox/masm
    set PATH= %PATH%;c:\;
    mount E /home/copie/dayworkspace/ASM
    E:

这里 我们先将我们解压的 MASM 文件挂载到 dosbox 的 C 盘，然后将 C 盘添加到环境变量里面。
然后再挂载一个目录作为自己的工作目录。把他挂载在 E 盘。

这个时候启动 DOSBOX 会看到如下的提示![bosbox启动界面](https://copie.cn/usr/uploads/2017/11/2964109382.png)

## Hello World!
环境搭建好以后就要来一个 Hello World! 镇场子了

在我们挂载 E 盘文件夹下面创建 hello.asm

    assume cs:codes, ds:datas
    datas segment
            str db 'hello,world',13,10,'$'
    datas ends
    codes segment
        start:
            mov ax, datas
            mov ds, ax
            lea dx, str
            mov ah, 9
            int 21h
            mov ah, 4ch
            int 21h
    codes ends
        end start

### 编译链接运行

打开 dosbox 运行下面三个命令

    E:\> masm hello.asm
    E:\> link hello.obj
    E:\> hello.exe
    hello,world


---

好了环境已经搭好了
