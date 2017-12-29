#!/bin/bash
# 为/etc/pacman.conf 添加 或者删除指定的 忽略升级的软件包


# copie@Lenovo  ~/Desktop  sudo bash 1.sh nup sddm
# 当前屏蔽了: sddm sddm
# copie@Lenovo  ~/Desktop  sudo bash 1.sh up nup
# 当前屏蔽了: sddm sddm
# copie@Lenovo  ~/Desktop  sudo bash 1.sh up sddm

# 使用方法 将 pacman_back_up.sh 添加运行权限，然后移动 pacman_back_up.sh 到 /usr/bin/ 并在 ~/.zshrc 下添加如下：
# alias pup='sudo pacman_back_up.sh up'
# alias pnp='sudo pacman_back_up.sh nup'

filepath="/etc/pacman.conf"
if [ $# == 2 ]
then
    if [ $1 == 'up' ]
    then
        # 删除指定软件包 `sudo bash 1.sh sddm`
        x='26s/\W'$2'//g'
        sed -i $x $filepath
    fi
    if [ $1 == "nup" ]
    then
    #  添加指定软件包的屏蔽
        x='26s/$/'$2'/'
        sed -i $x $filepath
        sed -i '26s/$/ /' $filepath
    fi
fi

y=`sed -n '26p' $filepath`
echo "当前屏蔽了: "${y:15}
