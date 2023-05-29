#include <Ethernet.h>
// Complete com as informacoes da sua rede
byte mac[] =
{
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 137, 223);
int leituraSensor = 0;
int saidaSensor = 7;
//Inicializa o webserver com a porta 80 - porta padrão do HTTP
EthernetServer server(80);
void setup()
{
  Serial.begin(9600);
  //Pino ler o sinal no coletor do fototransistor do TCRT5000
  pinMode(saidaSensor, INPUT);
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}
void loop()
{
  leituraSensor = digitalRead(saidaSensor);
  //Fica escutando requisições de novos clientes
  EthernetClient client = server.available();
  if (client)
  {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close"); // the connection will be closed after completion of the response
          client.println("Refresh: 5"); // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // Apresenta na tela a leitura do sensor
          client.print("<font color=#0000FF ><b><u>");
          client.print("Leitura do sensor online");
          client.print("</u></b></font>");
          client.println("<br />");
          client.println("<br />");
          if (leituraSensor == 0)
            client.println("Nenhum Objeto identificado!");
          else
            client.println("Nenhum bjeto identificado!");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
