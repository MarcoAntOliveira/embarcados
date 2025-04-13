// Exemplo de como ler uma entrada digital, teclado matricial e acionamento de display.


// Abrir o MONITOR SERIAL abaixo e digitar valores entre 1 e 4
// Observar leds e observar o envio dos valores lidos, comparando
// com os informados no voltímetro da simulação. Girar o potenciômetro
// e observar as diferentes leituras.


// INICIA COM AS DEFINIÇÕES DE VARIÁVEIS
// LEDs conectados aos pinos de saídas digitais 12 e 13
int ledVD = 12;
int ledVM = 13; 
// contador para definir tarefas
int conta = 0;	
// Conexões do teclado
const int Teclad_linhaA = 9;
const int Teclad_linhaB = 8;
const int Teclad_linhaC = 7;
const int Teclad_linhaD = 6;


// SEMPRE TEM UM SETUP PARA DEFINIR HARDWARE E PINOS
void setup() {
// configura pinos de TX e RX como comunicação serial com taxa de 9600bps 
Serial.begin(9600);
// configura pino digital como saída
pinMode(ledVD, OUTPUT);
pinMode(ledVM, OUTPUT); 
  
pinMode(Teclad_linhaA, OUTPUT);
pinMode(Teclad_linhaB, OUTPUT);
pinMode(Teclad_linhaC, OUTPUT);
pinMode(Teclad_linhaD, OUTPUT);
  
}


// LAÇO INFINITO PARA RODAR ETERNAMENTE O CÓDIGO PRINCIPAL
void loop() {
  // ********Código da leitura AD*********
  // faz a leitura analogical do pino 0:
  int sensorValue = analogRead(A1);
  // Converte a leitura analógica (que vai de 0 - 1023) para um valor de tensão (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // escreve o valor de tensão via comunicação serial:
  Serial.print("Valor real lido no pino   A1 = ");
  Serial.println(voltage);  
  //float voltage2 = map(sensorValue, 0, 1023, 0.0, 5.0);
  //Serial.print("Valor real convertido c/ map = ");
  //Serial.println(voltage2);
  
  // ********Código do Pisca-Pisca********
  // OPÇÃO 1
  //
  digitalWrite(ledVM, HIGH);   // liga o LED
  digitalWrite(ledVD, LOW);    // desliga o LED
  delay(100);                  // temporiza 1 segundo
  digitalWrite(ledVM, LOW);    // desliga o LED
  digitalWrite(ledVD, HIGH);    // desliga o LED
  delay(100);                  // aguarda mais um segundo
  
  /*
  // OPÇÃO 2
  // liga o LED
  if (conta < 10)   digitalWrite(ledVM, HIGH); 
  // desliga o LED
  if (conta >=10)  digitalWrite(ledVM, LOW);
  // aguarda mais 10 milisegundos
  delay(500); 
  // incrementa a variável conta
  conta++;
  // limita o valor da variável conta em 200 com o teste
  if (conta >= 20) conta =0;
  */
}
