#include <SPI.h> 
#include <Ethernet.h> 
 
byte mac[]     = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 
byte ip[]      = { 192, 168, 137, 223}; 
EthernetServer server(80);
EthernetClient client; 

const int pinLedVerde    = 7;
const int pinLedVermelho = 6;
const int pinBotao       = 2;
const int pinIluminacao  = A0;
String readString  = String(30);
int estLedVerde    = 0;
int estLedVermelho = 0;
int iluminacao     = 0; 

void setup(){
  Serial.begin(9600);
  Ethernet.begin(mac, ip); 
  server.begin();
  pinMode(pinLedVerde,    OUTPUT);
  pinMode(pinLedVermelho, OUTPUT);
  pinMode(pinBotao, INPUT_PULLUP);
  digitalWrite(pinLedVerde,    LOW);
  digitalWrite(pinLedVermelho, LOW);
}
  
void loop(){
  iluminacao = analogRead(pinIluminacao);
  client = server.available(); 
  if (client) {
    while (client.connected()){
      if (client.available()){ 
        char c = client.read();
          readString += c;
        if (c == '\n'){
            comandoRecebido();
            page();
            readString="";
            client.stop();
        }
      }
    }
  }
}

void comandoRecebido(){
    if(readString.indexOf("ledVerde=1")>0){
      digitalWrite(pinLedVerde, HIGH);
      estLedVerde = 1;
      Serial.println("Verde Ligado"); 
    }
    if(readString.indexOf("ledVerde=0")>0){
      digitalWrite(pinLedVerde, LOW);
      estLedVerde = 0; 
      Serial.println("Verde Desligado");
    }               
    if(readString.indexOf("ledVermelho=1")>0){
      digitalWrite(pinLedVermelho, HIGH);
      estLedVermelho = 1; 
    }      
    if(readString.indexOf("ledVermelho=0")>0){
      digitalWrite(pinLedVermelho, LOW);
      estLedVermelho = 0; 
    }
}

void page(){
    client.println(F("HTTP/1.1 200 OK"));
    client.println(F("Content-Type: text/html"));
    client.println(F("Connection: close"));  
    client.println(F("Refresh: 1")); 
    client.println();
    client.println(F("<!DOCTYPE HTML>"));
    client.println(F("<html lang=\"pt-br\">"));
    client.println(F("<head>"));
    client.println(F("<meta charset=\"UTF-8\"/>")); 
    client.println(F("<title> Arduino Week </title>")); 
    client.println(F("</head>"));
    client.println(F("<body style=background-color:#FFFFFF>")); 
    client.println(F("<center><font size='50'color='63AEB3'> <h1>II Workshop Arduino Week</font> </center></h1>"));
    client.println(F("<h1><font size='30'color='black'> <center> Sistema de iluminação </center></h1> <hr/>"));
    if (estLedVerde == 1){        
      client.print(F("<center><form method=get name=LED><input type=hidden name=ledVerde value=0 />"));
      client.println(F("<center><font size='5'color='green'>LED Verde: <font color='black' size='5'>LIGADO  <input type=submit  value=APAGAR> </form> </center>"));
    }
    if (estLedVerde == 0){
      client.print(F("<center><form method=get name=LED><input type=hidden name=ledVerde value=1 />"));
      client.println(F("<center><font size='5'color='green'>LED Verde: <font color='black' size='5'>DESLIGADO  <input type=submit value=LIGAR> </form> </center>"));
    }
    if (estLedVermelho == 1){        
      client.print(F("<center><form method=get name=LED><input type=hidden name=ledVermelho value=0 />"));
      client.println(F("<center><font size='5' color='red'>LED Vermelho: <font color='black' size='5'>LIGADO  <input type=submit value=APAGAR> </form> </center>"));
    }
    if (estLedVermelho == 0){
      client.print(F("<center><form method=get name=LED><input type=hidden name=ledVermelho value=1 />"));
      client.println(F("<center><font size='5' color='red'>LED Vermelho: <font color='black' size='5'>DESLIGADO  <input type=submit value=LIGAR> </form> </center>"));
    }
    
    // Informações sobre a iluminação
    client.println("<hr/>");
    client.print(F("<h2><center> Intensidade da iluminação: "));
    client.println(iluminacao);
    client.print(F("</center></h2>"));
    
    // Informações sobre o botão
    client.print(F("<h2><center> Estado Botão: "));
    if(!digitalRead(pinBotao))
      client.print(F("<font color='green'> Ativado"));
    else
      client.print(F("<font color='red'> Desativado"));
    client.print(F("</center></h2>"));
    client.println(F("</body>"));
    client.println(F("</html>"));
}
