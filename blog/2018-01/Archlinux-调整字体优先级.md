# archlinux 调整字体优先级

用 archlinux 我一直用的就是思源黑体中等。但是我一般就会不安装其他字体包括宋体。这让我看 word 十分的麻烦。
没有办法我还要安装上宋体在系统的默认优先级比较高所以导致 chrome 和其他的一些软件都是宋体十分的难看。我找了很长时间要改变这个。还好我今天刚刚好解决了这个问题。这里记录一下。

我们这里以思源黑体为例来解决这个问题


1. 修改文件 /etc/fonts/conf.avail/64-language-selector-prefer.conf 如下，无此文件则创建:

```xml
    <?xml version="1.0"?>
    <!DOCTYPE fontconfig SYSTEM "fonts.dtd">
    <fontconfig>
        <alias>
            <family>sans-serif</family>
            <prefer>
                <family>Source Han Sans CN Medium</family>
                <family>SimSun</family>
            </prefer>
        </alias>
        <alias>
            <family>serif</family>
            <prefer>
                <family>Source Han Sans CN Medium</family>
                <family>SimSun</family>
            </prefer>
        </alias>
        <alias>
            <family>monospace</family>
            <prefer>
                <family>Source Han Sans CN Medium</family>
                <family>SimSun</family>
            </prefer>
        </alias>
    </fontconfig>
```

2. 保存文件后，若 /etc/fonts 目录下有 conf.d/ 目录，则在该目录中创建指向 /etc/fonts/conf.avail/64-language-selector-prefer.conf 的同名软链接：

    sudo ln -s /etc/fonts/conf.avail/64-language-selector-prefer.conf /etc/fonts/conf.d/64-language-selector-prefer.conf

3. 然后更新字体缓存即可生效：

    fc-cache -fv


