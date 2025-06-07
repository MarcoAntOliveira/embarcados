
#include <EtherCard.h>      // inclui biblioteca para rede ethernet com chip ENC28J60

// define o endereço MAC
static byte mymac[] = { 0x5A,0x5A,0x5A,0x5A,0x5A,0x5A };

// define um endereço IP estático na sua rede - Observar a faixa de endereços possíveis
static byte myip[] = { 192,168,0,103 };

// Buffer ou memória para armazenar a Web-page
byte Ethernet::buffer[1300];
BufferFiller bfill;

int LedPins[] = { 2,3,4,5,6,7,8,9 };    // definição dos pinos em que estão as saídas

boolean PinStatus[] = { 2,3,4,5,6,7,8,9 }; // os mesmos pinos para definir a situação ou status

//-------------
// mensagem quando correu tudo bem
const char http_OK[] PROGMEM =
"HTTP/1.0 200 OK\r\n"
"Content-Type: text/html\r\n"
"Pragma: no-cache\r\n\r\n"
"<meta http-equiv='refresh' content='5'/>";    // indica que o navegador deve solicitar atualização a cada 1 segundos
//------------

// Função que define a Web page 
void homePage()
{
  int temp = analogRead(A0);  //  leitura analógica do pino A0
  int temp1 = analogRead(A1);  //  leitura analógica do pino A1
  int temp2 = analogRead(A2);  //  leitura analógica do pino A2
  bfill.emit_p(PSTR("$F"
    "<title>Sist.Embarc.Aplic.I</title>" // título da aba
    "<h1> Ulbra - 2020/2 - Prof. Dr. Dalton Vidor \n\r</h1>"
    "<h1>Leitura analogica de A0 = $D$</h1>"     // escreve texto com o formato h1 (título)
    "<h1>Leitura analogica de A1 = $D$</h1>"     // escreve texto com o formato h1 (título)
    "<h1>Leitura analogica de A2 = $D$</h1>"     // escreve texto com o formato h1 (título)        
    "<script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script>"
    "<script type=\"text/javascript\">"
      "google.charts.load('current', {'packages':['gauge']});"
      "google.charts.setOnLoadCallback(drawChart);"
      "function drawChart() {"
        "var data = google.visualization.arrayToDataTable(["
          "['Label', 'Value'],"
          "['Vin', $D],"
          "['Iin', $D],"
          "['Vcc', $D],"
          "['Vdd', $D],"
          "]);"
        "var options = {"
          "width: 750, height: 350,"
          "redFrom: 900, redTo: 1024,"
          "yellowFrom:500, yellowTo: 900,"
          "minorTicks: 20,"
          "max: 1024,"
          "min: 0,"
        "};"
        "var chart = new google.visualization.Gauge(document.getElementById('chart_div'));"
        "chart.draw(data, options);"
      "}"
    "</script>"
  "</head>"
  "<body>"
    "<div id=\"chart_div\" style=\"width: 1500px; height: 1500px;\"></div>"
  "</body>"), 

  http_OK,  // responde que a requisição de página está OK
  temp,     // escreve o valor da variável correspondente a leitura de A0
  temp1,
  temp2,
  analogRead(A0),
  analogRead(A1),
  analogRead(A2),
  temp/2
  );
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
    homePage(); // Return home page
    ether.httpServerReply(bfill.position());    // send http response
  }
}
