# linux_手动修复grub引导_基于btrfs

昨天夜里我为了删除 btrfs 的快照 ，其中有一些 删除的时候出现，出现了:

    # btrfs subvolume delete @_error
    ERROR: cannot delete ‘@_error‘ - Directory not empty
 
我竟然无法删除我新建的快照:)手动尴尬 提示很简单就是说这个文件夹不为空。

我看到有有一篇 blog 说 只有删除里层的 才可以删除这一个 我开始理解错了我以为 是删除 我当前用的然后才可以所以我运行了以下命令：

    # btrfs sub del @

然后可想而知 我彻底悲剧了 解释一下 这个命令 类似于这个:

    rm -rf /

:)苦笑

然后我的系统就崩溃了 无奈 只能强制关机 开机以后电脑出现了这个命令行：

    error: unknown filesystem
    grub rescue >

然后等待我的输入，看着一脸蒙蔽 是不是。由于我是运行了类似与 **rm -rf /** 这样的命令 所以说通过这个修复引导是完全不行的。但是我突然想到 我用的是 btrfs 文件系统 并且我以前还是有快照的。虽然 我把系统给删除了但是。快照没有被删除啊。我可以把引导修改一下引导到我的快照里面就可以进入命令行了。只要可以进入命令行。我就可以回滚我的快照了。说干就干。

我网上找了一下 grub rescue 如何修复引导的。一共只有一下几个命令

    ls, set, insmod, root, prefix(设置启动路径，我也是主要修改这里)

由于我是把系统给删了所以寻常的修复引导在这里完全不行的。

先查看一下我所在的目录下有什么

    grub rescue>ls
    (hd0) (hd0,msdos1) (hd0,msdos2) (hd0,msdos3)

这里可以看到我的硬盘 msdos1 应该就是我的第一的分区，我把它格式化为 btrfs 并在里面新建了一个卷挂载我的根目录 我查看了一下 (hd0,msdos1)

    ls (hd0,msdos1)/
    @_error @apt-*** ......

@ 就是我以前挂载根目录的地方 可惜被我给删了。我现在要做的就是 把 grub 的启动路径修改一下就是 上面说的 prefix

    grub rescue> prefix=(hd0,msdos1)/@apt-***/boot/grub
    grub rescue> set
    ......
    ......
    root=(hd0,msdos1)
    prefix=(hd0,msdos1)/@apt-***/boot/grub
    ......
    ......

这里我们已经修改好了启动路径现在启动系统

    grub rescue> insmod normal
    grub rescub> normal

这时候发现电脑启动了 grub 但是 grub 还是启动系统失败了。原来是我们启动了 grub 但是 grub 不知道我们的系统在那里是不所以修改 grub 的 配置文件。先选中我们要启动的系统 然后按 ‘e’ 开始修改配置文件 这个比较简单 就是把 配置文件里面里面的所有的 '@' 修改为 '@apt-\*\*\*\*' 具体就是一下两行

    kernel /@apt-***/boot/*******
    initrd /@apt-***/boot/*******

然后 看一下 下面有一个提示 按 f* 就可以启动我们的快照了 快照就是快照 进入的不是桌面环境 而是一个叫着 busyBox 的一个命令行 这就够了。我们现在 就可以 回滚快照了。

    mount /dev/sda1 /mnt # 如果提示没有/mnt你可以 mkdir /mnt 一个
    ls
    @_error @apt-*** # 启动需要的@被我删了
    cd /mnt
    mv @apt-*** @    # 这就是回滚简单吧 
    reboot           # 重启 等待重启以后电脑就又满血复活了


