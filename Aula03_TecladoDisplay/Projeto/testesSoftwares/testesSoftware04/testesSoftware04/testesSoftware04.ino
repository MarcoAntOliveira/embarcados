/*
  Uso de display e da biblioteca LiquidCrystal
  
  Demonstra o uso de display 16 colunas 2 linhas ou similares que
  utilizam o controlador de display compatível com Hitachi HD44780 
  Este tipo de controlador permite que os dados sejam enviados por 
  4 pinos apenas. O pino rs é responsável por definir palavras de
  controle ou de dados, o pino rw define leitura ou escrita, o pino
  en habilita ou não a troca de informações no display e o restante
  dos pinos são pinos de dados ou alimentação.

  O circuito:
 * Pino RS do LCD vai para pino 12 arduino
 * Pino Enable do LCD vai para pino 11 arduino
 * Pino D4 do LCD vai para pino 5 arduino
 * Pino D5 do LCD vai para pino 4 arduino
 * Pino D6 do LCD vai para pino 3 arduino
 * Pino D7 do LCD vai para pino 2 arduino
 * Pino RW do LCD vai para 0V ou terra (sempre escrita neste caso)
 * Pino VSS do LCD vai para 0V ou terra
 * Pino VCC do LCD vai para 5V
 * 10K resistor define contraste do display
 * Ligar 5V no backlight se houver

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// incluir a biblioteca para display operar
#include <LiquidCrystal.h>
// Definir pinos ligados ao display conforme LiquidCrystal(rs, enable, d4, d5, d6, d7) 
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
// Criando um caracter especial via tabela de pontos em uma variável
byte CaracEspecial[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};
byte cima[8] = {
  B00100,
  B01110,
  B11111,
  B10101,
  B00100,
  B00100,
  B00100,
};
byte baixo[8] = {
  B00100,
  B00100,
  B00100,
  B10101,
  B11111,
  B01110,
  B00100,
};
byte direita[8] = {
  B00000,
  B01100,
  B00110,
  B11111,
  B00110,
  B01100,
  B00000,
};
byte esquerda[8] = {
  B00000,
  B00110,
  B01100,
  B11111,
  B01100,
  B00110,
  B00000,
};


// incluindo a biblioteca de leitura do teclado matricial
#include <Keypad.h> //Biblioteca para uso de teclados matriciais 
const byte numLinhas = 4; //Quantidade de linhas do teclado
const byte numColunas = 4; //Quantidade de colunas do teclado
//Matriz de caracteres referente aos botões do teclado
char teclasMatriz[numLinhas][numColunas] = {
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', '0', '*', '+'},
  {'#', '$', '%', '@'}
};
// Conexões das linhas do teclado
byte pinosLinhas[numLinhas] = {6, 7, 8, 9}; //Pinos das linhas
byte pinosColunas[numColunas] = {2, 3, 4, 5}; //Pinos das Colunas
//Cria um objeto do tipo Keypad
Keypad meuteclado = Keypad(makeKeymap(teclasMatriz), pinosLinhas, pinosColunas, numLinhas, numColunas);


  
// INICIA COM AS DEFINIÇÕES DE PINOS E DE VARIÁVEIS
// LEDs conectados aos pinos de saídas digitais 12 e 13
int ledVD = 12;
int ledVM = 13; 
// Acionamento do display e de teclado conectados aos pinos de saídas digitais 11 e 10
int EnDisplay = 11;
int EnTeclado = 10; 
// variável - contador para definir tarefas
int conta = 0;	



// *******************  SEMPRE TEM UM SETUP PARA DEFINIR HARDWARE E PINOS
void setup() {

// configura pinos de TX e RX como comunicação serial com taxa de 9600bps 
Serial.begin(9600);

// configura pino digital como saída dos leds
pinMode(ledVD, OUTPUT);
pinMode(ledVM, OUTPUT); 
// configura pino digital como saída de acionamento do display ou teclado
pinMode(EnDisplay, OUTPUT);
pinMode(EnTeclado, OUTPUT); 
  
  // habilita acionamento do display
  digitalWrite(EnDisplay, HIGH);  
  delay(200);  

  
  // configurar número de colunas (16) e linhas (2)
  lcd.begin(16, 2);
  // Como a inicialização posiciona o cursor na primeira linha 
  // e coluna, o comando abaixo apresenta o texto neste local.
  lcd.print("Top. Especiais   ");
  lcd.print("\n");
  lcd.print("Sistemas Embarcados");
  delay(1000);

  // grava na memória do display o caracter especial na posição 0
  lcd.createChar(0, CaracEspecial);
  lcd.createChar(1, cima);
  lcd.createChar(2, baixo);
  lcd.createChar(3, esquerda);
  lcd.createChar(4, direita);
  // define o cursor na primeira coluna (0) e segunda linha (1) 
  lcd.setCursor(15,0); 
  // apresenta o caracter especial por 2 segundos
  lcd.write(byte(0));
  delay(2000);

 // define o cursor na primeira coluna (0) e primeira linha (0) 
 lcd.setCursor(0,0);  
 // apresenta texto 
 lcd.print("UFSC-CTJ      ");
 // define o cursor na primeira coluna (0) e segunda linha (1) 
 lcd.setCursor(0,1);  
 // apresenta texto nesta posição 
 lcd.print("Tecla:");  
}


// ****************  Void Loop é o que roda ciclicamente para sempre até desligar o kit
void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
  
 int botao;  
 botao = analogRead (A1);  //Leitura do valor da porta analógica A0
 Serial.println(botao);
  

  // habilita acionamento do display
  digitalWrite(EnDisplay, HIGH);  
  delay(2);    
  lcd.setCursor(8,1);  
 if (botao < 100) {  
  lcd.print ("Direita ");
  lcd.setCursor(15,0); 
  lcd.write(byte(4));
 }  
 else if (botao < 200) {  
  lcd.print ("Cima    ");
  lcd.setCursor(15,0);
  lcd.write(byte(1));
 }  
 else if (botao < 400){  
  lcd.print ("Baixo   ");
  lcd.setCursor(15,0); 
  lcd.write(byte(2));
 }  
 else if (botao < 600){  
  lcd.print ("Esquerda");
  lcd.setCursor(15,0);
  lcd.write(byte(3));
 }  
 else if (botao < 800){  
  lcd.print ("Selecao ");  
 }   
  // deshabilita acionamento do display
  digitalWrite(EnDisplay, LOW);  
  delay(2);    

  // habilita acionamento do display
  digitalWrite(EnTeclado, HIGH);  
  delay(2);   
  char pressionado = meuteclado.getKey(); ///Verifica se alguma tecla foi pressionada
  if (pressionado) { //Se alguma tecla foi pressionada
    Serial.print("Botão pressionado: "); //Imprime mensagem no monitor serial
    Serial.println(pressionado); //Imprime tecla pressionada
  }
  // deshabilita acionamento do display
  digitalWrite(EnTeclado, LOW);  
  delay(2);

}
 
