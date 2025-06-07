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

// #include <Arduino.h>

// void setup() {
//     Serial.begin(115200);
// }

// void loop() {
//     // ATENÇÃO: o ESP8266 tem apenas 1 pino analógico (A0) com resolução de 10 bits (0–1023)
//     // Alguns modelos usam um divisor de tensão interno. Verifique antes de usar sensores externos!

//     int velocidade = analogRead(A0) / 4;  // Converte para 8 bits (0–255)
//     Serial.print("{\"velocidade\":");
//     Serial.print(velocidade);
//     Serial.println("}");
//     delay(500);
// }

// #include <Arduino.h>

// void setup() {
//   pinMode(LED_BUILTIN, OUTPUT);  // LED onboard
//   Serial.begin(115200);          // Inicializa serial
//   Serial.println("ESP8266 pronto!");
// }

// void loop() {
//   digitalWrite(LED_BUILTIN, LOW);   // Liga o LED (ativo em nível baixo)
//   Serial.println("LED ON");
//   delay(500);

//   digitalWrite(LED_BUILTIN, HIGH);  // Desliga o LED
//   Serial.println("LED OFF");
//   delay(500);
// }
