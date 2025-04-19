// ==============================
//        VARIÁVEIS GLOBAIS
// ==============================

// Armazena o tempo da última execução do ciclo de 5 ms
unsigned long UltimoMillis;

// Índice usado no loop de configuração
int i;

// Contadores para temporizações escalonadas
int Contador_100ms = 0;   // Dispara ação a cada 100 ms
int Contador_500ms = 0;   // Dispara a cada 500 ms
int Contador_1000ms = 0;  // Dispara a cada 1000 ms
int Contador_2000ms = 0;  // Dispara a cada 2000 ms
int Contador_4000ms = 0;  // Dispara a cada 4000 ms

// ==============================
//           CONFIGURAÇÃO
// ==============================

void setup() {
  // Configura os pinos digitais de 0 a 13 como saída
  for (i = 0; i < 14; i++) {
    pinMode(i, OUTPUT);
  }

  // Inicializa o tempo de referência
  UltimoMillis = millis();
}

// ==============================
//             LOOP
// ==============================

void loop() {
  // Executa a cada 5 milissegundos
  if ((millis() - UltimoMillis) >= 5) {
    UltimoMillis = millis();     // Atualiza o tempo de referência
    Coisas_5_mili();             // Executa tarefas periódicas
  }

  // Alterna rapidamente os pinos 0 e 1 (frequência alta)
  digitalWrite(0, !digitalRead(0));
  digitalWrite(1, !digitalRead(1));
}

// ==============================
//       TAREFAS A CADA 5 MS
// ==============================

void Coisas_5_mili() {
  // Inverte os estados dos pinos 2 e 3
  digitalWrite(2, !digitalRead(2));
  digitalWrite(3, !digitalRead(3));

  // A cada 100 ms (20 * 5 ms)
  if (++Contador_100ms >= 20) {
    Contador_100ms = 0;
    Coisas_100_mili();
  }
}

// ==============================
//      TAREFAS A CADA 100 MS
// ==============================

void Coisas_100_mili() {
  // Inverte os pinos 4 e 5
  digitalWrite(4, !digitalRead(4));
  digitalWrite(5, !digitalRead(5));

  // A cada 500 ms (5 * 100 ms)
  if (++Contador_500ms >= 5) {
    Contador_500ms = 0;
    Coisas_500_mili();
  }
}

// ==============================
//      TAREFAS A CADA 500 MS
// ==============================

void Coisas_500_mili() {
  // Inverte os pinos 6 e 7
  digitalWrite(6, !digitalRead(6));
  digitalWrite(7, !digitalRead(7));

  // A cada 1000 ms (2 * 500 ms)
  if (++Contador_1000ms >= 2) {
    Contador_1000ms = 0;
    Coisas_1000_mili();
  }
}

// ==============================
//     TAREFAS A CADA 1000 MS
// ==============================

void Coisas_1000_mili() {
  // Inverte os pinos 8 e 9
  digitalWrite(8, !digitalRead(8));
  digitalWrite(9, !digitalRead(9));

  // A cada 2000 ms (2 * 1000 ms)
  if (++Contador_2000ms >= 2) {
    Contador_2000ms = 0;
    Coisas_2000_mili();
  }
}

// ==============================
//     TAREFAS A CADA 2000 MS
// ==============================

void Coisas_2000_mili() {
  // Inverte os pinos 10 e 11
  digitalWrite(10, !digitalRead(10));
  digitalWrite(11, !digitalRead(11));

  // A cada 4000 ms (2 * 2000 ms)
  if (++Contador_4000ms >= 2) {
    Contador_4000ms = 0;
    Coisas_4000_mili();
  }
}

// ==============================
//     TAREFAS A CADA 4000 MS
// ==============================

void Coisas_4000_mili() {
  // Inverte os pinos 12 e 13
  digitalWrite(12, !digitalRead(12));
  digitalWrite(13, !digitalRead(13));
}
