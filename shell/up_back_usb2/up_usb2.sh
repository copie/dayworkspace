echo "enabled" > /sys/bus/usb/devices/3-9/power/wakeup

if [ $? -eq 0 ]
then
    echo "已经恢复USB2.0唤醒电脑"
else
    echo "恢复失败"
fi