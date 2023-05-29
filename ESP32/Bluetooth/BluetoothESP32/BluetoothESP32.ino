#include "BluetoothSerial.h"
int leitura;
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("FV");
  pinMode(13, OUTPUT);
  
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    leitura = SerialBT.read();
  if(leitura == 'G'){
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
  }
 }
}
