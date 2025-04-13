import sys
import serial
import json
import numpy as np
from collections import deque
from PySide6.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget
from PySide6.QtCore import QTimer
import pyqtgraph as pg

# Configuração da porta serial (ajuste conforme necessário)
serial_port = serial.Serial("/dev/ttyUSB0", 115200, timeout=1)

# Janela principal
class RealTimePlot(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Gráfico em Tempo Real - Motor")
        self.setGeometry(100, 100, 600, 400)

        # Criar widget central
        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)
        layout = QVBoxLayout(self.central_widget)

        # Criar gráfico com PyQtGraph
        self.graphWidget = pg.PlotWidget()
        layout.addWidget(self.graphWidget)

        # Configurar o gráfico
        self.graphWidget.setBackground("w")
        self.graphWidget.setTitle("Velocidade do Motor")
        self.graphWidget.setLabel("left", "Velocidade", units="RPM")
        self.graphWidget.setLabel("bottom", "Tempo", units="s")
        self.graphWidget.addLegend()
        self.graphWidget.showGrid(x=True, y=True)

        # Criar curva do gráfico
        self.data_x = deque(maxlen=100)  # Armazena os últimos 100 valores no eixo X (tempo)
        self.data_y = deque(maxlen=100)  # Armazena os últimos 100 valores no eixo Y (velocidade)
        self.plot = self.graphWidget.plot(self.data_x, self.data_y, pen=pg.mkPen(color="b", width=2), name="Velocidade")

        # Timer para atualização dos dados
        self.timer = QTimer()
        self.timer.timeout.connect(self.update_plot)
        self.timer.start(100)  # Atualiza a cada 100ms

        # Contador de tempo
        self.time_counter = 0

    def update_plot(self):
        """Lê os dados da serial e atualiza o gráfico."""
        if serial_port.in_waiting:
            try:
                data = serial_port.readline().decode().strip()
                dados_json = json.loads(data)  # Decodifica JSON do microcontrolador
                velocidade = dados_json["velocidade"]

                # Atualiza os dados do gráfico
                self.data_x.append(self.time_counter)
                self.data_y.append(velocidade)
                self.time_counter += 0.1  # Incrementa tempo em 0.1s

                # Atualiza a curva do gráfico
                self.plot.setData(self.data_x, self.data_y)

            except Exception as e:
                print(f"Erro na leitura da serial: {e}")

# Iniciar aplicativo
app = QApplication(sys.argv)
window = RealTimePlot()
window.show()
sys.exit(app.exec())
