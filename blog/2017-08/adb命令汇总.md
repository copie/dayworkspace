# adb命令汇总

adb的全称为Android Debug Bridge，就是起到调试桥的作用。通过adb我们可以在Eclipse中方便通过DDMS来调试Android程序，说白了就是debug工具。adb的工作方式比较特殊，采用监听Socket TCP 5554等端口的方式让IDE和Qemu通讯，默认情况下adb会daemon相关的网络端口，所以当我们运行Eclipse时adb进程就会自动运行。作为开发人员，掌握适当所需要的ADB操作命令是非常必须的。就把平时工作中用得相对比较多的adb命令作个小总结。

## ADB自身管理相关命令

    adb kill-server   终止ADB服务进程

    adb start-server 启动或重启ADB服务进程

    adb root  以root权限重启ADB服务

## 使用ADB进行设置（包括模拟器）管理

    adb devices 查看连接到计算机上的设备

    adb  get-serialno  获取连接到电脑上设备的序列号，当前只能连接一台设备才能获取得到

    adb  reboot    重启连接到电脑上的设备

    adb reboot bootloader /recovery 重启设备进入到fastboot模式或recovery模式，通常在刷机的时候用到

    adb [-d|-e|-s<serialNumber>] command  发送指定命令给指定设备，其中serialNuber是设备号

## 获取设备硬件信息

    adb shell cat /sys/class/net/wlan0/address 获取wifi mac地址

    adb shell cat/proc/cpuinfo   获取cpu序列号

    adb shell cat /system/build.prop  获取设备编译属性

    adb shell cat /data/misc/wifi/*.conf  获取设备wifi配置信息

## 通过设备管理APP应用操作

    adb install [-r|-s] <apkfile>  安装apk文件

    adb uninstall [-k] <packagename> 卸载APP

    adb  shell top [-m <number>] 查看内存情况，如果有number表示查看多少条数据

    adb  shell ps 查看进程列表数据

    adb shell kill <pid>  杀死对应pid的进程

    adb shell ps -x <pid>   查看指定pid进行的运行状态

    adb  shell  service list 查看后台服务信息

    adb  shell cat /proc/meminfo  查看当前内存占用情况

    adb  shell cat /proc/iomen 查看io内存分区情况

## 对文件进行操作的相关adb命令

    adb shell ls mnt  查看所有设备中的存储设备名

    adb  remount 将system分区重新挂载为可读写分区

    adb push <local> <remote> 从本地复制文件到设备中local和remote分别对应本地与设备的文件

    adb  pull <remote> <local>从设备复制文件到本地的操作

    adb shell ls 查看目录下的所有文件及文件夹

    adb shell cd <folder> 查看文件夹内容

    adb  shell mkdir path/floldername 新建文件

## 其它操作命令

    adb  shell input text <context>  发送文件内容

    adb  shell input keyevent <keycode>  通过adb命令发送键盘事件

    adb  shell wm size  获取设备分辨率

    adb  shell getprop <key> 获取设备参数信息

    adb shell setprop <key> <value> 设置设备的参数信息

    adb shell screencap -p <path/file> 使用adb命令进行截屏操作

    adb  shell screenrecord [options] <path/filename>    使用adb命令进行视屏录制

    [options]  可以填写：

    size WIDTH*HEIGHT

    bit -rete

    -time -limit 时间限制等
