# 为sudo输入密码提供视觉提示

我们在用sudo输入密码的时候如果自己不小心输错了密码要按删除键好多下还是有一点不放心用起来特别的不方便比如以下GIF：

![没有修改前的GIF](http://copie.cn/usr/uploads/2017/07/504511771.gif)

没有一点反馈

我宁愿看到一些*也好呀

![修改文件](http://copie.cn/usr/uploads/2017/07/973888623.gif)

1. 打开一个新的终端窗口（Ctrl + Alt + T）并输入以下命令：

    sudo visudo

1. 使用键盘导航键（或鼠标滚轮）移动到以下行：

    Defaults env_reset

1. 将方框移动到该行的末尾，并添加以下文本，使其为：

    Defaults env_reset,pwfeedback

1. 按Ctrl + X完成编辑，然后按YEnter并返回以保存输入的更改

完成以后你就可以看到小星号了(:手动苦笑

如图：

![成果](http://copie.cn/usr/uploads/2017/07/3883835340.gif)
