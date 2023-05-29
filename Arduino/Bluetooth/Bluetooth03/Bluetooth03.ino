#include <SoftwareSerial.h>

//Create a new software  serial
SoftwareSerial bluetooth(10, 11); //TX, RX (Bluetooth)
  
int texto;      // a variable to read incoming serial data into

void setup() {
  //Initialize the software serial
  bluetooth.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // see if there's incoming serial data:
  if (bluetooth.available() > 0) {
    // read the oldest byte in the serial buffer:
    texto = bluetooth.read();

      Serial.println(texto);
 
  }
}
