# fastboot命令汇总

对于我这种闲着没事总爱刷机的孩子来说自从用了Linux用电脑刷机好像变得困难了，经过我的google发现不是困难了而时变简单了，fastboot命令来拯救我们

## 一. 帮助说明

    usage: fastboot [ <option> ] <command>

    commands:
    update <filename>                        reflash device from update.zip
    flashall                                 flash boot, system, vendor and if found,
                                            recovery
    flash <partition> [ <filename> ]         write a file to a flash partition
    erase <partition>                        erase a flash partition
    format[:[<fs type>][:[<size>]] <partition> format a flash partition.
                                            Can override the fs type and/or
                                            size the bootloader reports.
    getvar <variable>                        display a bootloader variable
    boot <kernel> [ <ramdisk> [ <second> ] ] download and boot kernel
    flash:raw boot <kernel> [ <ramdisk> [ <second> ] ] create bootimage and 
                                            flash it
    devices                                  list all connected devices
    continue                                 continue with autoboot
    reboot                                   reboot device normally
    reboot-bootloader                        reboot device into bootloader
    help                                     show this help message

    options:
    -w                                       erase userdata and cache (and format
                                            if supported by partition type)
    -u                                       do not first erase partition before
                                            formatting
    -s <specific device>                     specify device serial number
                                            or path to device port
    -l                                       with "devices", lists device paths
    -p <product>                             specify product name
    -c <cmdline>                             override kernel commandline
    -i <vendor id>                           specify a custom USB vendor id
    -b <base_addr>                           specify a custom kernel base address.
                                            default: 0x10000000
    -n <page size>                           specify the nand page size.
                                            default: 2048
    -S <size>[K|M|G]                         automatically sparse files greater
                                            than size.  0 to disable

## 二. 具体分析
### 1 升级系统

    fastboot flash bootloader u-boot.bin
    fastboot flash kernel uImage
    fastboot flash system system.img
    fastboot flash userdata userdata.img
    fastboot flash ramdisk ramdisk-uboot.img
    fastboot erase cache
    fastboot flash {partition} {*.img} 

    例：fastboot flash boot boot.img或fastboot flash system system.img等。

    fastboot flashall 

    注意：此命令会在当前目录中查找所有img文件，将这些img文件烧写到所有对应的分区中，并重新启动手机。

一次烧写boot，system，recovery分区：

1. 创建包含boot.img，system.img，recovery.img文件的zip包。

2. 执行：fastboot update {*.zip}

烧写开机画面：

    fastboot flash splash1 开机画面

### 2 重启系统

    fastboot reboot

### 3 不烧写flash情况下调试

    fastboot boot uImage 或者u-boot.bin

### 4 查看版本号

    fastboot getver:version

### 5 复位到bootloader

    fastboot reboot-bootloader

### 6 命令格式

主机端发送字符串的命令，字符串小于等于64个字节，客户端首先返回四个字节的内容，是OKAY、FAIL、DATA、INFO之一，随后跟着是信息或数数据。

### 7 清空分区

    fastboot erase {partition} 例：fastboot erase boot或fastboot erase system等。

    fastboot erase boot

    fastboot erase system

    fastboot erase data

    fastboot erase cache

上面的命令也可以简化成一条命令

    fastboot erase system -w

### 8 获取客户端(手机端)变量信息

fastboot getvar version:version-bootloader:version-baseband:product:serialno:secure

version 客户端支持的fastboot协议版本

version-bootloader Bootloader的版本号

version-baseband 基带版本

product 产品名称

serialno 产品序列号

secure 返回yes 表示在刷机时需要获取签名

支持的参数

偏移和地址在u-boot中定义，要想使用好fastboot，就必须要知道参数名称与文件的对应关系。

    name                 offset             size
    xloader             0x00000000       0x00080000
    bootloader          0x00080000       0x00180000
    environment         0x001C0000       0x00040000
    kernel              0x00200000       0x01D00000
    system              0x02000000       0x0A000000
    userdata            0x0C000000       0x02000000
    cache               0x0E000000       0x02000000



    name                 type of file                                 usual file
    xloader              xloader binary                                 MLO
    bootloader           uboot binary                                   u-boot.bin
    environment          text file                                      list of  variables to set
    kernel               kernel or kernel + ramdisk     uImage, uMulti
    system               yaffs2                                         system.img
    userdata             yaffs2                                         userdata.img
    cache                yaffs2                                          ?

### 9 环境变量

fastboot支持环境变量文件，通常在fastboot烧写nand flash时，会将偏移量和大小写入环境变量中，命名格式为：

    _nand_offset
    _nand_size

例如，内核烧写完成后printenv可以看到：

    kernel_nand_offset=0x140000
    kernel_nand_size=0x1f70000

### 10 查看USB设备

查看连接到OTG的USB设备情况，lsusb:

    Bus 008 Device 030: ID 0451:cafe Texas Instruments, Inc.

更多细节查看

    cat /proc/bus/usb/devices

### 11 静态模块地址

fastboot重用内核的nand地址分配方式，并且大部分是可以变化的，但是下面列出来的这些地址是不变的。

    name         offset         size

    xloader      0x00000000   0x00080000

    bootloader   0x00080000   0x00180000

    environment  0x001C0000   0x00040000

### 12 文件大小限制

最大下载文件大小为240M。

### 13 擦除分区：

    fastboot erase {partition} 例：fastboot erase boot或fastboot erase system等。

### 14 烧写指定分区：

    fastboot flash {partition} {*.img} 例：fastboot flash boot boot.img或fastboot flash system system.img等。

### 15 烧写所有分区：

    fastboot flashall 注意：此命令会在当前目录中查找所有img文件，将这些img文件烧写到所有对应的分区中，并重新启动手机。

### 16 一次烧写boot，system，recovery分区：

（1）创建包含boot.img，system.img，recovery.img文件的zip包。

（2）执行：fastboot update {*.zip}

### 17 烧写开机画面：

    fastboot flash splash1 开机画面

### 18 重启手机：

    fastboot reboot

    fastboot reboot-bootloader

