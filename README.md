## Tópicos especiais em sistemas embarcados
### Comandos platformio
#### inicializar projeto
```shell

//inicializar projeto
pio project init --board uno
//compilar
pio run

pio run -t upload
pio run --target upload


//porta serial
pio device monitor
pio device monitor --port /dev/ttyUSB0


```
