# 屏蔽Linux被鼠标意外唤醒

惊奇的发现我的电脑在关机和睡眠的时候是对USB供电的。关机还好，睡眠的时候我的无线鼠标就会把电脑唤醒，这样的话就尴尬了。电脑在书包里面风扇呼呼地转。然后一会就没电了。

用以下方法屏蔽无线鼠标唤醒就可以了。
    
    echo "XHC" > /proc/acpi/wakeup
    echo "EHC1" > /proc/acpi/wakeup
    echo "EHC2" > /proc/acpi/wakeup
