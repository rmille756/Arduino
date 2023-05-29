#include <SoftwareSerial.h>
bool AZUL = false;
bool VERDE = false;
//Create a new software  serial
SoftwareSerial bluetooth(10, 11); //TX, RX (Bluetooth)
  
const int ledPin = 13; // the pin that the LED is attached to
int incomingByte;      // a variable to read incoming serial data into

void setup() {
  //Initialize the software serial
  bluetooth.begin(9600);
  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
    pinMode(3, OUTPUT);
}

void loop() {
  // see if there's incoming serial data:
  if (bluetooth.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = bluetooth.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'J') {
      
      digitalWrite(13, HIGH);
      bluetooth.println("LED: ON");
    }
     if (incomingByte == '1') {
      AZUL = !AZUL;
      digitalWrite(13, AZUL);
      bluetooth.println("LED: ON");
     }
     
    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == 'Z') {
      bluetooth.println("LED: OFF");
      digitalWrite(13, LOW);
      digitalWrite(3, LOW);
    }
        if (incomingByte == '3') {
      bluetooth.println("LED: OFF");
      digitalWrite(13, LOW);
      digitalWrite(3, LOW);
    }
        if (incomingByte == 'H') {
      digitalWrite(3, HIGH);
      bluetooth.println("LED: ON");
  }
      if (incomingByte == '2') {
        VERDE = !VERDE;
        digitalWrite(3, VERDE);
      bluetooth.println("LED: ON");
  }
 }
}
