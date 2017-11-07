# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ppp.ui'
#
# Created by: PyQt5 UI code generator 5.9
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_mainWindow(object):
    def setupUi(self, mainWindow):
        mainWindow.setObjectName("mainWindow")
        mainWindow.resize(604, 100)
        mainWindow.setMinimumSize(QtCore.QSize(604, 100))
        mainWindow.setMaximumSize(QtCore.QSize(604, 100))
        self.lineEdit = QtWidgets.QLineEdit(mainWindow)
        self.lineEdit.setGeometry(QtCore.QRect(2, 0, 601, 101))
        self.lineEdit.setMinimumSize(QtCore.QSize(601, 101))
        self.lineEdit.setMaximumSize(QtCore.QSize(601, 101))
        font = QtGui.QFont()
        font.setPointSize(28)
        self.lineEdit.setFont(font)
        self.lineEdit.setObjectName("lineEdit")

        self.retranslateUi(mainWindow)
        QtCore.QMetaObject.connectSlotsByName(mainWindow)

    def retranslateUi(self, mainWindow):
        _translate = QtCore.QCoreApplication.translate
        mainWindow.setWindowTitle(_translate("mainWindow", "Form"))

