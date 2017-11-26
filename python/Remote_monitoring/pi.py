# 树梅派下的程序,完成对于DHT11传感器数据的监控与上传
# 或取远程的对与风扇的控制信息来调整风扇的状态

import threading
import time

import requests

import Adafruit_DHT
import RPi.GPIO as gpio

gpio.setmode(gpio.BOARD)
gpio.setup(40, gpio.OUT)  # 板子上面的40引脚 马达的引脚
mada_rate = 0    # 马达 PWM 的空占比


def mada():
    '''这里将0.01秒分成100份进行PWM调速'''
    while True:
        gpio.output(40, gpio.HIGH)
        time.sleep(mada_rate / 10000)
        gpio.output(40, gpio.LOW)
        time.sleep(0.01 - mada_rate / 10000)

threading.Thread(target=mada, args=()).start()
# 开一个线程进行控制马达电机

while True:
    print("begin")
    try:
        # 从传感器湿度和温度 这里用的是DHT11传感器,树梅派的十八引脚
        humidity, temperature = Adafruit_DHT.read_retry(
            Adafruit_DHT.DHT11, "18")
        print("获取完毕")
        # 上传获取的温湿度 链接为 http://copie.cn:5000/update?h=湿度&t=温度
        # 这个链接返回的是 "15 44" 不加引号这样的字符串
        res = requests.get(
            "http://copie.cn:5000/update?h={1:0.1f}&t={0:0.1f}".format(humidity, temperature))
        print(res.text)
        # 从远程获取马达的空占比
        # 这个链接返回的是一个字符串 "21" 不加引号
        mada_rate = int(requests.get("http://copie.cn:5000/madarate").text)
        print("这是马达rate", mada_rate)

    except Exception:
        print("error")
        time.sleep(30)
