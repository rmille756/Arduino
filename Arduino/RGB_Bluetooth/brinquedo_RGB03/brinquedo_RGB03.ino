#include <SoftwareSerial.h>

bool AZUL = false;
bool VERDE = false;
bool VERMELHO = false;

#define azul 13
#define verde 12
#define vermelho 11

SoftwareSerial bluetooth(4, 5); //TX, RX (Bluetooth)
  
int comando; 

void setup() {
  bluetooth.begin(9600);
  pinMode(azul, OUTPUT);//13
  pinMode(verde, OUTPUT);//12
  pinMode(vermelho, OUTPUT);//11
}

void loop() {
  if (bluetooth.available() > 0) {
    comando = bluetooth.read();
  switch (comando) {
    case 'J':
      acendeAzul;
    break;
      
    case 'H':
      acendeVerde;
    break;
      
    case 'D':
      acendeVermelho;
    break;
      
    case '1':
      inverteAzul;
    break;

    case '2':
      inverteVerde;
    break;
      
    case '3':
      inverteVermelho;
    break;
      
    case 'Z':
      apagaTodos;
    break;

    }
  }
}
