import sys
import serial
import threading
from PyQt5 import uic, QtWidgets

class Ventana(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("Examen Departamental 3.ui", self)

        # QTextEdit
        self.cuadroTexto = self.findChild(QtWidgets.QTextEdit, "lecturas_txt")
        self.estado_anterior = ""  # Guardar el último estado

        # Puerto serial (ajusta COM si es necesario)
        self.serial = serial.Serial("COM3", 9600, timeout=1)

        # Hilo de lectura
        self.thread = threading.Thread(target=self.leer_serial)
        self.thread.daemon = True
        self.thread.start()

    def leer_serial(self):
        while True:
            if self.serial.in_waiting > 0:
                linea = self.serial.readline().decode(errors='ignore').strip()
                print("Datos recibidos:", linea)

                if linea in ["Movimiento", "Sin movimiento"]:
                    if linea != self.estado_anterior:  # Solo si cambia
                        self.cuadroTexto.append(linea)
                        self.estado_anterior = linea
# Ejecutar app
app = QtWidgets.QApplication(sys.argv)
ventana = Ventana()
ventana.show()
sys.exit(app.exec_())
