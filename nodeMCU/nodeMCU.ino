#include <ESP8266WiFi.h>

const char* ssid = "MEO-DCBBCD";
const char* password = "5F57F6E934";

#define led 16
#define D1 5

int firstrun = 0;
int buttonpressed = 5;

WiFiServer server(80);

void setup() {
  pinMode(D1, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  digitalWrite(D1, LOW);
  Serial.begin(115200);
  delay(10);

//Conectar ao WIFI
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

//Esperar pela connecção
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }

//Confirmação WiFi
  Serial.println("");
  Serial.println("Wifi connected!!");

//Web Server
  server.begin();
  Serial.println("Web Server Started");

//Mostrar IP adress
  Serial.print("Connect to the server here:  ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println();
  Serial.println();

}

void loop() {


//Verificar se alguem esta ligado ao servidor
  WiFiClient client = server.available();
  if (!client){
    return;
  }


//ler qual o botao pressionado na pagina
  String request = client.readStringUntil('\r');

  if(request.indexOf("/ligarpin") != -1){
    digitalWrite(D1, HIGH);
    digitalWrite(led, LOW);
    buttonpressed = 1;
  }
  if(request.indexOf("/desligarpin") != -1){
    digitalWrite(D1, LOW);
    digitalWrite(led, HIGH);
    buttonpressed = 2;
  }

//pagina WEB
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");

  client.println("<html>");
  
  client.println("<style>");
  //client.println("body {background-color: #003399;}");
  client.println("</style>");
  
  if(firstrun == 0){
    client.println("Carrega num Botao:");
    firstrun=1;
    }
  else{
    client.println("O Pin D1 esta: ");
  }
  
  if(buttonpressed == 1){
    client.println("LIGADO!! :)");
    }
  if(buttonpressed == 2){
    client.println("DESLIGADO!! :(");
  }

  client.println("<br><br>");
  client.println("<a href=\"/ligarpin\"\"><button>Ligar</button></a>");
  client.println("<a href=\"/desligarpin\"\"><button>Desligar</button></a>");
  client.println("</html>");
  delay(10);
  


  
}

