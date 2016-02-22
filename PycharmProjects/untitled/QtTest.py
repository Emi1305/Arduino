import sys, time
from datetime import datetime
from PyQt5 import QtGui, QtWidgets
from PyQt5.QtWidgets import *
from mainwindow import Ui_MainWindow
from PyQt5.QtGui import QPainter, QPen, QColor
from PyQt5.QtCore import Qt
archLog = None

def logger(funcion):
    def inner(*args):
        global archLog
        if not archLog:
            archLog = open('/home/emiliano/Python/QtTest.log', 'w+')
        archLog.write('[' + str(datetime.fromtimestamp(time.time())) + '] ' + funcion.__name__ + '(' + str(args) + ')')
        archLog.flush()
        return funcion(*args)
    return inner

class Arduino():
    miArduino = None
    class __Arduino__():
        def __init__(self):
            import serial
            self.ser = serial.Serial("/dev/ttyACM0",9600)

        @logger
        def pedirTemperatura(self):
            '''Devuelve la temperatura XX.X °C'''
            Arduino.miArduino.ser.write(b'T')
            s = Arduino.miArduino.ser.readline()
            return float(s)/10

        @logger
        def pedirHumedad(self):
            '''Devuelve la humedad en XX.XX%'''
            Arduino.miArduino.ser.write(b'H')
            s = Arduino.miArduino.ser.readline()
            return float(s)

        def cerrarConexion(self):
            self.ser.close()
    def __init__(self):
        if not Arduino.miArduino:
            Arduino.miArduino = Arduino.__Arduino__()
    def __getattr__(self, item):
        return getattr(self.miArduino, item)

class WidgetPrincipal(Ui_MainWindow):
    def setupUi(self, MainWindow):
        super(WidgetPrincipal, self).setupUi(MainWindow)
        self.salir.clicked.connect(self.close(MainWindow))
        self.actionSalir.triggered.connect(self.close(MainWindow))
        self.reiniciar.clicked.connect(self.medirTemperatura)


    def medirTemperatura(self):
        temperatura = Arduino().pedirTemperatura()
        def innerPaint(this):
            painter = QPainter()
            painter.begin(this)
            painter.setPen(QPen(QColor(255,0,0,0), 20))
            painter.drawLine(10,10,500,500)
            painter.end()
        self.grafico.paintEvent = innerPaint
        self.grafico.paintEvent()


        self.statusBar.showMessage(str(temperatura))

    def medirHumedad(self):
        humedad = Arduino().pedirHumedad()
        self.statusBar.showMessage(str(humedad)+'%')


    def close(self, MainWindow):
        def __innerClose__():
            reply = QMessageBox.question(MainWindow,'', "Seguro?", QMessageBox.Yes | QMessageBox.No , QMessageBox.No)
            if reply == QMessageBox.Yes:
                global archLog
                archLog.close()
                Arduino().cerrarConexion()
                MainWindow.close()
        return __innerClose__


class MyQApplication(QtWidgets.QApplication):
    def __init__(self, args):
        super(MyQApplication, self).__init__(args)
        from serial import SerialException
        try:
            Arduino()
        except SerialException:
            error = QErrorMessage()
            error.showMessage('No se encuentra el arduino')
            error.exec_()
            #quit()


if __name__ == '__main__':
    app = MyQApplication(sys.argv)
    window = QMainWindow()
    ui = WidgetPrincipal()
    ui.setupUi(window)
    window.show()
    sys.exit(app.exec())