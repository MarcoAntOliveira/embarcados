/*******************************************************************************
* Teclado Matricial 16 Teclas : Controle de Acesso (v1.0)
*
* O codigo ira verificar se a senha digitada esta correta. Caso correta, o 
* acesso e liberado, caso contrario o acesso se mantem travado.
*
* Copyright 2020 RoboCore.
* Escrito por Matheus Cassioli (30/07/2019).
* Atualizado por Giovanni de Castro (22/01/2020).
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version (<https://www.gnu.org/licenses/>).
****************************************************************************/

#include <Password.h> // Biblioteca utilizada para controle de senha
#include <Keypad.h> // Biblioteca para controle do teclado de matrizes

const byte LINHAS = 4; // Linhas do teclado
const byte COLUNAS = 4; // Colunas do teclado

Password senha = Password( "8765" ); // Senha utilizada para liberacao

const int PINO_LED_VERMELHO = 11; // LED vermelho conectado ao pino 11
const int PINO_LED_VERDE = 10; // LED verde conectado ao pino 10

const char TECLAS_MATRIZ[LINHAS][COLUNAS] = { // Matriz de caracteres (mapeamento do teclado)
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

const byte PINOS_LINHAS[LINHAS] = {9, 8, 7, 6}; // Pinos de conexao com as linhas do teclado
const byte PINOS_COLUNAS[COLUNAS] = {5, 4, 3, 2}; // Pinos de conexao com as colunas do teclado

Keypad teclado_personalizado = Keypad(makeKeymap(TECLAS_MATRIZ), PINOS_LINHAS, PINOS_COLUNAS, LINHAS, COLUNAS); // Inicia teclado

void setup() {
  
  Serial.begin(9600); // Inicializa serial monitor
  
  pinMode(PINO_LED_VERMELHO, OUTPUT); // Define pino 10 como saida
  pinMode(PINO_LED_VERDE, OUTPUT); // Define pino 11 como saida

  digitalWrite(PINO_LED_VERDE, LOW); // LED Verde apagado
  digitalWrite(PINO_LED_VERMELHO, LOW); // LED Vermelho apagado
  
}

void loop() {
    
  char leitura_teclas = teclado_personalizado.getKey(); // Atribui a variavel a leitura do teclado
  
  if(leitura_teclas){ // Se alguma tecla foi pressionada

    if(leitura_teclas == 'C'){ // Se a tecla 'C' foi pressionada
      
      if(senha.evaluate()){ // Verifica se a senha digitada esta correta
        
        Serial.println("Senha confirmada!"); // Exibe a mensagem que a senha esta correta
        for(int i = 0; i < 5; i++){ // Pisca o LED 5 vezes rapidamente
          digitalWrite(PINO_LED_VERDE, HIGH);
          delay(50);
          digitalWrite(PINO_LED_VERDE, LOW);
          delay(50);
          
        }
      } else { // Caso a senha esteja incorreta
        
        Serial.println("Senha incorreta!"); // Exibe a mensagem que a senha esta errada
        for(int i = 0; i < 5; i++){ // Pisca o LED 5 vezes rapidamente
          digitalWrite(PINO_LED_VERMELHO, HIGH);
          delay(50);
          digitalWrite(PINO_LED_VERMELHO, LOW);
          delay(50);
          
        }
      }
      
      senha.reset(); // Limpa a variavel senha
      
    } else { // Caso outra tecla tenha sido pressionada
      
      Serial.println(leitura_teclas); // Exibe a tecla pressionada
      senha.append(leitura_teclas); // Salva o valor da tecla pressionada na variavel senha
      
    }
  }

}