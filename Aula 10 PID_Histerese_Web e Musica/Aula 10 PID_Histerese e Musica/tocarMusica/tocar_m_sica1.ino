/*     Prof. Dr. Dalton Vidor

 Utilizando o exemplo disponível em
 http://www.arduino.cc/en/Tutorial/Tone   */

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

// Internacional
/*
sol sol fa# sol FA MI DO# la RE
RE RE RE DO# DO si
la# si MI RE si la sol
sol sol sol la sol la si si
si DO si DO RE RE
la la sol# la RE 
*/
int Inter[] = {
  NOTE_G6, NOTE_G6, NOTE_FS6, NOTE_G6, NOTE_F7, NOTE_E7,
  NOTE_CS7, NOTE_A6, NOTE_D7, 0,
  NOTE_D7, NOTE_D7, NOTE_D7, NOTE_CS7, NOTE_C7, NOTE_B6
  
};

// duração das notas: 4 = 1/4 do tempo da nota, 8 = 1/8 do tempo da nota, etc.:
int DuracoesInter[] = {
  4, 4, 4, 4, 4, 4, 4, 4, 2, 4,
  4, 4, 2, 4, 4, 2
  
};



// Gremio
/*
DO LA SOL FA SOL LA SOL DO
DO LA SOL FA SOL LA SOL
LA SI DO SI DO #DO DO #DO MI RE
LA SI DO RE DO SOL SI LA MI
*/

int Gremio[] = {
  NOTE_C6, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_G5, NOTE_A5,
  NOTE_G5, NOTE_C5, 0,
  NOTE_C6, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_G5, NOTE_A5,
  NOTE_G5, 
  
};

// duração das notas: 4 = 1/4 do tempo da nota, 8 = 1/8 do tempo da nota, etc.:
int DuracoesGremio[] = {
  2, 4, 4, 2, 4, 4, 2, 2, 1, 
  2, 4, 4, 2, 4, 4, 2
};


//definição dos pinos e nomes associados às teclas
#define Tecla_Inter   7
#define Tecla_Gremio  3

void setup() {
  // inicailizar os pinos digitais das teclas com PullUp
  pinMode(Tecla_Inter , INPUT_PULLUP);
  pinMode(Tecla_Gremio, INPUT_PULLUP);
}

void loop() {

    if (!digitalRead(Tecla_Inter)){                           // testa se a tecla foi apertada
      for (int EstaNota = 0; EstaNota < 16; EstaNota++) {     // EstaNota indica o índice da notas da pequena melodia
      int TempoNota = 1000 / DuracoesInter[EstaNota];         // nota com 1/4 do tempo note = 1000 / 4, nota com 1/8 do tempo  note = 1000/8, etc.
      tone(8, Inter[EstaNota], TempoNota);                    // produz o tom da nota com o tempo determinado no pino definido
      int PausaEntreNotas = TempoNota * 1.30;                 // define o delay das pausas entre notas
      delay(PausaEntreNotas);                                 // gasta o tempo de pausa entre notas
      noTone(8);                                              // desliga a saída de áudio para trocar de nota ou terminar
      }
    }

    if (!digitalRead(Tecla_Gremio)){                          // testa se a tecla foi apertada
      for (int EstaNota = 0; EstaNota < 16; EstaNota++) {     // EstaNota indica o índice da notas da pequena melodia
      int TempoNota = 1000 / DuracoesGremio[EstaNota];        // nota com 1/4 do tempo note = 1000 / 4, nota com 1/8 do tempo  note = 1000/8, etc.
      tone(8, Gremio[EstaNota], TempoNota);                   // produz o tom da nota com o tempo determinado no pino definido
      int PausaEntreNotas = TempoNota * 1.30;                 // define o delay das pausas entre notas
      delay(PausaEntreNotas);                                 // gasta o tempo de pausa entre notas
      noTone(8);                                              // desliga a saída de áudio para trocar de nota ou terminar
      }
    }
}
