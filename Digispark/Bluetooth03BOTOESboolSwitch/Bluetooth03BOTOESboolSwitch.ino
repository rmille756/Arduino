#include <SoftSerial.h>

bool AZUL = false;
bool VERDE = false;

SoftSerial bluetooth(2, 3); //TX, RX (Bluetooth)
  
int comando;    

void setup() {
  bluetooth.begin(9600);
  
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
}

void loop() {
  if (bluetooth.available() > 0) {
    comando = bluetooth.read();
  switch (comando) {
    case 'Q':
      AZUL = !AZUL;
      digitalWrite(0, AZUL);
      break;

    case 'A':
      digitalWrite(0, LOW);
      digitalWrite(1, LOW);
      break;
      
    case 'J':
    VERDE = !VERDE;
      digitalWrite(1, VERDE);
      break;
 
    }
 }
}
