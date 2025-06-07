
int ValorRef, ValorSaida;
double Referencia, Realimentacao, Erro,  SetPoint=80;


#define Ref       A0    // Leitura analógica da referência no pino A0
#define LeSaida   A1    // Leitura analógica da saída realimentada no pino A1
#define Atua1      3     // Vai atuar no PWM do pino 3


#define Faixa1H     300
#define Faixa1L     -300


void setup() {
  
  Serial.begin(9600);

  pinMode(Ref, INPUT);
  pinMode(LeSaida, INPUT);
  pinMode(Atua1, OUTPUT);


}


void loop() {

  ValorRef = analogRead(Ref);
  ValorSaida = analogRead(LeSaida);

  Referencia = map(ValorRef, 0, 1023, 0, 10000);
  Realimentacao = map(ValorSaida, 0, 1023, 0, 10000);

 
      // Implementação 
      
      Erro = Referencia - Realimentacao;
      // Erro = SetPoint - Realimentação;

      //Erro positivo e saída abaixo do valor desejado
      if (Erro>Faixa1H) {digitalWrite(Atua1, HIGH);}
      
      //Erro negativo e saída acima do valor desejado
      if (Erro<Faixa1L) {digitalWrite(Atua1, LOW);}   
  
}
