#include <WiFi.h>

// coloque aqui o nome e senha da rede WiFi
const char* ssid = "COMPUTADOR11";
const char* password = "12345678";

char c;
// Set web server port number to 80
WiFiServer server(80);
// Variable to store the HTTP request
String header;

int led = 14;
int contadorA = 0;
int contadorB = 0;
int comando;
String site;
// Variable to store the HTTP requestString header;
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
void setup (){
  Serial.begin(115200);
  ledcSetup(0, 5000, 8);
  ledcAttachPin(led, 0);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
    if(contadorA == contadorB){
      ledcWrite(0, 0);
      ledcDetachPin(led);
      led = 14;
  ledcAttachPin(led, 0);}
      
    if(contadorA > contadorB){
      ledcWrite(0, 0);
      ledcDetachPin(led);
      led = 12;
  ledcAttachPin(led, 0);}
      
    if(contadorA < contadorB){
      ledcWrite(0, 0);
      ledcDetachPin(led);
      led = 13;
  ledcAttachPin(led, 0);}
  
  ledcWrite(0, 10);
  if(Serial.available()>0){
    comando = Serial.read();
    if(comando == 'A'){
      contadorA = Serial.parseInt();
      Serial.println(placar());
    }
    else if(comando == 'B'){
      contadorB = Serial.parseInt();
      Serial.println(placar());
    }
  }
  
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("Novo acesso.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        c = client.read();              // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            client.print("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println("");
            if (header.indexOf("GET /A") >= 0) {
              contadorA++;
            Serial.println(placar());
            }
            else if (header.indexOf("GET /B") >= 0) {
              contadorB++;
            Serial.println(placar());
            }
            else if (header.indexOf("GET /0") >= 0) {
              contadorA = 0;
              contadorB = 0;
            Serial.println(placar());
            }
            client.print(site1());
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        }
      }
    }
    header = "";
    // Close the connection
    client.stop();
  }
}


String site1(){
  site = "<!DOCTYPE html><html>\n";
  site += "<head><title>Contador de Pontos</title></head>\n";
  site += "<style> html {color:#eee; font-family: Helvetica; font-weight: bold;";
  site += "display: inline-block; margin: 0px auto; text-align: center;";
  site += "background-color: #0a0a0a}";
  site += "body {padding-top: 60px}\n";
  site += ".button { border: 3px solid; border-radius: 5px;";
  site += "padding: 14px 35px; font-size: 25px; font-weight: bold;";
  site += "margin: 2px; transition-duration: 0.4s; cursor: pointer;}\n";
  site += ".button0{ background-color: #222; color: #aaa;}</style>\n";
  site += "<font size=+2><h1>Contador de Pontos<br/><br/></h1>\n";
  site += "<p><font color=\"#0f0\"><h2>[Time 1]: ";
  site += contadorA;
  site += "</font><font color=\"#f00\"> &nbsp;&nbsp;&nbsp;&nbsp;[Time 2]: ";
  site += contadorB;
  site += "</font></h2></p></font>\n";
  site += "<p><a href=\"/A\"><button class=\"button\">PONTO</button></a>";//BOTOES
  site += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
  site += "<a href=\"/B\"><button class=\"button\">PONTO</button></a></p>\n";
  site += "<a href=\"/0\"><button class=\"button button0\">ZERAR</button></a>\n";
  site += "</body>\n";
  site += "</html>";
  site += "\n";
  return site;
}
String placar(){
  String pontuacao = "";
  pontuacao += contadorA;
  pontuacao += " ";
  pontuacao += contadorB;
  return pontuacao;
}