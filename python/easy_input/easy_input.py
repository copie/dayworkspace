from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5 import QtCore
from ui import *
import sys
from Xlib.display import Display
import os
import pyperclip


class easyInput:
    _display = Display(os.environ['DISPLAY'])

    def __init__(self):
        self.app = QApplication(sys.argv)
        self.mainWindow = QMainWindow()
        self.ui = Ui_mainWindow()
        self.ui.setupUi(self.mainWindow)
        self.mainWindow.setWindowTitle("方便输入")

    def run(self):

        self.mainWindow.move(*self._position())
        # 输入结束信号连接run槽
        self.ui.lineEdit.editingFinished.connect(self.call_action)
        # 重写keyPressEvent
        self.ui.lineEdit.keyPressEvent = self.keypressevent(
            self.ui.lineEdit.keyPressEvent)
        # 窗口透明
        self.mainWindow.setWindowOpacity(0.7)
        # 去除顶栏
        self.mainWindow.setWindowFlags(QtCore.Qt.FramelessWindowHint)
        self.mainWindow.show()
        sys.exit(self.app.exec_())

    # 获取鼠标的绝对位置
    @classmethod
    def _position(cls):
        pos_info = cls._display.screen().root.query_pointer()._data
        return pos_info['root_x'], pos_info['root_y']

    def call_action(self):
        text = self.ui.lineEdit.text()
        self.write_paste(text)
        self.app.exit()

    def keypressevent(self, fun):
        def warr(event):
            if event.key() == QtCore.Qt.Key_Escape:
                self.call_action()
            else:
                fun(event)
        return warr

    @staticmethod
    def write_paste(text):
        pyperclip.copy(text)
        print("假设我已经写入到了剪切板")


def main():
    window = easyInput()
    window.run()

if __name__ == '__main__':
    main()
