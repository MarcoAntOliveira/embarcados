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
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // para a placa lcd keypad shield

// Criando um caracter especial via tabela de pontos
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




void setup() {
  
  Serial.begin(9600);
  // grava na memória do display o caracter especial na posição 0
  lcd.createChar(0, CaracEspecial);
  
  lcd.createChar(1, cima);
  lcd.createChar(2, baixo);
  lcd.createChar(3, esquerda);
  lcd.createChar(4, direita);
  
  // configurar número de colunas (16) e linhas (2)
  lcd.begin(16, 2);
  // Como a inicialização posiciona o cursor na primeira linha 
  // e coluna, o comando abaixo apresenta o texto neste local.
  lcd.print("hello, world!");
  delay(1000);
  // define o cursor na primeira coluna (0) e segunda linha (1) 
  lcd.setCursor(15,0); 
  // apresenta o caracter especial por 5 segundos
  lcd.write(byte(0));
  delay(5000);
  
 // define o cursor na primeira coluna (0) e primeira linha (0) 
 lcd.setCursor(0,0);  
 // apresenta texto 
 lcd.print("Arduino e Cia");  
 // define o cursor na primeira coluna (0) e segunda linha (1) 
 lcd.setCursor(0,1);  
 // apresenta texto nesta posição 
 lcd.print("Tecla :");  
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
  
 int botao;  
 botao = analogRead (0);  //Leitura do valor da porta analógica A0
 Serial.println(botao);
  
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
  
}
 