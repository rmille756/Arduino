#include <WiFi.h>

// coloque aqui o nome e senha da rede WiFi
const char* ssid = "********";
const char* password = "********";

char c;
// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

const int redPin = 13;
String red = "off";//DECLARANDO AS VARIÁVEIS DA COR VERMELHA

const int greenPin = 12;
String green = "off";//DECLARANDO AS VARIÁVEIS DA COR VERDE

const int bluePin = 14;
String blue = "off";//DECLARANDO AS VARIÁVEIS DA COR AZUL

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // define os pinos do led rgb como saída
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  // desliga todos os pinos
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  digitalWrite(redPin, LOW);

  // conecta a esp32 a rede WiFi
  Serial.print("Se conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // imprime no monitor serial o IP e inicia a página web
  Serial.println("");
  Serial.println("Wifi conectado.");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
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
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.print("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println("Refresh: 3");
            client.println();
            
            // função que liga/desliga os pinos do led rgb
            if (header.indexOf("GET /g/s") >= 0) {
              Serial.println("Verde ligado");
              green = "on";
              digitalWrite(greenPin, HIGH);
            } else if (header.indexOf("GET /g/n") >= 0) {
              Serial.println("Verde desligado");
              green = "off";
              digitalWrite(greenPin, LOW);
            } else if (header.indexOf("GET /b/s") >= 0) {
              Serial.println("Azul ligado");
              blue = "on";
              digitalWrite(bluePin, HIGH);
            } else if (header.indexOf("GET /b/n") >= 0) {
              Serial.println("Azul delsigado");
              blue = "off";
              digitalWrite(bluePin, LOW);
            } else if (header.indexOf("GET /r/s") >= 0) {
              Serial.println("Vermelho ligado");
              red = "on";
              digitalWrite(redPin, HIGH);
            } else if (header.indexOf("GET /r/n") >= 0) {
              Serial.println("Vermelho desligado");
              red = "off";
              digitalWrite(redPin, LOW);
            }
            
            // Display the HTML web page
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
    Serial.println("Cliente desconectado.");
    Serial.println("");
  }
}
String site1(){
  String cod = "<!DOCTYPE html><html>\n";
  cod += "<head><meta charset=\"UTF-8\">\n";
  cod += "<title>RGB.com</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";//define o titulo da aba
  cod += "<link rel=\"icon\" href=\"data:,\">\n";
  cod += "<style>html {color:#eee; font-family: Helvetica; font-weight: bold; display: inline-block; margin: 0px auto; text-align: center; background-color: #050505}\n";
  cod += ".gradient { background-color: black; background-image: linear-gradient( to bottom, #f00 33%, #0f0 55%, #00f 76%);";
  cod += "background-clip: text; -webkit-background-clip: text; -webkit-text-fill-color: transparent;}\n";//css para definir o gradiente do titulo da pagina
  
  cod += ".button { border: 3px solid; border-radius: 5px; padding: 14px 35px; font-size: 25px; font-weight: bold; margin: 2px; transition-duration: 0.4s; cursor: pointer;}\n";
  //parte do css que define o estilo dos botões
  cod += ".buttonr { background-color: #200; border-color: #b00; color: #f00;}\n";//css do botao vermelho
  cod += ".buttonr:hover { background-color: #f00; border-color: #900; color: #111;}\n";
  //hover: botão quando o mouse passa por cima
  cod += ".buttong { background-color: #020; border-color: #0b0; color: #0f0;}\n";//css do botao verde
  cod += ".buttong:hover { background-color: #0f0; border-color: #090; color: #111;}\n";

  cod += ".buttonb { background-color: #002; border-color: #00b; color: #00f;}\n";//css do botao azul
  cod += ".buttonb:hover { background-color: #00f; border-color: #009; color: #111;}\n";
  
  cod += ".button2 {background-color: #222; border-color: #bbb; color: #aaa; padding: 14px 30px; font-weight: bold;}\n";
  cod += ".button2:hover { background-color: #aaa; border-color: #555; color: #111;}\n";//css do botao de desligar(todos)
  //css definindo os queadros coloridos em volta dos títulos das cores
  cod += "#vermelho{display:block; color: #f00; border: 3px solid #f00; padding: 8px 12px; width: fit-content; margin: 0 auto;}\n";
  cod += "#vermelho:hover{color: #000; border-color: #900; background-color: #f00; cursor: not-allowed;}\n";

  cod += "#verde{display:block; color: #0f0; border: 3px solid #0f0; padding: 8px 12px;width: fit-content; margin: 0 auto;}\n";
  cod += "#verde:hover{color: #000; border-color: #090; background-color: #0f0; cursor: not-allowed;}\n";

  cod += "#azul{display:block; color: #00f; border: 3px solid #00f; padding: 8px 12px;width: fit-content; margin: 0 auto;}\n";
  cod += "#azul:hover{color: #000; border-color: #009; background-color: #00f; cursor: not-allowed;}\n";
  cod += "</style></head>\n";//
  cod += "<body><h1 class=\"gradient\"><b>RGB.com</b></h1>\n";
  cod += "<p id=\"vermelho\">VERMELHO - " + red + "</p>\n";
       if (red=="off") {
  cod += "<p><a href=\"/r/s\"><button class=\"button buttonr\">ON</button></a></p>\n";
   } 
      else {
  cod += "<p><a href=\"/r/n\"><button class=\"button button2\">OFF</button></a></p>\n";
    }
  cod += "<p id=\"verde\">VERDE - " + green + "</p>\n";
       if (green=="off") {
  cod += "<p><a href=\"/g/s\"><button class=\"button buttong\">ON</button></a></p>\n";
   }
       else {
  cod += "<p><a href=\"/g/n\"><button class=\"button button2\">OFF</button></a></p>\n";
 }
  cod += "<p id=\"azul\">AZUL - " + blue + "</p>\n";
       if (blue=="off") {
  cod += "<p><a href=\"/b/s\"><button class=\"button buttonb\">ON</button></a></p>\n";
    }  
       else {
  cod += "<p><a href=\"/b/n\"><button class=\"button button2\">OFF</button></a></p>\n";
   }
  cod += "</body></html>\n";
  cod += "\n";
  return cod;
}
