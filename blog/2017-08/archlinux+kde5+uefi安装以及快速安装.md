# archlinux+kde5+uefi安装以及快速安装

现在越来越喜欢archlinux的pacman了太强大了在他面前什么apt，yum，dnf都是渣，arch的wiki也十分的牛逼不管你遇到了什么问题wiki上面都写得很清楚。但是arch的安装让不少人说还是算了吧。。。。。。
所以我结合wiki以及网上的一些教程写一篇arch的安装指南

首先对硬盘（256GB SSD）进行清除数据，低格全部填零（其实不必低格太伤固态了）

    dd if=/dev/zero of=/dev/sda bs=16M

使用parted命令进行分区，(parted)标识指在命令内部操作

    parted /dev/sda

建立gpt分区表

    (parted) mklabel gpt

建立ESP分区

    (parted) mkpart primary 1 512M

建立剩余部分全部分区

    (parted) mkpart primary 512M -1

设定ESP分区标志：boot

    (parted) set 1 boot on

查看与退出

    (parted) p
    (parted) q

查看分区

    lsblk

我的分区状态

EFI：/dev/sda1
Linux：/dev/sda2
生成ESP分区的文件系统FAT32

    mkfs.vfat -F32 /dev/sda1
 
格式化根分区

    mkfs.ext4 /dev/sda2

挂载根分区

    mount /dev/sda2 /mnt


建立efi目录

    mkdir -p /mnt/boot/efi

挂载EFI分区

    mount /dev/sda1 /mnt/boot/efi

电脑进行联网，本喵用wifi

    wifi-menu

测试网络是否畅通

    ping -c 3 www.baidu.com

编辑镜像源文件，添加中国源到第一行（源地址文件内可找到，比如163的），加快安装速度

    vi /etc/pacman.d/mirrorlist

安装基本包

    pacstrap -i /mnt base

编辑fstab记录当前mount状态

    genfstab -U -p /mnt >> /mnt/etc/fstab


完成后打开/mnt/etc/fstab 看看记录是否正确，建议把efi那行最后的数字改成0，不让每次都检查磁盘

    vi /mnt/etc/fstab

把/mnt作为新的根目录

    arch-chroot /mnt

