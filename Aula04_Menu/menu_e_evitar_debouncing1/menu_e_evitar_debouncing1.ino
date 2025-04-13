
// incluir a biblioteca para display operar
#include <LiquidCrystal.h>
//definição dos pinos e nomes associados às teclas
#define botao_p_baixo  		10
#define botao_p_cima		9
#define botao_seleciona		8

//definição dos pinos e nomes associados aos leds
#define L_AM  	A5
#define L_AZ  	A4
#define L_VM  	A3
#define L_VD  	A2

int menu = 1;       		//Variável para selecção da página.
int LedVerdePisca = 0;     	//Variável para liberar o led verde para piscar


// Definir pinos ligados ao display conforme LiquidCrystal(rs, enable, d4, d5, d6, d7) 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // para a placa lcd keypad shield

void setup() {
  // define a velocidade da comunicação serial
  Serial.begin(9600);
  // configurar o display com colunas (16) e linhas (2)
  lcd.begin(16, 2);
  // inicailizar os pinos digitais das teclas com PullUp
  pinMode(botao_p_baixo, INPUT_PULLUP);
  pinMode(botao_p_cima, INPUT_PULLUP);
  pinMode(botao_seleciona, INPUT_PULLUP);
  // inicailizar os pinos dos LEDs com função digital
  pinMode(L_AM, OUTPUT);
  pinMode(L_AZ, OUTPUT);
  pinMode(L_VM, OUTPUT);
  pinMode(L_VD, OUTPUT);
  // nos pinos do display a biblioteca se encarrega de acertar
  AtualizaMenu();			// chama função que atualiza o Menu
}

void loop() {
  
  
  if (!digitalRead(botao_p_baixo)){ // testa se os botões vão para nível zero!!!
    menu++;					// incrementa tela de menu
    AtualizaMenu();			// chama função que atualiza o Menu
    delay(100);				// aguarda um tempo para soltar a tecla
    while (!digitalRead(botao_p_baixo)); // espera soltar a tecla
  }
  
  if (!digitalRead(botao_p_cima)){ // testa se os botões vão para nível zero!!!
    menu--;					// decrementa tela de menu
    if(menu>5) menu=5;
    AtualizaMenu();			// chama função que atualiza o Menu
    delay(100);				// aguarda um tempo para soltar a tecla
    while(!digitalRead(botao_p_cima)); // espera soltar a tecla
  }
  
  if (!digitalRead(botao_seleciona)){ // testa se os botões vão para nível zero!!!
    ExecutaAcao();			// chama função que executa ação
    AtualizaMenu();			// chama função que atualiza o Menu
    delay(100);				// aguarda um tempo para soltar a tecla
    while (!digitalRead(botao_seleciona)); // espera soltar a tecla
  }
  
  if(LedVerdePisca){
    digitalWrite(L_VD, !digitalRead(L_VD));
    delay(100);
  } 
}


  
  void AtualizaMenu() {
  switch (menu) {
    case 0:						// se a seleção é menor do que a primeira tela
      menu = 1;					// então seleciona a primeira tela
      break;
    case 1:
      lcd.clear();
      lcd.print("1.LED AMARELO");
      lcd.setCursor(0, 1);
      lcd.print("Selec->muda");
      break;
    case 2:
      lcd.clear();
      lcd.print("2.LED AZUL");
      lcd.setCursor(0, 1);
      lcd.print("Selec->submenu");
      break;
    case 3:
      lcd.clear();
      lcd.print("3.LED VERMELHO");
      lcd.setCursor(0, 1);
      lcd.print("Selec->submenu");
      break;
    case 4:
      lcd.clear();
      lcd.print("4.LED VERDE");
      lcd.setCursor(0, 1);
      lcd.print("Selec->muda");
      break;
    case 5:
      menu = 4;
      break;
  }
}




void ExecutaAcao() {
  switch (menu) {
    case 1:
      acao1();
      break;
    case 2:
      acao2();
      break;
    case 3:
      acao3();
      break;
    case 4:
      acao4();
      break;
    case 21:
      acao21();
      break;
    case 31:
      acao31();
      break;    
  }
}



void acao1() {
  lcd.clear();
  lcd.print("Executando1");
  digitalWrite(L_AM, !digitalRead(L_AM));
  delay(1500);
}
void acao2() {
  lcd.clear();
  lcd.print("Executando2");
  menu=21;			// seleciona submenu
  lcd.setCursor(0, 1);
  lcd.print("Vai p submenu21");
  delay(1500);
}
void acao3() {
  lcd.clear();
  lcd.print("Executando3");
  menu=31;			// seleciona submenu
  lcd.setCursor(0, 1);
  lcd.print("Vai p submenu31");  
  delay(1500);
}
void acao4() {
  lcd.clear();
  lcd.print("Executando4");
  if(LedVerdePisca){
    LedVerdePisca=0;
  } else{
    LedVerdePisca=1;
  }
  delay(1500);
}
void acao21() {
  lcd.clear();
  lcd.print("Executando21");
  digitalWrite(L_AZ, !digitalRead(L_AZ));
  delay(1500);
}
void acao31() {
  lcd.clear();
  lcd.print("Executando31");
  digitalWrite(L_VM, !digitalRead(L_VM));
  delay(1500);
} 