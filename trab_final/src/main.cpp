#include <Arduino.h>

void setup() {
    Serial.begin(115200);
}

void loop() {
    int velocidade = analogRead(A0) / 4;  // Simula leitura de velocidade
    Serial.print("{\"velocidade\":");
    Serial.print(velocidade);
    Serial.println("}");
    delay(500);
}