时区与编码(编辑locale.gen文件，去掉en_US.UTF-8,zh_CN.UTF-8,zh_CN.GBK前面的#

    vi /etc/locale.gen

重建编码表

    locale-gen

设置时区

    ln -S /usr/share/zoneinfo/Asia/Shanghai /etc/localtime

同步本地时钟

    hwclock --localtime

设置主机名

    echo YourHostName >> /etc/hostname

安装wifi工具

    pacman -S dialog
    pacman -S wpa_supplicant
    pacman -S netctl
    pacman -S wireless_tools

安装vim(vi太坑了有木有，hahahaha)

    pacman -S vim

安装GRUB

    pacman -S grub-efi-x86_64
    pacman -S efibootmgr

把grub装到efi分区里

    grub-install --efi-directory=/boot/efi --bootloader-id=arch-grub --recheck

复制语言文件

    cp /usr/share/locale/en@quot/LC_MESSAGES/grub.mo /boot/grub/locale/en.mo

如果是双系统

    pacman -S os-prober


生成grub配置文件

    grub-mkconfig -o /boot/grub/grub.cfg

基本系统安装完毕，现在可以重启然后拔掉U盘了

    exit
    umount /mnt/boot/efi
    umount /mnt
    reboot


如果一切OK此时就可以进去GRUB菜单了
配置和完善

用户名:root
密码：空

进入archlinux

来设置个root密码

    passwd

联网

    wifi-menu

如果想自动激活wifi的话可以
安装 X 图形系统

    pacman -S xorg xorg-xinit

安装触摸板驱动

    pacman -S xf86-input-synaptics

安装一些xorg的app

    pacman -S xorg-twm xtrem

安装字体

    pacman -S ttf-dejavu wqy-microhei

建立普通用户

    useradd -m -k /etc/skel -G users,wheel YourLoginName

为新用户建立密码

    passwd YourLoginName

安装kde5桌面

    pacman -S kf5 kf5-aids
    pacman -S plasma kdebase kdegraphics-ksnapshot gwenview
    pacman -R plasma-mediacenter
    pacman -S sddm sddm-kcm
    systemctl enable sddm

> vim /etc/sddm.conf

在sddm.conf加入一下内容，没有的话自己创建

    [Theme]
    Current=breeze
    CursorTheme=breeze_cursors



安装其他软件包

    pacman -S gtk-engines gtk2 gtk3 gnome-themes-standard gnome-icon-theme

显示回收站(trash)图标

    pacman -S gvfs gamin

安装解压缩软件

    pacman -S p7zip zip unzip rar unrar

安装NTP

    pacman -S ntp
    systemctl enable ntpd

安装NetworkManager

    pacman -S networkmanager net-tools
    systemctl enable NetworkManager dhcpcd

安装声音

    pacman -S alsa-utils pulseaudio pulseaudio-alsa libcanberra-pulse libcanberra-gstreamer jack2-dbus

安装NTFS系统识别

    pacman -S ntfs-3g


安装sudo

    pacman -S sudo

编辑sudo配置文件,去掉root ALL=(ALL) ALL 和%wheel ALL=(ALL) NOPASSWD: ALL 前面的注释
    vim /etc/sudoers

安装kde中文语言包

    pacman -S kde-l10n-zh_cn

安装kde全部应用(不建议)

    pacman -S kde-applications

安装fcitx输入法

    pacman -S fcitx
    pacman -S fcitx-rime
    pacman -S fcitx-im
    pacman -S kcm-fcitx

新建配置文件，使之qt支持fcitx和中文环境

    cd /home/YourLoginName/
    vim .xprofile

加入以下内容

    export LANG=zh_CN.UTF-8
    export LC_ALL=zh_CN.UTF-8
    export GTK_IM_MODULE=fcitx
    export QT_IM_MODULE=fcitx
    export XMODIFIERS="@im=fcitx"

重启

    reboot

如果一切正常就该进入kde5桌面了。。。

记住联网时如果要创建kde钱包，请输入空密码，这样就不用以后每次登录都要输入钱包密码了。。
不要在意这些细节以上是我砖的
解决蓝牙问题

安装 bluez 和 bluez-utils 软件包。bluez 软件包提供蓝牙协议栈，bluez-utils 软件包提供 bluetoothctl 工具。 如果尚未加载通用蓝牙驱动则需先加载：

    modprobe btusb

然后 启动 bluetooth.service systemd 单元。可以在系统引导时自动 启用它。

图形化前端 
bluedevil 是 KDE 的蓝牙管理工具，可以用 bluedevil（KDE Plasma 5）或 bluedevil4[broken link: package not found]（KDE 4）安装。

确认bluetooth守护进程在运行。你可以在dolphin和系统通知区域里得到一个蓝牙图标，你可以通过点击这个图标来设置bluedevil、检测蓝牙设备等等。你也可以通过KDE的系统设置来配置bluedevil。
这样以后还有一点问题就是蓝牙能够配对但是不能够连接解决如下： 

PulseAudio 5.x 开始默认支持 A2DP。 确保这些包已经安装Install: pulseaudio-alsa, pulseaudio-bluetooth, bluez, bluez-libs, bluez-utils, bluez-firmware. 如果没有安装 pulseaudio-bluetooth，蓝牙设备在配对完成后，连接会失败，而且你不会得到任何有用的提示。

启动bluetooth服务: 

    systemctl start bluetooth

好了重头戏来了上面不理解也可以10分钟（取决于网速还可以更快）我写的简单脚本
1.sh

    mkfs.vfat -F32 /dev/sda1 
    mkfs.ext4 /dev/sda2 
    mount /dev/sda2 /mnt 
    mkdir -p /mnt/boot/efi 
    mount /dev/sda1 /mnt/boot/efi 
    pacstrap -i /mnt base 
    genfstab -U -p /mnt >> /mnt/etc/fstab 
    arch-chroot /mnt 


2.sh

    echo copie > /etc/hostname 
    pacman -S dialog 
    pacman -S wpa_supplicant 
    pacman -S netctl 
    pacman -S wireless_tools 
    pacman -S vim 
    pacman -S grub-efi-x86_64 
    pacman -S efibootmgr 
    grub-install --efi-directory=/boot/efi --bootloader-id=arch-grub --recheck 
    cp /usr/share/locale/en@quot/LC_MESSAGES/grub.mo /boot/grub/locale/en.mo 
    grub-mkconfig -o /boot/grub/grub.cfg 
    pacman -S xorg xorg-xinit 
    pacman -S xf86-input-synaptics 
    pacman -S xorg-twm xtrem 
    pacman -S ttf-dejavu wqy-microhei 
    useradd -m -k /etc/skel -G users,wheel copie
    passwd copie
    pacman -S kf5 kf5-aids 
    pacman -S plasma kdebase gwenview 
    pacman -R plasma-mediacenter 
    pacman -S sddm sddm-kcm 
    systemctl enable sddm 
    pacman -S gtk-engines gtk2 gtk3 gnome-themes-standard gnome-icon-theme 
    pacman -S gvfs gamin 
    pacman -S p7zip zip unzip unrar 
    pacman -S ntp 
    systemctl enable ntpd 
    pacman -S networkmanager net-tools 
    systemctl enable NetworkManager dhcpcd
    pacman -S alsa-utils pulseaudio pulseaudio-alsa libcanberra-pulse libcanberra-gstreamer jack2-dbus 
    pacman -S ntfs-3g 
    pacman -S sudo 
    pacman -S kde-l10n-zh_cn 
    modprobe btusb
    pacman -S bluez bluez-utils
    systemctl enable bluetooth.service
    systemctl start bluetooth.service

以上两个脚本我不想多说结合脚本和上面的讲解适当的改些东西就可以了。