#include <SoftSerial.h>

/*
 VERMELHO NO PINO 3
 VERDE NO PINO 5
 AZUL NO PINO 6
 RX BLUETOOTH NO PINO 10
 TX BLUETOOTH NO PINO 11
 */
SoftSerial modulo(2,4);


const int redPin = 0;
int red;//DECLARANDO AS VARIÁVEIS DA COR VERMELHA
bool Vermeio = false;

const int greenPin = 1;
int green;//DECLARANDO AS VARIÁVEIS DA COR VERDE
bool Vredi = false;

const int bluePin = 3;
int blue;//DECLARANDO AS VARIÁVEIS DA COR AZUL
bool Azu = false;

void setup() {
  Serial.begin(9600);
  modulo.begin(9600);//INICIALIZA AS PORTAS SERIAIS
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);//DECLARA A SAÍDA DOS PINOS
  pinMode(bluePin, OUTPUT);
}

void loop() {
  
  if(modulo.available() > 0){ 
    switch(modulo.read()){
      case 'R':
       red = modulo.parseInt();
       constrain(red, 0, 255);
  color(red, green, blue);
       Serial.println(red, HEX);
      break;
      
      case 'G':
       green = modulo.parseInt();
       constrain(green, 0, 255);
  color(red, green, blue);
       Serial.println(green, HEX);
      break;
      
      case 'B':
       blue = modulo.parseInt();
       constrain(blue, 0, 255);
  color(red, green, blue);
       Serial.println(blue, HEX);
      break;
      
      case 'Q':
       Vermeio = !Vermeio;
  boolcolor(Vermeio, Vredi, Azu);
      break;
      
      case 'J':
       Vredi = !Vredi;
  boolcolor(Vermeio, Vredi, Azu);
      break;
      
      case 'K':
       Azu = !Azu;
  boolcolor(Vermeio, Vredi, Azu);
      break;
      
      case 'A':
       Vermeio = false;
       Vredi = false;
       Azu = false;
  boolcolor(Vermeio, Vredi, Azu);
      break;
    } 
  }
}
void color (unsigned char red, unsigned char green, unsigned char blue){ 
analogWrite(redPin, red); 
analogWrite(greenPin, green); 
analogWrite(bluePin, blue); 
}
void boolcolor (unsigned char verm, unsigned char verd, unsigned char azul){ 
digitalWrite(redPin, verm); 
digitalWrite(greenPin, verd); 
digitalWrite(bluePin, azul); 
}
