#include <SoftwareSerial.h>
SoftwareSerial bluetooth(4, 5); //TX, RX (Bluetooth)
  
int comando;    
int BLUE = 0;

void setup() {
  bluetooth.begin(9600);
  pinMode(12, OUTPUT);
}

void loop() {
  if (bluetooth.available() > 0) {
    comando = bluetooth.read();
  switch (comando) {
    case 'Z':
      digitalWrite(13, BLUE);
      BLUE = BLUE;
      break;

    case 'D':
      digitalWrite(13, BLUE);
      BLUE = BLUE + 1;
      break;
      
    case 'H':
      digitalWrite(13, BLUE);
      BLUE--;
      break;

 
    }
 }
}
