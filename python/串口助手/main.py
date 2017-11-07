import sys
import time
from queue import Queue

from PyQt5.QtCore import QThread, pyqtSignal
from PyQt5.QtWidgets import QApplication, QMainWindow
from serial import Serial

from ui import *

KILL_THREAD_FLAG = Queue(1)


class mythread(QThread):
    _signal = pyqtSignal(str)

    def __init__(self, server, kill_key):
        self.server = server
        self.kill_key = kill_key
        super(mythread, self).__init__()

    def run(self):
        while True:
            try:
                print(self.server.isOpen())
                text = self.server.read(1)
            except Exception as e:
                print("hello world!")
                print(e)
                # self.server.close()
                return
            else:
                try:
                    text =  text.decode()
                except UnicodeDecodeError as e:
                    self._signal.emit(str(text))
                else:
                    self._signal.emit(text)
            tmp = None
            try:
                tmp = KILL_THREAD_FLAG.get_nowait()
            except Exception as e:
                pass
            if tmp is not self.kill_key:
                if tmp is not None:
                    Queue.put(tmp)
            else:
                return


class myserial:
    def __init__(self):
        self.app = QApplication(sys.argv)
        self.mainWindow = QMainWindow()
        self.ui = Ui_mainWindrow()
        self.ui.setupUi(self.mainWindow)
        self.mainWindow.setWindowTitle("串口助手")
        self.ui.openCloseButton.clicked.connect(self.open_close_serial)
        self.ui.sendButton.clicked.connect(self.send_msg)
        self.mainWindow.show()
        self.server = None
        self.port = None
        self.rate = 9600
        self.thread = None
        sys.exit(self.app.exec_())

    def open_close_serial(self):
        if self.ui.openCloseButton.text() == "打开串口":
            self._get_info()
            try:
                self.server = Serial(port=self.port, baudrate=self.rate)
            except Exception as e:
                self.ui.inputEdit.clear()
                self.ui.inputEdit.insertPlainText("打开串口失败请选择适当的端口,并添加权限")
            else:

                if self.server.isOpen() is True:
                    print("打开串口成功")
                    self.ui.openCloseButton.setText("关闭串口")
                    self.thread = mythread(self.server, 'shabi')
                    self.thread._signal.connect(
                        self.ui.outputEdit.insertPlainText)
                    self.thread.start()
        else:
            self.server.close()
            if self.server.isOpen() is False:
                print("关闭串口成功")
                self.ui.openCloseButton.setText("打开串口")
                KILL_THREAD_FLAG.put("shabi")
                time.sleep(0.5)

    def _get_info(self):
        self.port = self.ui.portBox.currentText()
        self.rate = self.ui.rateBox.currentText()

    def send_msg(self):
        text = self.ui.inputEdit.toPlainText()
        try:
            self.server.write(text.encode())
        except AttributeError as e:
            self.ui.inputEdit.clear()
            self.ui.inputEdit.insertPlainText("请打开串口连接")
        else:
            self.ui.inputEdit.clear()
            self.ui.inputEdit.focusWidget()


def main():
    myserial()


if __name__ == '__main__':
    main()
