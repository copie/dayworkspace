# 用来测试马达空占比的代码
import RPi.GPIO as gpio
import time
gpio.setmode(gpio.BOARD)
gpio.setup(40, gpio.OUT)  # 板子上面的40引脚 马达的引脚
mada_rate = 10


def main():
    global mada_rate
    while True:
        mada_rate +=0.1
        gpio.output(40, gpio.HIGH)
        time.sleep(mada_rate / 10000)
        gpio.output(40, gpio.LOW)
        time.sleep(0.01-mada_rate / 10000)
        print(mada_rate)


if __name__ == '__main__':
    main()
    gpio.cleanup()
