#include <SoftwareSerial.h>

SoftwareSerial modulo(2, 3);

void setup() {
pinMode(13, INPUT);
modulo.begin(9600);
pinMode(12, OUTPUT);
Serial.begin(9600);
}

void loop() {
  if (modulo.available()) {
    Serial.write(modulo.read());
  }
  if (Serial.available()) {
    modulo.write(Serial.read());
  }
  if(digitalRead(13) == HIGH){
    modulo.println("a isa é linda");
    Serial.println("a isa é linda");
    digitalWrite(12, HIGH);
    delay(500);
    digitalWrite(12, LOW);
  }
}
