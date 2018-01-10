# Linux 下安装 PowerShell 并创建配置文件

## Linux 安装 PowerShell
[安装教程](https://github.com/PowerShell/PowerShell/blob/master/README.md)
这里是官方给出的教程如果你用的是 红帽系,或者 debian 系的话比较简单.由于我用的是 Arch 要用 AUR 安装 PowerShell-bin 从源码安装比较麻烦所以直接安装二进制还是比较好的.看官方教程安装还是比较简单的.

## 创建配置文件

1. 在 Windows PowerShell 提示符处，键入以下命令，然后按 Enter：

    Test-path $profile

2. 如果上一个命令的结果为 false，则转到步骤 3。如果结果为 true，则转到步骤 4。

3. 键入以下命令，然后按 Enter。

    New-item –type file –force $profile

4. 键入以下命令，然后按 Enter。

    vim $profile

5. 输入自己要在运行 PowerShell 需要运行的命令就可以了
