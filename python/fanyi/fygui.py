import os
import sys
import time
import requests
from PyQt5 import QtCore, QtWidgets
from PyQt5.QtGui import QClipboard
from PyQt5.QtWidgets import QApplication, QMainWindow
from Xlib.display import Display

from ui import *
from inputT import *
from wordutil import wordutil


class fygui():
    _display = Display(os.environ['DISPLAY'])

    def __init__(self):
        self.app = QApplication(sys.argv)
        self.mainWindow = QMainWindow()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self.mainWindow)

        self.Dialog = QtWidgets.QDialog()
        self.ui2 = Ui_Form()
        self.ui2.setupUi(self.Dialog)

        self.ui.textEdit.setReadOnly(True)
        self.clipboard = QApplication.clipboard()
        self.clipboard.selectionChanged.connect(self.fanyi)
        self.mainWindow.setWindowTitle("划词翻译")
        self.mainWindow.setWindowFlags(QtCore.Qt.WindowStaysOnTopHint)
        self.ui2.lineEdit.editingFinished.connect(self.callInput)
        self.Dialog.moveEvent = self.mainMove
        self.wordutil = wordutil()
        self.time = time.time()
        self.ui.textEdit.mouseDoubleClickEvent = self.inputText

    def mainMove(self, *kw):
        pos = self.Dialog.pos()
        x = pos.x()
        y = pos.y()
        if x > 400:
            x -= 400
        else:
            x += 380
        self.mainWindow.move(x, y)

    def callInput(self):
        text = self.ui2.lineEdit.text()
        if text != '':
            text = self.wordutil.execfind(text)
            self.ui.textEdit.clear()
            self.ui.textEdit.insertHtml(text)
        self.Dialog.close()

    def inputText(self, *kw):
        pos = self.mainWindow.pos()
        self.Dialog.move(pos.x() + 400, pos.y())
        self.Dialog.show()

    @classmethod
    def _position(cls):
        pos_info = cls._display.screen().root.query_pointer()._data
        return pos_info['root_x'] + 50, pos_info['root_y'] + 50

    def fanyi(self):
        if time.time() - self.time < 0.3:
            print("停一下")
            return
        self.time = time.time()
        if self.ui.textEdit.hasFocus():
            return
        text = self.clipboard.text(self.clipboard.Selection)
        if len(text) > 20:
            return
        self.mainWindow.move(*self._position())
        texttmp = ""
        for c in text:
            if c.isupper():
                texttmp += " " + c
            else:
                texttmp += c
        text = texttmp
        text = text.strip(' ')
        if text != '':
            text = self.wordutil.execfind(text)
            self.ui.textEdit.clear()
            self.ui.textEdit.insertHtml(text)

    def run(self):
        self.mainWindow.show()
        sys.exit(self.app.exec_())


def main():
    window = fygui()
    window.run()


if __name__ == '__main__':
    main()
