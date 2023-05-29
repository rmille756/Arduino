#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10, 11); //TX, RX (Bluetooth)
  
int incomingByte;      // a variable to read incoming serial data into

void setup() {
  bluetooth.begin(9600);
  
  pinMode(13, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  if (bluetooth.available() > 0) {
    incomingByte = bluetooth.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'J') {
      digitalWrite(13, HIGH);
      bluetooth.println("LED: ON");
    }
     if (incomingByte == '1') {
      digitalWrite(13, HIGH);
     }
     
    if (incomingByte == 'Z') {
      digitalWrite(13, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
    }
        if (incomingByte == '3') {
      digitalWrite(4, HIGH);
    }
        if (incomingByte == 'H') {
      digitalWrite(3, HIGH);
  }
      if (incomingByte == '2') {
      digitalWrite(3, HIGH);
      bluetooth.println("LED: ON");
  }
    if (incomingByte == 'Y') {
      digitalWrite(4, HIGH);
      bluetooth.println("LED: ON");
    }
  }
}
