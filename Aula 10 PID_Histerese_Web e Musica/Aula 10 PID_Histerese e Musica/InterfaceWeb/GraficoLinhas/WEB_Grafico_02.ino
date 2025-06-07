
#include <EtherCard.h>      // inclui biblioteca para rede ethernet com chip ENC28J60

int LeituraA0[]={0,0,0,0,0,0,0,0,0,0}, LeituraA1[]={0,0,0,0,0,0,0,0,0,0}, LeituraA2[]={0,0,0,0,0,0,0,0,0,0};

// define o endereço MAC
static byte mymac[] = { 0x5A,0x5A,0x5A,0x5A,0x5A,0x5A };

// define um endereço IP estático na sua rede - Observar a faixa de endereços possíveis
static byte myip[] = { 192,168,0,103 };

// Buffer ou memória para armazenar a Web-page
byte Ethernet::buffer[1300];
BufferFiller bfill;

int LedPins[] = { 2,3,4,5,6,7,8,9 };    // definição dos pinos em que estão as saídas
boolean PinStatus[] = { 2,3,4,5,6,7,8,9 }; // os mesmos pinos para definir a situação ou status
int temp, temp1, temp2;

//-------------
// mensagem quando correu tudo bem
const char http_OK[] PROGMEM =
"HTTP/1.0 200 OK\r\n"
"Content-Type: text/html\r\n"
"Pragma: no-cache\r\n\r\n"
"<meta http-equiv='refresh' content='2'/>";    // indica que o navegador deve solicitar atualização a cada 1 segundos
//------------

// Função que define a Web page 
void homePage()
{
  temp = analogRead(A0);  //  leitura analógica do pino A0
  temp1 = analogRead(A1);  //  leitura analógica do pino A1
  temp2 = analogRead(A2);  //  leitura analógica do pino A2
  bfill.emit_p(PSTR("$F"
    "<title>Sist.Embarc.Aplic.I</title>" // título da aba
    "<h1> Ulbra - 2020/2 - Prof. Dr. Dalton Vidor \n\r</h1>"
    "<h1>Leitura analogica de A0 = $D$</h1>"     // escreve texto com o formato h1 (título)
    "<h1>Leitura analogica de A1 = $D$</h1>"     // escreve texto com o formato h1 (título)
    "<h1>Leitura analogica de A2 = $D$</h1>"     // escreve texto com o formato h1 (título)        
    "<head>"
    "<script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script>"
    "<script type=\"text/javascript\">"
      "google.charts.load('current', {'packages':['corechart']});"
      "google.charts.setOnLoadCallback(drawChart);"
      "function drawChart() {"
        "var data = google.visualization.arrayToDataTable(["
          "['Tempo','A0','A1','A2'],"
          "['00',$D$,$D$,$D$],"
          "['01',$D$,$D$,$D$],"
          "['02',$D$,$D$,$D$],"
          "['03',$D$,$D$,$D$],"
          "['04',$D$,$D$,$D$],"
          "['05',$D$,$D$,$D$],"
          "['06',$D$,$D$,$D$],"
          "['07',$D$,$D$,$D$],"
          "['08',$D$,$D$,$D$],"
          "['09',$D$,$D$,$D$],"
        "]);"
        "var options = {"
          "title: 'Historico dos valores lidos',"
          "curveType: 'function',"
          "legend: { position: 'top' }"
        "};"
        "var chart = new google.visualization.LineChart(document.getElementById('curve_chart'));"
        "chart.draw(data, options);"
      "}"
    "</script>"
  "</head>"
  "<body>"
    "<div id=\"curve_chart\" style=\"width: 900px; height: 500px\"></div>"
  "</body>"
"</html>"), 

  http_OK,  // responde que a requisição de página está OK
  temp,     // escreve o valor da variável correspondente a leitura de A0
  temp1,
  temp2,
  LeituraA0[0], LeituraA1[0], LeituraA2[0],
  LeituraA0[1], LeituraA1[1], LeituraA2[1],
  LeituraA0[2], LeituraA1[2], LeituraA2[2],
  LeituraA0[3], LeituraA1[3], LeituraA2[3],
  LeituraA0[4], LeituraA1[4], LeituraA2[4],
  LeituraA0[5], LeituraA1[5], LeituraA2[5],
  LeituraA0[6], LeituraA1[6], LeituraA2[6],
  LeituraA0[7], LeituraA1[7], LeituraA2[7],
  LeituraA0[8], LeituraA1[8], LeituraA2[8],
  LeituraA0[9], LeituraA1[9], LeituraA2[9]
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
  
  word len = ether.packetReceive();   // Verifica pacote Ethernet
  word pos = ether.packetLoop(len);   // Verifica pacote TCP
  
  if (pos) {
    bfill = ether.tcpOffset();
    homePage(); // Return home page
    ether.httpServerReply(bfill.position());    // Envia resposta http

  for(int i = 1; i <= 9; i++)
  {
    LeituraA0[i-1]=LeituraA0[i];
    LeituraA1[i-1]=LeituraA1[i];
    LeituraA2[i-1]=LeituraA2[i];
  } 
    LeituraA0[9]=temp;
    LeituraA1[9]=temp1;
    LeituraA2[9]=temp2;
    
  }
}
