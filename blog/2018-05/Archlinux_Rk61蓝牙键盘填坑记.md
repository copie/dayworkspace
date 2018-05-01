# Archlinux_RK61 蓝牙键盘填坑记

当初在网上,看到这个双模蓝牙键盘挺便宜的,就买了...... 由于我自己一直都是使用 Linux ,而他们只保证在 安卓,ios,macos,windows 上面能够很好的使用.
拿回来以后发现蓝牙一直有如下问题:

+ 开机不能自动连接
+ 连接后不能输入(ps:时间证明这个 BUG 是 kde 蓝牙前端的锅)
+ fn+num 不可以使用

## 解决以上的问题

1. 开机不能自动连接是因为我笔记本的蓝牙没有在开机的时候启动,如下配置即可

    [/etc/bluetooth/main.conf]
    AutoEnable=true

2. 假如你和我一样连接以后发现输入的和按键按的对不上号,我的解决方法是,卸载桌面系统的蓝牙前端,直接使用命令行进行连接

+ 使用 bluetoothctl 进入蓝牙控制窗口
+ 使用 power on 为蓝牙模块上电
+ 使用 agent KeyboardOnly 设置为只查看键盘, 并设置为默认代理
+ 使用 pairable on 将蓝牙模块设置为可配对模式
+ 使用 scan on 查找可配对的蓝牙设备
+ 使用 pair 01:02:03:04:05:06 与自己要配对的设备配对,注意自己设备的MAC地址
+ 使用 trust 01:02:03:04:05:06 信任此设备
+ 使用 connect 01:02:03:04:05:06 连接此设备
+ 使用 quit 退出蓝牙控制

这样以后就可以在输入开机密码的时候用蓝牙键盘了

3. fn+num 我使用的方法是和苹果键盘在 Linux 不能使用一个解决办法

临时配置
+ echo "2" | sudo tee /sys/module/hid_apple/parameters/fnmode

永久配置
```
echo "options hid_apple fnmode=2" | sudo tee /etc/modprobe.d/hid_apple.conf
```
修改 /etc/mkinitcpio.conf 文件 保证 HOOK 中有 mdconf
然后在 FILES 中添加 /etc/modprobe.d/hid_apple.conf
修改后的样子

```
FILES=(/etc/modprobe.d/hid_apple.conf)
HOOKS=(base udev autodetect modconf block filesystems keyboard fsck)
```
最后重新建立启动镜像就可以了

    sudo mkinitcpio -p linux

