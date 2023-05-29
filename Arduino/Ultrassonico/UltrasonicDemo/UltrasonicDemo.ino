
#include <Ultrasonic.h>

#define TRIGGER_PIN  4
#define ECHO_PIN     5

Ultrasonic ultrasonico(TRIGGER_PIN, ECHO_PIN);

void setup()
  {
  Serial.begin(9600);
  }

void loop()
  {
  float cmMsec, inMsec;
  long microsec = ultrasonico.timing();

  cmMsec = ultrasonico.convert(microsec, Ultrasonic::CM);


  Serial.print("MS:");
  Serial.print(microsec);
  Serial.print(" CM:");
  Serial.println(cmMsec);
  delay(500);
  }
