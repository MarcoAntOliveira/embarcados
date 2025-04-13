// Exemplo de como ler uma entrada analógica, convertê-la para 
// o valor real e enviar pela serial. Além da opção com delay, que
// prende o processador gastando tempo, tem  a opção com um contador
// e ainda como utilizar a estrutura SWITCH-CASE para múltiplas
// decisões a respeito de comandos com valores de 1 a 4 recebidos
// pela serial que ligam leds específicos.

// Abrir o MONITOR SERIAL abaixo e digitar valores entre 1 e 4
// Observar leds e observar o envio dos valores lidos, comparando
// com os informados no voltímetro da simulação. Girar o potenciômetro
// e observar as diferentes leituras.


// INICIA COM AS DEFINIÇÕES DE VARIÁVEIS
// LED conectado ao pino digital 13
int ledPin = 13;   
// contador para definir tarefas
int conta = 0;	
const int Led1 = 7;
const int Led2 = 8;
const int Led3 = 9;
const int Led4 = 10;


// SEMPRE TEM UM SETUP PARA DEFINIR HARDWARE E PINOS
void setup() {
// configura pinos de TX e RX como comunicação serial com taxa de 9600bps 
Serial.begin(9600);
// configura pino digital como saída
pinMode(ledPin, OUTPUT); 
  
pinMode(Led1, OUTPUT);
pinMode(Led2, OUTPUT);
pinMode(Led3, OUTPUT);
pinMode(Led4, OUTPUT);
  
}


// LAÇO INFINITO PARA RODAR ETERNAMENTE O CÓDIGO PRINCIPAL
void loop() {
  // ********Código da leitura AD*********
  // faz a leitura analogical do pino 0:
  int sensorValue = analogRead(A0);
  // Converte a leitura analógica (que vai de 0 - 1023) para um valor de tensão (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // escreve o valor de tensão via comunicação serial:
  Serial.print("Valor real lido no pino   A0 = ");
  Serial.println(voltage);  
  int voltage2 = map(sensorValue, 0, 1023, 0, 50);
  Serial.print("Valor real convertido c/ map = ");
  Serial.println(voltage2);
  
  // ********Código do Pisca-Pisca********
  // OPÇÃO 1
  /*
  digitalWrite(ledPin, HIGH);   // liga o LED
  delay(500);                  // temporiza 1 segundo
  digitalWrite(ledPin, LOW);    // desliga o LED
  delay(500);                  // aguarda mais um segundo
  */
  
  // OPÇÃO 2
  // liga o LED
  if (conta < 10)   digitalWrite(ledPin, HIGH); 
  // desliga o LED
  if (conta >=10)  digitalWrite(ledPin, LOW); 
  // aguarda mais 10 milisegundos
  delay(500); 
  // incrementa a variável conta
  conta++;
  // limita o valor da variável conta em 200 com o teste
  if (conta >= 20) conta =0;

  
  // ********Estrutura de decisão********
  if (Serial.available()) {
   char Caracter_Lido = Serial.read();
   switch (Caracter_Lido) {
     case '1':
      digitalWrite(Led1, HIGH);
      digitalWrite(Led2, LOW);
      digitalWrite(Led3, LOW);
      digitalWrite(Led4, LOW);
      break;
     case '2':
      digitalWrite(Led1, HIGH);
      digitalWrite(Led2, HIGH);
      digitalWrite(Led3, LOW);
      digitalWrite(Led4, LOW);
      break;
     case '3':
      digitalWrite(Led1, HIGH);
      digitalWrite(Led2, HIGH);
      digitalWrite(Led3, HIGH);
      digitalWrite(Led4, LOW);
      break;
     case '4':
      digitalWrite(Led1, HIGH);
      digitalWrite(Led2, HIGH);
      digitalWrite(Led3, HIGH);
      digitalWrite(Led4, HIGH);
      break;
     default:
      Serial.print("Valor ");
      Serial.print(Caracter_Lido);
      Serial.println(" incorreto.");
      digitalWrite(Led1, LOW);
      digitalWrite(Led2, LOW);
      digitalWrite(Led3, LOW);
      digitalWrite(Led4, LOW);
     }
   }

}
