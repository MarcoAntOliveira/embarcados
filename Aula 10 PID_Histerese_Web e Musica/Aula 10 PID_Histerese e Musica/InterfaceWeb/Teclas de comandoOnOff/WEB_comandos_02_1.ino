
#include <EtherCard.h>      // inclui biblioteca para rede ethernet com chip ENC28J60

// define o endereço MAC
static byte mymac[] = { 0x5A,0x5A,0x5A,0x5A,0x5A,0x5A };

// define um endereço IP estático na sua rede - Observar a faixa de endereços possíveis
static byte myip[] = { 150,162,216,157 };

// Buffer ou memória para armazenar a Web-page
byte Ethernet::buffer[1200];
BufferFiller bfill;

int LedPins[] = { 2,3,4,5,6,7,8,9 };    // definição dos pinos em que estão as saídas

boolean PinStatus[] = { 2,3,4,5,6,7,8,9 }; // os mesmos pinos para definir a situação ou status

//-------------
// mensagem quando correu tudo bem
const char http_OK[] PROGMEM =
"HTTP/1.0 200 OK\r\n"
"Content-Type: text/html\r\n"
"Pragma: no-cache\r\n\r\n"
"<meta http-equiv='refresh' content='1'/>";    // indica que o navegador deve solicitar atualização a cada 1 segundos

// mensagem quando deu erro
const char http_Found[] PROGMEM =
"HTTP/1.0 302 Found\r\n"
"Location: /\r\n\r\n"
"<meta http-equiv='refresh' content='1'/>";    // indica que o navegador deve solicitar atualização a cada 1 segundos

// mensagem quando não foi autorizado
const char http_Unauthorized[] PROGMEM =
"HTTP/1.0 401 Unauthorized\r\n"
"Content-Type: text/html\r\n\r\n"
"<h1>401 Unauthorized</h1>"
"<meta http-equiv='refresh' content='1'/>";    // indica que o navegador deve solicitar atualização a cada 1 segundos

//------------

// Função que define a Web page 
void homePage()
{
  int temp = analogRead(A0);  //  leitura analógica do pino A0
  float tempbar=temp/1023;
  bfill.emit_p(PSTR("$F"
    "<title>Topicos em Sist.Embarc.I</title>" // título da aba
    "<h1> UFSC - 2025/1 - Prof. Dr. Dalton Vidor \n\r</h1>"
    "<h1>Leitura analogica de A0 = $D$ (entre 0 e 1023)</h1>"     // escreve texto com o formato h1 (título)
    //"<label for=\"test\">Valor lido: </label>"
    //"<meter id=\"test\" value= \"$D$\" ></meter><br>"
    "<label for=\"file\">Valor lido:   </label>"
    "<progress id=\"file\" value =\"$D$\" max=\"1023\"></progress>"
    "<h1>Saida 1: <a href=\"?ArduinoPIN1=$F\">$F</a><br />"
    "Saida 2: <a href=\"?ArduinoPIN2=$F\">$F</a><br />"  
    "Saida 3: <a href=\"?ArduinoPIN3=$F\">$F</a><br />"
    "Saida 4: <a href=\"?ArduinoPIN4=$F\">$F</a><br />"
    "Saida 5: <a href=\"?ArduinoPIN5=$F\">$F</a><br />"
    "Saida 6: <a href=\"?ArduinoPIN6=$F\">$F</a><br />"
    "Saida 7: <a href=\"?ArduinoPIN7=$F\">$F</a><br />"   
    "Saida 8: <a href=\"?ArduinoPIN8=$F\">$F</a></h1>"), 

  http_OK,  // responde que a requisição de página está OK
  temp, temp,     // escreve o valor da variável correspondente a leitura de A0
  PinStatus[0]?PSTR("off"):PSTR("on"),
  PinStatus[0]?PSTR("<font color=\"green\"><b>ON</b></font>"):PSTR("<font color=\"red\">OFF</font>"), 
  PinStatus[1]?PSTR("off"):PSTR("on"),
  PinStatus[1]?PSTR("<font color=\"green\"><b>ON</b></font>"):PSTR("<font color=\"red\">OFF</font>"),
  PinStatus[2]?PSTR("off"):PSTR("on"),
  PinStatus[2]?PSTR("<font color=\"green\"><b>ON</b></font>"):PSTR("<font color=\"red\">OFF</font>"),
  PinStatus[3]?PSTR("off"):PSTR("on"),
  PinStatus[3]?PSTR("<font color=\"green\"><b>ON</b></font>"):PSTR("<font color=\"red\">OFF</font>"),
  PinStatus[4]?PSTR("off"):PSTR("on"),
  PinStatus[4]?PSTR("<font color=\"green\"><b>ON</b></font>"):PSTR("<font color=\"red\">OFF</font>"),
  PinStatus[5]?PSTR("off"):PSTR("on"),
  PinStatus[5]?PSTR("<font color=\"green\"><b>ON</b></font>"):PSTR("<font color=\"red\">OFF</font>"),
  PinStatus[6]?PSTR("off"):PSTR("on"),
  PinStatus[6]?PSTR("<font color=\"green\"><b>ON</b></font>"):PSTR("<font color=\"red\">OFF</font>"), 
  PinStatus[7]?PSTR("off"):PSTR("on"),
  PinStatus[7]?PSTR("<font color=\"green\"><b>ON</b></font>"):PSTR("<font color=\"red\">OFF</font>"));
}

