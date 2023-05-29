#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "LUNA_2G";
const char* password = "lucianoeronaldo";

char c;

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state

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
  // Initialize the output variables as outputs
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  // Set outputs to LOW
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  digitalWrite(redPin, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        c = client.read();             // read a byte, then
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
            client.println("Refresh: 1");
            client.println();
            
            // turns the GPIOs on and off
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
            
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta charset=\"UTF-8\"><title>ronaldo.com</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html {color:#eee; font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; background-color: #333}");
            client.println("body{padding-top: 120px;};");
            client.println(".button {background-color: #4CAF50; border: none; color: white; padding: 16px 40px;border-radius: 5px; ");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}");
            client.println("#verde{display:block; color: #0f0; border: 3px solid #0f0; padding: 8px 12px;width: fit-content; margin: 0 auto;}");
            client.println("#vermelho{display:block; color: #f00; border: 3px solid #f00; padding: 8px 12px;width: fit-content; margin: 0 auto;}");
            client.println("#azul{display:block; color: #00f; border: 3px solid #00f; padding: 8px 12px;width: fit-content; margin: 0 auto;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Ronald e joão.com</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p id=\"verde\">VERDE - " + green + "</p>");
            if (green=="off") {
              client.println("<p><a href=\"/g/s\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/g/n\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<p id=\"azul\">AZUL - " + blue + "</p>");     
            if (blue=="off") {
              client.println("<p><a href=\"/b/s\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/b/n\"><button class=\"button button2\">OFF</button></a></p>");
            }
            
            // Display current state, and ON/OFF buttons for GPIO 28  
            client.println("<p id=\"vermelho\">VERMELHO - " + red + "</p>");   
            if (red=="off") {
              client.println("<p><a href=\"/r/s\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/r/n\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("<h2><input type=\"color\"></h2>");
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } 
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
