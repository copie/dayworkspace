# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'tp.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(1053, 761)
        self.label = QtWidgets.QLabel(Form)
        self.label.setGeometry(QtCore.QRect(240, 20, 551, 171))
        self.label.setObjectName("label")
        self.dial = QtWidgets.QDial(Form)
        self.dial.setGeometry(QtCore.QRect(670, 310, 131, 81))
        self.dial.setObjectName("dial")
        self.layoutWidget = QtWidgets.QWidget(Form)
        self.layoutWidget.setGeometry(QtCore.QRect(240, 230, 194, 230))
        self.layoutWidget.setObjectName("layoutWidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.layoutWidget)
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout.setObjectName("verticalLayout")
        self.label_2 = QtWidgets.QLabel(self.layoutWidget)
        self.label_2.setObjectName("label_2")
        self.verticalLayout.addWidget(self.label_2)
        self.label_3 = QtWidgets.QLabel(self.layoutWidget)
        self.label_3.setObjectName("label_3")
        self.verticalLayout.addWidget(self.label_3)
        self.label_4 = QtWidgets.QLabel(self.layoutWidget)
        self.label_4.setObjectName("label_4")
        self.verticalLayout.addWidget(self.label_4)
        self.layoutWidget1 = QtWidgets.QWidget(Form)
        self.layoutWidget1.setGeometry(QtCore.QRect(470, 230, 191, 231))
        self.layoutWidget1.setObjectName("layoutWidget1")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.layoutWidget1)
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.ledT = QtWidgets.QLCDNumber(self.layoutWidget1)
        self.ledT.setObjectName("ledT")
        self.verticalLayout_2.addWidget(self.ledT)
        self.ledE = QtWidgets.QLCDNumber(self.layoutWidget1)
        self.ledE.setObjectName("ledE")
        self.verticalLayout_2.addWidget(self.ledE)
        self.ledH = QtWidgets.QLCDNumber(self.layoutWidget1)
        self.ledH.setObjectName("ledH")
        self.verticalLayout_2.addWidget(self.ledH)

        self.retranslateUi(Form)
        self.dial.valueChanged['int'].connect(self.ledE.display)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))
        self.label.setText(_translate("Form", "<html><head/><body><p><span style=\" font-size:48pt;\">远程温度监控系统</span></p></body></html>"))
        self.label_2.setText(_translate("Form", "<html><head/><body><p><span style=\" font-size:36pt;\">当前温度</span></p></body></html>"))
        self.label_3.setText(_translate("Form", "<html><head/><body><p><span style=\" font-size:36pt;\">风扇转速</span></p></body></html>"))
        self.label_4.setText(_translate("Form", "<html><head/><body><p><span style=\" font-size:36pt;\">当前湿度</span></p></body></html>"))

