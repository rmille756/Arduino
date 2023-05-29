#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "LUNA_2G";
const char* password = "lucianoeronaldo";

WebServer client(80);

int led = 14;
int contadorA = 0;
int contadorB = 0;
int comando;
String site;
void handleRoot() {
  digitalWrite(2, HIGH);
  site =  "<html>\n";
  site += "<head><title>Contador de Pontos</title></head>\n";
  site += "<meta http-equiv=\"refresh\" content=\"3\">\n";
  site += "<style> html {color:#eee; font-family: Helvetica; font-weight: bold;";
  site += "display: inline-block; margin: 0px auto; text-align: center;";
  site += "background-color: #0a0a0a}";
  site += "body {padding-top: 60px}\n";
  site += "button { border: 3px solid; border-radius: 5px;";
  site += "padding: 14px 35px; font-size: 25px; font-weight: bold;";
  site += "margin: 2px; transition-duration: 0.4s; cursor: pointer;}</style>\n";
  site += "<font size=+2><h1>Contador de Pontos<br/><br/></h1>\n";
  site += "<p><font color=\"#0f0\"><h2>[Time 1]: ";
  site += contadorA;
  site += "</font><font color=\"#f00\"> &nbsp;&nbsp;&nbsp;&nbsp;[Time 2]: ";
  site += contadorB;
  site += "</font></h2></p></font>\n";
  site += "</body>\n";
  site += "</html>";
  client.send(200, "text/html", site);
  site = "";
  delay(50);
  digitalWrite(2, LOW);
}

void setup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");}
  Serial.println(WiFi.localIP());
  client.on("/", handleRoot);
  client.on("/inline", []() {
    client.send(200, "text/plain", "this works as well");
  });
  client.begin();

  Serial.begin(115200);
  ledcSetup(0, 5000, 8);
  ledcAttachPin(led, 0);
}

void loop() {
  client.handleClient();
  
  ledcWrite(0, 10);
  if(Serial.available()>0){
    comando = Serial.read();
    if(comando == 'A'){
      contadorA = Serial.parseInt();
      Serial.print(contadorA);
      Serial.print(" ");
      Serial.println(contadorB);
    }
    else if(comando == 'B'){
      contadorB = Serial.parseInt();
      Serial.print(contadorA);
      Serial.print(" ");
      Serial.println(contadorB);
    }

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
  }
}
