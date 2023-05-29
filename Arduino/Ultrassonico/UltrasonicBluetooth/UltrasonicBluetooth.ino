#include <Ultrasonic.h>
#include <SoftwareSerial.h>

#define TRIGGER_PIN  2
#define ECHO_PIN     3

Ultrasonic ultrasonico(TRIGGER_PIN, ECHO_PIN);

SoftwareSerial bluetooth(4, 5); //TX, RX (Bluetooth)

void setup()
  {
  Serial.begin(9600);
  bluetooth.begin(9600);
  }

void loop()
  {
  float cmMsec, inMsec;
  long microsec = ultrasonico.timing();

  cmMsec = ultrasonico.convert(microsec, Ultrasonic::CM);

  bluetooth.print(" CM:");
  bluetooth.println(cmMsec);
  delay(1000);
  }
