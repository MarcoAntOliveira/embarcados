
unsigned long UltimoMillis;
int i, Tempo100, Tempo500,Tempo1000;


void setup() {
  for (i=0; i<14; i++){
    pinMode(i, OUTPUT);     // configura todos os pinos no loop 
  }
  //pinMode(button, INPUT_PULLUP);
  UltimoMillis = millis();
}

void loop() {

  if ((millis() - UltimoMillis) >= 5) {
    UltimoMillis = millis();
    Coisas_5_mili();
  }
  digitalWrite(0, !digitalRead(0));
  digitalWrite(1, !digitalRead(1));
}


void Coisas_5_mili(){
    digitalWrite(2, !digitalRead(2));
    digitalWrite(3, !digitalRead(3));
    if (Tempo100<20) {
      Tempo100++;
    } else{
      Coisas_100_mili();
      Tempo100=0;
    }
}

void Coisas_100_mili(){
    digitalWrite(4, !digitalRead(4));
    digitalWrite(5, !digitalRead(5));  
    if (Tempo1000<10) {
      Tempo1000++;
    } else{
      Coisas_500_mili();
      Tempo1000=0;
    }
}

void Coisas_500_mili(){
    digitalWrite(6, !digitalRead(6));
    digitalWrite(7, !digitalRead(7));  
    if (Tempo500<5) {
      Tempo500++;
    } else{
      Coisas_1000_mili();
      Tempo500=0;
    }
}

void Coisas_1000_mili(){

}