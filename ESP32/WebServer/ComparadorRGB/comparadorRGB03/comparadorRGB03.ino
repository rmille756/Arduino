#include <WiFi.h>
#include <WebServer.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>


const char* ssid = "LUNA_2G";
const char* password = "lucianoeronaldo";

WebServer client(80);

int led = 14;
int contadorA = 0;
int contadorB = 0;
int comando;

String site;

const char* PARAM_INPUT = "value";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void handleRoot() {
  digitalWrite(2, HIGH);
const char index_html[] PROGMEM = R"rawliteral(
  <html>
  <head><title>Contador de Pontos</title></head>
  <meta http-equiv=\"refresh\" content=\"3\">
  <style> html {color:#eee; font-family: Helvetica; font-weight: bold;
  display: inline-block; margin: 0px auto; text-align: center;
  background-color: #0a0a0a}
  body {padding-top: 60px}
  button { border: 3px solid; border-radius: 5px;
  padding: 14px 35px; font-size: 25px; font-weight: bold;
  margin: 2px; transition-duration: 0.4s; cursor: pointer;}</style>
  <font size=+2><h1>Contador de Pontos<br/><br/></h1>
  <p><font color=\"#0f0\"><h2>[Time 1]: 
  contadorA;
  </font><font color=\"#f00\"> &nbsp;&nbsp;&nbsp;&nbsp;[Time 2]: 
  contadorB;
  </font></h2></p></font>
  </body>
  </html>  
)rawliteral";
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
