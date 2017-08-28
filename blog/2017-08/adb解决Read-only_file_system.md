#  android adb shel l命令使用 解决 Read-only file system

android adb shell命令使用  
当运行一个命令的时候出现
    
    mv failed for /system/fonts/, Read-only file system

## 解决方法：

    mount -o remount rw  /system

也就是将/system分区重新挂载为可读写分区
如果操作完后想恢复为只读，命令如下：

    mount -o ro,remount /system