import sys
import serial
import threading
from PySide6.QtWidgets import QApplication, QWidget, QVBoxLayout, QLabel
from PySide6.QtCore import QTimer

# Configurar a comunicação serial (ajuste a porta conforme necessário)
serial_port = serial.Serial("/dev/ttyUSB0", 115200, timeout=1)

class SerialMonitor(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Monitor Serial - PySide6")
        self.setGeometry(100, 100, 400, 200)

        # Layout
        self.layout = QVBoxLayout()
        self.label = QLabel("Aguardando dados...")
        self.layout.addWidget(self.label)
        self.setLayout(self.layout)

        # Atualizar dados da serial a cada 1s
        self.timer = QTimer()
        self.timer.timeout.connect(self.update_serial_data)
        self.timer.start(1000)

    def update_serial_data(self):
        if serial_port.in_waiting:
            data = serial_port.readline().decode().strip()
            self.label.setText(f"Dado recebido: {data}")

# Inicializar a interface gráfica
app = QApplication(sys.argv)
window = SerialMonitor()
window.show()
sys.exit(app.exec())
