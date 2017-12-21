import configparser
import os
import sys

import pyperclip
from PyQt5 import QtCore
from PyQt5.QtWidgets import QApplication, QMainWindow
from Xlib.display import Display

from ui import *


class easyInput:
    _display = Display(os.environ['DISPLAY'])

    def __init__(self):
        self.app = QApplication(sys.argv)
        self.mainWindow = QMainWindow()
        self.ui = Ui_mainWindow()
        self.ui.setupUi(self.mainWindow)
        self.mainWindow.setWindowTitle("方便输入")
        self.config = configparser.ConfigParser()
        self.config = configparser.ConfigParser()
        self.config.read('.easy_input_rc')
        self.ui.lineEdit.mouseDoubleClickEvent = self.config_panel

    def config_panel(self, *kw):
        # 这里显示面板
        print(kw)
        print("我也许是面板吧")

    def _getconfig(self):
        # 获取配置文件
        self.font_size = 23
        # 字体大小
        self.windowW = 450
        self.windowH = 60
        # 窗口大小
        self.windowOpacity = 0.7
        # 窗口透明度
        self.background = "#2F4F4F"
        # 背景颜色
        self.font_color = "rgb(230,230,250)"
        # 字体颜色
        if 'info' in self.config.sections():
            self.font_size = int(self.config.get("info", "font_size"))
            self.windowW = int(self.config.get("info", "windowW"))
            self.windowH = int(self.config.get("info", "windowH"))
            self.windowOpacity = float(
                self.config.get("info", "windowOpacity"))
            self.background = self.config.get("info","background")
            self.font_color = self.config.get("info","font_color")
        else:
            self.config.add_section("info")

    def _writeconfig(self):
        # 写入配置文件
        self.config.set("info", "font_size", str(self.font_size))
        self.config.set("info", "windowW", str(self.windowW))
        self.config.set("info", "windowH", str(self.windowH))
        self.config.set("info", "windowOpacity", str(self.windowOpacity))
        self.config.set("info","background",self.background)
        self.config.set("info","font_color",self.font_color)
        self.config.write(open(".easy_input_rc", "w"))

    def _lodeconfig(self):
        # 根据配置文件重新设置界面
        self.mainWindow.resize(self.windowW, self.windowH)
        self.mainWindow.setMinimumSize(
            QtCore.QSize(self.windowW, self.windowH))
        self.mainWindow.setMaximumSize(
            QtCore.QSize(self.windowW, self.windowH))
        self.ui.lineEdit.setGeometry(
            QtCore.QRect(0, 0, self.windowW, self.windowH))
        self.ui.lineEdit.setMinimumSize(
            QtCore.QSize(self.windowW, self.windowH))
        self.ui.lineEdit.setMaximumSize(
            QtCore.QSize(self.windowW, self.windowH))
        font = QtGui.QFont()
        font.setPointSize(self.font_size)
        self.ui.lineEdit.setFont(font)
        self.mainWindow.setWindowOpacity(self.windowOpacity)
        self.ui.lineEdit.setStyleSheet("background:{};color:{};".format(self.background,self.font_color))
        
    def run(self):

        self.mainWindow.move(*self._position())
        # 输入结束信号连接run槽
        self.ui.lineEdit.editingFinished.connect(self.call_action)
        # 重写keyPressEvent
        self.ui.lineEdit.keyPressEvent = self.keypressevent(
            self.ui.lineEdit.keyPressEvent)
        # 去除顶栏
        self.mainWindow.setWindowFlags(QtCore.Qt.FramelessWindowHint)
        self._getconfig()
        self._lodeconfig()
        self._writeconfig()
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
