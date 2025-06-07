#!/bin/bash

# Caminho para o diretório onde o ambiente virtual será criado
VENV_DIR="/home/marco/projects/embarcados/trab_final/amb"

# Caminho para o código Python que você quer executar
PYTHON_SCRIPT="/home/marco/projects/embarcados/trab_final/src/graph.py"

# Caminho para o arquivo platformio.ini (se necessário)
PIO_DIR="/home/marco/projects/embarcados/trab_final"

# Verificar se o ambiente virtual já existe
if [ ! -d "$VENV_DIR" ]; then
    echo "O ambiente virtual não existe. Criando um novo ambiente virtual..."
    python3 -m venv $VENV_DIR
    source $VENV_DIR/bin/activate
    pip install numpy pyserial pyside6 pyqtgraph
    echo "Ambiente virtual criado com sucesso!"
else
    echo "Ambiente virtual já existe. Ativando o ambiente virtual..."
fi

# Ativar o ambiente virtual
source $VENV_DIR/bin/activate

# Rodar o código do PlatformIO
echo "Executando PlatformIO..."
cd $PIO_DIR  # Navega até o diretório do projeto do PlatformIO
pio run -t upload  # Executa o comando 'pio run' para compilar e carregar o código

# Executar o código Python para plotagem
echo "Executando o script Python..."
python $PYTHON_SCRIPT

# Desativar o ambiente virtual (opcional)
deactivate
