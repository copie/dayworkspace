# linux创建快照与使用Btrfs文件系统

## Btrfs文件系统

1. 扩展性 (scalability) 相关的特性，btrfs 最重要的设计目标是应对大型机器对文件系统的扩展性要求。 Extent，B-Tree 和动态 inode 创建等特性保证了 btrfs 在大型机器上仍有卓越的表现，其整体性能而不会随着系统容量的增加而降低。

2. 数据一致性 (data integrity) 相关的特性。系统面临不可预料的硬件故障，Btrfs 采用 COW 事务技术来保证文件系统的一致性。 btrfs 还支持 checksum，避免了 silent corrupt 的出现。而传统文件系统则无法做到这一点。

3. 多设备管理相关的特性。 Btrfs 支持创建快照 (snapshot)，和克隆 (clone) 。 btrfs 还能够方便的管理多个物理设备，使得传统的卷管理软件变得多余。

4. 其他难以归类的特性。这些特性都是比较先进的技术，能够显著提高文件系统的时间 / 空间性能，包括延迟分配，小文件的存储优化，目录索引等。

## 使用 apt-btrfs-snapshot 创建快照

当你在使用apt操作软件包时，apt-btrfs-snapshot会自动为系统创建快照。这样即使出现错误也可以轻松的恢复到之前的状态。

**如果你想使用的话需要 Btrfs 的文件系统**

安装系统的时候选择如下：

![ubuntu下Btrfs文件系统选择实例](https://copie.cn/usr/uploads/2017/08/1897167073.png)

### 安装apt-btrfs-snapshot

#### debain 系列(ps:非 debian 系列也不用 APT 吧)

    sudo apt-get install apt-btrfs-snapshot
#### 查看系统是否支持快照

    sudo apt-btrfs-snapshot supported
如果是Supported 表示支持 如果是**… system lacks support for snapshot feature** 建立一下链接就可以了

    sudo ln -s /bin/btrfs /sbin/btrfs

### 生成快照

测试：

    sudo apt update
    sudo apt upgrade

在安装软件前如果你看到了：

    Create a snapshot of '/tmp/apt-btrfs-snapshot-mp-0od17oa1/@' in '/tmp/apt-btrfs-snapshot-mp-0od17oa1/@apt-snapshot-2017-08-17_16:18:24'
说明已经创建成功了快照

#### 查看快照

    sudo apt-btrfs-snapshot list

出现一下内容:

---
    Available snapshots:
    @apt-snapshot-2017-08-15_08:29:06  
    @apt-snapshot-2017-08-15_08:35:11  
    @apt-snapshot-2017-08-15_08:32:57  
    @apt-snapshot-2017-08-15_08:32:58  
    @apt-snapshot-2017-08-15_08:43:04  
    @apt-snapshot-2017-08-15_08:43:34  
    @apt-snapshot-2017-08-15_10:04:35  
    @apt-snapshot-2017-08-15_17:55:21  
    @apt-snapshot-2017-08-15_18:00:57  
    @apt-snapshot-2017-08-16_15:17:11  
    @apt-snapshot-2017-08-16_15:17:30  
    @apt-snapshot-2017-08-16_19:44:40  
    @apt-snapshot-2017-08-16_19:55:16  
    @apt-snapshot-2017-08-17_09:23:47  
    @apt-snapshot-2017-08-17_09:24:17  
    @apt-snapshot-2017-08-17_09:41:23  
    @apt-snapshot-2017-08-17_10:22:09  
    @apt-snapshot-2017-08-17_15:38:22  
    @apt-snapshot-2017-08-17_16:18:24  
    @apt-snapshot-2017-08-17_16:19:26

---

### 恢复快照

如果你的系统被你弄死了，你就要恢复了。。。。

不需要启动盘 挂载btrfs文件系统到/mnt：

    sudo mount /dev/sda1 /mnt

列出subvolumes：

    ls -l /mnt/

把 @apt-snapshot-2017-08-17_16:19:26 重命名为@

    sudo mv /mnt/@ /mnt/@_current
    sudo mv /mnt/@apt-snapshot-2017-08-17_16:19:26 /mnt/@

这样就可以了
重启系统之后你就恢复到之前的快照了

### 删除快照:

    mount /dev/sda1 /mnt/
    btrfs subvolume delete /mnt/@_current
