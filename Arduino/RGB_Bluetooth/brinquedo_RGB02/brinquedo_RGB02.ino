#include <SoftwareSerial.h>

bool AZUL = false;
bool VERDE = false;
bool VERMELHO = false;

#define azul 13
#define verde 12
#define vermelho 11

SoftwareSerial bluetooth(4, 5); //TX, RX (Bluetooth)
  
int comando;    
int BLUE;

void setup() {
  bluetooth.begin(9600);
  pinMode(azul, OUTPUT);//13
  pinMode(verde, OUTPUT);//12
  pinMode(12, OUTPUT);

  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
}

void loop() {
  if (bluetooth.available() > 0) {
    comando = bluetooth.read();
  switch (comando) {
    case 'J':
      digitalWrite(13, HIGH);
      break;
      
    case '1':
      AZUL = !AZUL;
      digitalWrite(13, AZUL);
      break;

    case 'Z':
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(3, LOW);
      break;

    case 'D':
      digitalWrite(12, HIGH);
      break;
      
    case '3':
    VERMELHO = !VERMELHO;
      digitalWrite(12, VERMELHO);
      break;
      
    case 'H':
      digitalWrite(verde, HIGH);
      break;
      
    case '2':
    VERDE = !VERDE;
      digitalWrite(3, VERDE);
      break;

    case 'B':
    BLUE = (bluetooth.read());
    digitalWrite(8, BLUE);
 
    }
  }
}
