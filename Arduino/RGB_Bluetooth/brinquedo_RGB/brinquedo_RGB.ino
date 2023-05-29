#include <SoftwareSerial.h>

bool AZUL = false;
bool VERDE = false;
bool VERMELHO = false;

SoftwareSerial bluetooth(4, 5); //TX, RX (Bluetooth)
  
int comando;    

void setup() {
  bluetooth.begin(9600);
  
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
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
      digitalWrite(11, AZUL);
      break;

    case 'Z':
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);
      break;
      
    case '3':
    VERMELHO = !VERMELHO;
      digitalWrite(13, VERMELHO);
      break;
      
    case 'H':
      digitalWrite(11, HIGH);
      break;
      
      
    case '2':
    VERDE = !VERDE;
      digitalWrite(12, VERDE);
      break;

    case 'D':
      digitalWrite(12, HIGH);
      break;

    }
  }
}
