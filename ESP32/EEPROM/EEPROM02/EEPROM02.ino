#include <EEPROM.h>
#define EEPROM_SIZE 64
int ledStado = 0;
int dado;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(14, OUTPUT);
  Serial.begin(9600);
  EEPROM.begin(EEPROM_SIZE);
  ledStado = EEPROM.read(0);
  digitalWrite(2, ledStado);
  Serial.print("estado:");
  Serial.println(ledStado);
  delay(10);
}

void loop() {
  if(Serial.available() > 0){
    dado = Serial.read();
  if(dado == 'b'){
    ledStado = Serial.parseInt();
    Serial.print("estado:");
    Serial.println(ledStado);
    EEPROM.write(0, ledStado);
    analogWrite(2, ledStado);
  }
  else if(dado == 'h'){
    digitalWrite(2, LOW);
    ledStado = 0;
    Serial.print("estado:");
    Serial.println(ledStado);
    EEPROM.write(0, ledStado);
  digitalWrite(2, ledStado);
  }
  }
  EEPROM.commit();
}
