from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5 import QtCore
from ui import *
import sys
from Xlib.display import Display
import os
import pyperclip


class shuru:
    def __init__(self):
        self._display = Display(os.environ['DISPLAY'])
        self.app = QApplication(sys.argv)
        self.mainWindow = QMainWindow()
        self.ui = Ui_mainWindow()
        self.ui.setupUi(self.mainWindow)
        self.mainWindow.setWindowTitle("方便输入")
        self.mainWindow.move(*self._position())
        # 输入结束信号连接run槽
        self.ui.lineEdit.editingFinished.connect(self.run)
        # 窗口透明
        self.mainWindow.setWindowOpacity(0.7)
        # 去除顶栏
        self.mainWindow.setWindowFlags(QtCore.Qt.FramelessWindowHint)
        self.mainWindow.show()
        sys.exit(self.app.exec_())

    # 获取鼠标的绝对位置
    def _position(self):
        pos_info = self._display.screen().root.query_pointer()._data
        return pos_info['root_x'], pos_info['root_y']

    def run(self):
        t = self.ui.lineEdit.text()
        self.write_paste(t)
        self.app.exit()

    def write_paste(self, text):
        pyperclip.copy(text)
        print("假设我已经写入到了剪切板")


def main():
    shuru()


if __name__ == '__main__':
    main()
