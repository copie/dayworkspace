echo "disabled" > /sys/bus/usb/devices/3-9/power/wakeup

if [ $? -eq 0 ]
then
    echo "已经屏蔽USB2.0唤醒电脑"
else
    echo "屏蔽失败"
fi