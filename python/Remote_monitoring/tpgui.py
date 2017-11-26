from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5 import QtCore
from tp import *
import sys
import os
from PyQt5.QtCore import QThread, pyqtSignal
import requests
import time


class mythread(QThread):
    # 建立两个信号
    _signalt = pyqtSignal(int)
    _signalh = pyqtSignal(int)

    def __init__(self):
        super(mythread, self).__init__()

    def run(self):
        while True:
            print("hello")
            req = requests.get("http://106.14.222.191:5000/")
            # 获取温湿度
            print(req)
            temperature, humidity = map(int, map(float, req.text.split()))
            print(temperature, humidity)
            self._signalt.emit(temperature)
            # 发出温度信号
            self._signalh.emit(humidity)
            # 发出湿度信号
            time.sleep(0.5)


class tpgui:

    def __init__(self):
        self.app = QApplication(sys.argv)
        self.mainWindow = QMainWindow()
        self.ui = Ui_Form()
        self.ui.setupUi(self.mainWindow)
        self.mainWindow.setWindowTitle("温湿监控")
        self.thread = None

    def ch_rate(self, rate):
        '''改变马达空占比'''
        requests.get("http://copie.cn:5000/madarate?rate="+str(rate))

    def run(self):
        self.mainWindow.show()
        self.thread = mythread()
        self.thread._signalt.connect(self.ui.ledT.display)
        # 在 ui.ledT 显示温度
        self.thread._signalh.connect(self.ui.ledH.display)
        # 在 ui.ledT 显示湿度
        self.thread.start()
        self.ui.dial.valueChanged.connect(self.ch_rate)
        # 如果旋钮dial 被转动
        sys.exit(self.app.exec_())


def main():
    window = tpgui()
    window.run()


if __name__ == '__main__':
    main()
