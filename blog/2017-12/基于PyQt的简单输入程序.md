# 基于PyQt的简单输入程序

在 Linux 下有时会出现一下特别难受的就是有些程序是不能输入汉语的如果想要输入汉语只能在外面找个文本编辑器在里面输入然后再复制粘贴进去.这样及其影响自己的心情,也太麻烦了.有写解决的方法又太麻烦.懒得折腾.毕竟有些闭源的程序是没有办法找到解决方案的.所以就要一个简单的解决方法.

## 简介

由于我们的需求就是不要太麻烦,所以功能不能太多操作要尽量的简单喽.
1. 设置一个快捷键 比如我的 Ctrl+Alt+p
2. 按下快捷键后会在鼠标的位置出现一个的窗口
![外观示例](https://copie.cn/usr/uploads/2017/12/3126323023.png)
3. 输入后的样子是这样的
![输入后](https://copie.cn/usr/uploads/2017/12/3192412083.png)
4. 按下ESC 或者失去焦点程序就会自动退出并且把你刚写的汉字复制到粘贴板里面

## 逻辑代码

    import os
    import sys

    import pyperclip
    from PyQt5 import QtCore
    from PyQt5.QtWidgets import QApplication, QMainWindow

    from ui import *
    from Xlib.display import Display

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

至于UI代码可以去我的[giuhub](https://github.com/copie/dayworkspace/tree/master/python/easy_input)