//------------------------

void setup()
{
  Serial.begin(9600);
  
  if (ether.begin(sizeof Ethernet::buffer, mymac, 10) == 0);

// descomentar se usar DHCP e comentar se usar IP estático
  //if (!ether.dhcpSetup()); // descomentar se usar DHCP
  //ether.printIp("O Routeador com DHCP designou o IP: ", ether.myip);

// descomentar se usar IP estático e comentar se usar DHCP
  ether.staticSetup(myip);
  ether.printIp("IP estatico definido: ", ether.myip);

  for(int i = 0; i <= 7; i++)
  {
    pinMode(LedPins[i],OUTPUT);   // define como pinos de saída
    PinStatus[i]=false;           // coloca todos os pinos em zero ou nível baixo
  }  
}

// --------------------------------------

void loop()
{
  delay(1);
  
  word len = ether.packetReceive();   // check for Ethernet packet
  word pos = ether.packetLoop(len);   // check for TCP packet
  
  if (pos) {
    bfill = ether.tcpOffset();
    char *data = (char *) Ethernet::buffer + pos;
    if (strncmp("GET /", data, 5) != 0) {
      bfill.emit_p(http_Unauthorized);
    }
    else {
      data += 5;
      if (data[0] == ' ') {       
        homePage(); // Return home page
        
        for (int i = 0; i <= 7; i++)
        {
          digitalWrite(LedPins[i],PinStatus[i]);   
        }
      }


      // observação -> "16" = número de caracteres na palavra "?ArduinoPINx=on "
      else if (strncmp("?ArduinoPIN1=on ", data, 16) == 0) {
        PinStatus[0] = true;        
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN2=on ", data, 16) == 0) {
        PinStatus[1] = true;        
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN3=on ", data, 16) == 0) {
        PinStatus[2] = true;        
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN4=on ", data, 16) == 0) {
        PinStatus[3] = true;        
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN5=on ", data, 16) == 0) {
        PinStatus[4] = true;        
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN6=on ", data, 16) == 0) {
        PinStatus[5] = true;        
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN7=on ", data, 16) == 0) {
        PinStatus[6] = true;        
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN8=on ", data, 16) == 0) {
        PinStatus[7] = true;        
        bfill.emit_p(http_Found);
      }

      // observação -> "17" = número de caracteres na palavra "?ArduinoPINx=off "  

      else if (strncmp("?ArduinoPIN1=off ", data, 17) == 0) {
        PinStatus[0] = false;        
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN2=off ", data, 17) == 0) {
        PinStatus[1] = false;        
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN3=off ", data, 17) == 0) {
        PinStatus[2] = false;        
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN4=off ", data, 17) == 0) {
        PinStatus[3] = false;        
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN5=off ", data, 17) == 0) {
        PinStatus[4] = false;        
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN6=off ", data, 17) == 0) {
        PinStatus[5] = false;        
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN7=off ", data, 17) == 0) {
        PinStatus[6] = false;        
        bfill.emit_p(http_Found);
      }
      else if (strncmp("?ArduinoPIN8=off ", data, 17) == 0) {
        PinStatus[7] = false;        
        bfill.emit_p(http_Found);
      }

      //---------------------------

      else {
        // Page not found
        bfill.emit_p(http_Unauthorized);
      }
    }
    ether.httpServerReply(bfill.position());    // send http response
  }
}
