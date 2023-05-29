#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* ssid = "COMPUTADOR19";
const char* password = "12345678";

WebServer client(80);

const int led = 13;
int verde = 0;

void handleRoot() {
  digitalWrite(led, HIGH);
  client.send(200, "text/plain", "acabei de conseguir criar um website com o esp32");
  delay(50);
  digitalWrite(led, LOW);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += client.uri();
  message += "\nMethod: ";
  message += (client.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += client.args();
  message += "\n";
  for (uint8_t i = 0; i < client.args(); i++) {
    message += " " + client.argName(i) + ": " + client.arg(i) + "\n";
  }
  client.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  client.on("/", handleRoot);

  client.on("/inline", []() {
    client.send(200, "text/plain", "this works as well");
  });

  client.onNotFound(handleNotFound);

  client.begin();
  Serial.println("HTTP client started");
}

void loop(void) {
  client.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}
