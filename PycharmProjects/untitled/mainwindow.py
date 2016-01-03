# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '/home/emiliano/Qt/Test1/mainwindow.ui'
#
# Created by: PyQt5 UI code generator 5.5.1
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(400, 300)
        self.centralWidget = QtWidgets.QWidget(MainWindow)
        self.centralWidget.setObjectName("centralWidget")
        self.formLayoutWidget = QtWidgets.QWidget(self.centralWidget)
        self.formLayoutWidget.setGeometry(QtCore.QRect(9, 9, 371, 211))
        self.formLayoutWidget.setObjectName("formLayoutWidget")
        self.formLayout = QtWidgets.QFormLayout(self.formLayoutWidget)
        self.formLayout.setFieldGrowthPolicy(QtWidgets.QFormLayout.AllNonFixedFieldsGrow)
        self.formLayout.setContentsMargins(11, 11, 11, 11)
        self.formLayout.setSpacing(6)
        self.formLayout.setObjectName("formLayout")
        self.reiniciar = QtWidgets.QPushButton(self.formLayoutWidget)
        self.reiniciar.setObjectName("reiniciar")
        self.formLayout.setWidget(0, QtWidgets.QFormLayout.FieldRole, self.reiniciar)
        self.salir = QtWidgets.QPushButton(self.formLayoutWidget)
        self.salir.setObjectName("salir")
        self.formLayout.setWidget(1, QtWidgets.QFormLayout.FieldRole, self.salir)
        self.grafico = QtWidgets.QGraphicsView(self.formLayoutWidget)
        self.grafico.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.grafico.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.grafico.setLineWidth(5)
        self.grafico.setMidLineWidth(5)
        self.grafico.setObjectName("grafico")
        self.formLayout.setWidget(0, QtWidgets.QFormLayout.LabelRole, self.grafico)
        MainWindow.setCentralWidget(self.centralWidget)
        self.menuBar = QtWidgets.QMenuBar(MainWindow)
        self.menuBar.setGeometry(QtCore.QRect(0, 0, 400, 27))
        self.menuBar.setObjectName("menuBar")
        self.menuArchivo = QtWidgets.QMenu(self.menuBar)
        self.menuArchivo.setObjectName("menuArchivo")
        MainWindow.setMenuBar(self.menuBar)
        self.mainToolBar = QtWidgets.QToolBar(MainWindow)
        self.mainToolBar.setObjectName("mainToolBar")
        MainWindow.addToolBar(QtCore.Qt.TopToolBarArea, self.mainToolBar)
        self.statusBar = QtWidgets.QStatusBar(MainWindow)
        self.statusBar.setObjectName("statusBar")
        MainWindow.setStatusBar(self.statusBar)
        self.actionSalir = QtWidgets.QAction(MainWindow)
        self.actionSalir.setObjectName("actionSalir")
        self.menuArchivo.addAction(self.actionSalir)
        self.menuBar.addAction(self.menuArchivo.menuAction())

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.reiniciar.setText(_translate("MainWindow", "Reiniciar"))
        self.salir.setText(_translate("MainWindow", "Salir"))
        self.menuArchivo.setTitle(_translate("MainWindow", "Archivo"))
        self.actionSalir.setText(_translate("MainWindow", "Salir"))


# if __name__ == "__main__":
#     import sys
#     app = QtWidgets.QApplication(sys.argv)
#     MainWindow = QtWidgets.QMainWindow()
#     ui = Ui_MainWindow()
#     ui.setupUi(MainWindow)
#     MainWindow.show()
#     sys.exit(app.exec_())

