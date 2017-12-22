import configparser
import os
import sys

import pyperclip
from PyQt5 import QtCore
from PyQt5.QtWidgets import QApplication, QMainWindow
from Xlib.display import Display

from config import *
from ui import *


class easyInput:
    _display = Display(os.environ['DISPLAY'])

    def __init__(self):
        self.app = QApplication(sys.argv)
        self.mainWindow = QMainWindow()
        self.ui = Ui_mainWindow()
        self.ui.setupUi(self.mainWindow)
        self.mainWindow.setWindowTitle("方便输入")
        self.config_init()

    def config_init(self):
        '''与配置文件有关的初始化'''
        self.config = configparser.ConfigParser()
        self.config.read('.easy_input_rc')
        self.ui.lineEdit.mouseDoubleClickEvent = self.config_panel
        # 加载设置窗口
        self.Dialog = QtWidgets.QDialog()
        self.ui2 = Ui_config_panel()
        self.ui2.setupUi(self.Dialog)
        self.Dialog.setWindowTitle("设置")
        self.test_text = "我能吞下玻璃,而不伤身体"
        self.tmpText = "我能吞下玻璃,而不伤身体"

    def value_change(self):
        '''当设置的值改变的时候获取改变
            并从新加载输入窗口设置'''
        self.font_size = self.ui2.font_size.value()
        self.windowW = self.ui2.windowW.value()
        self.windowH = self.ui2.windowH.value()
        self.windowOpacity = self.ui2.windowOpacity.value()
        self.font_color = self.ui2.font_color.text()
        self.background = self.ui2.background.text()
        self._lodeconfig()

    def save(self):
        ''' 点击设置中的保存键后
            配置写入文件
            关闭设置'''
        self._writeconfig()
        self.Dialog.close()

    def close(self, close_even):
        ''' 设置界面关闭后
            恢复输入框的状态
            即打开设置之前的状态'''
        if close_even.isAccepted() is True:
            # 设置输入框可写
            self.ui.lineEdit.setReadOnly(False)
            # 双击输入框会弹出设置窗口
            self.ui.lineEdit.mouseDoubleClickEvent = self.config_panel
            # 恢复输入框里面的文字
            self.ui.lineEdit.setText(self.tmpText)
    def close_back(self):
        self._getconfig()
        self._lodeconfig()
        self.Dialog.close()
        
    def config_panel(self, *kw):
        '''显示面板'''
        self.ui2.font_size.setValue(self.font_size)
        self.ui2.windowW.setValue(self.windowW)
        self.ui2.windowH.setValue(self.windowH)
        self.ui2.windowOpacity.setValue(self.windowOpacity)
        self.ui2.font_color.setText(self.font_color)
        self.ui2.background.setText(self.background)

        self.ui2.font_size.valueChanged.connect(self.value_change)
        self.ui2.windowW.valueChanged.connect(self.value_change)
        self.ui2.windowH.valueChanged.connect(self.value_change)
        self.ui2.windowOpacity.valueChanged.connect(self.value_change)
        self.ui2.font_color.textChanged.connect(self.value_change)
        self.ui2.background.textChanged.connect(self.value_change)
        self.ui2.save.clicked.connect(self.save)
        self.ui2.close.clicked.connect(self.close_back)
        self.Dialog.closeEvent = self.close
        self.Dialog.show()

    def _getconfig(self):
        '''获取配置文件'''
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
            self.background = self.config.get("info", "background")
            self.font_color = self.config.get("info", "font_color")
        else:
            self.config.add_section("info")

    def _writeconfig(self):
        '''写入配置文件'''
        self.config.set("info", "font_size", str(self.font_size))
        self.config.set("info", "windowW", str(self.windowW))
        self.config.set("info", "windowH", str(self.windowH))
        self.config.set("info", "windowOpacity", str(self.windowOpacity))
        self.config.set("info", "background", self.background)
        self.config.set("info", "font_color", self.font_color)
        self.config.write(open(".easy_input_rc", "w"))

    def _lodeconfig(self):
        '''根据配置文件重新设置界面'''
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
        self.ui.lineEdit.setStyleSheet(
            "background:{};color:{};".format(self.background, self.font_color))

    def run(self):
        '''运行并显示窗口'''
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

    @classmethod
    def _position(cls):
        '''获取鼠标的绝对位置'''
        pos_info = cls._display.screen().root.query_pointer()._data
        return pos_info['root_x'], pos_info['root_y']

    def call_action(self):
        ''' 输入窗口认为自己输入结束后的动作
            用户按下回车
            输入框失去焦点'''
        if self.Dialog.isVisible():
            # 如果是因为设置界面弹出的话
            self.ui.lineEdit.setReadOnly(True)
            self.ui.lineEdit.mouseDoubleClickEvent = None
            self.tmpText = self.ui.lineEdit.text()
            self.ui.lineEdit.setText(self.test_text)
        else:
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
