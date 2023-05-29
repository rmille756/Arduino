#include <EEPROM.h>
#define EEPROM_SIZE 1
int ledStado = 0;
int dado;

void setup() {
  pinMode(2, OUTPUT);
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
  if(dado == 'g'){
    digitalWrite(2, HIGH);
    ledStado = 1;
    Serial.print("estado:");
    Serial.println(ledStado);
  }
  else if(dado == 'h'){
    digitalWrite(2, LOW);
    ledStado = 0;
    Serial.print("estado:");
    Serial.println(ledStado);
  }
  }
  EEPROM.write(0, ledStado);
  EEPROM.commit();
}
