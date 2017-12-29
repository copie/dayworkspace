# 一键编译运行 C 代码

由于 使用  vscode 写代码 又不愿意 配置 DEBUG 的配置文件 所以这里就自己写了一个一键运行的脚本

## 使用

1. 
        sudo cp yx.sh /usr/bin/yx
        sudo chmod +x /usr/bin/yx
2.
        yx 1.cpp
        或
        yx # 会自动选择最新的文件进行运行

如果你是 windows 的话我这里也写了 powershell 版的 yx

使用方法:
新建
  
      C:\Users\copie\Documents\WindowsPowerShell\Microsoft.PowerShell_profile.ps1

在里面写入如下:

        Set-Alias yx C:\Users\copie\Documents\dayworkspace\shell\yx\yx.ps1

具体的文件位置要看你自己把我这个脚本放到了哪里了
使用方法和上面写的一样
