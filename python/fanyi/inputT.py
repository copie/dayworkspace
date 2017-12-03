# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'inputT.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(376, 68)
        Form.setMinimumSize(QtCore.QSize(376, 68))
        Form.setMaximumSize(QtCore.QSize(376, 68))
        self.lineEdit = QtWidgets.QLineEdit(Form)
        self.lineEdit.setGeometry(QtCore.QRect(0, 0, 381, 71))
        self.lineEdit.setMinimumSize(QtCore.QSize(381, 71))
        self.lineEdit.setMaximumSize(QtCore.QSize(381, 71))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.lineEdit.setFont(font)
        self.lineEdit.setObjectName("lineEdit")

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "输入框"))

