#include <BluetoothSerial.h>
BluetoothSerial SerialBT; 
bool AZUL = false;
bool VERDE = false;

  
int comando;    

void setup() {
SerialBT.begin("Mille");
  pinMode(12, OUTPUT);
    pinMode(14, OUTPUT);
}

void loop() {
  if (SerialBT.available() > 0) {
    comando = SerialBT.read();
  switch (comando) {
    case 'J':
      digitalWrite(12, HIGH);
      break;
      
    case '1':
      AZUL = !AZUL;
      digitalWrite(12, AZUL);
      break;

    case 'Z':
      digitalWrite(12, LOW);
      digitalWrite(14, LOW);
      break;
      
    case '3':
      digitalWrite(12, LOW);
      digitalWrite(14, LOW);
      break;
      
    case 'H':
      digitalWrite(14, HIGH);
      break;
      
    case '2':
    VERDE = !VERDE;
      digitalWrite(14, VERDE);
      break;
 
    }
 }
}
