#include <SoftwareSerial.h>

bool AZUL = false;
bool VERDE = false;

SoftwareSerial bluetooth(10, 11); //TX, RX (Bluetooth)
  
int comando;    

void setup() {
  bluetooth.begin(9600);
  
  pinMode(13, OUTPUT);
    pinMode(3, OUTPUT);
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
      digitalWrite(3, LOW);
      break;
      
    case '3':
      digitalWrite(13, LOW);
      digitalWrite(3, LOW);
      break;
      
    case 'H':
      digitalWrite(3, HIGH);
      break;
      
    case '2':
    VERDE = !VERDE;
      digitalWrite(3, VERDE);
      break;
 
    }
  }
}
