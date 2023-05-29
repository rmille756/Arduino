#include <Servo.h>

Servo myservo;
void setup() {
  // put your setup code here, to run once:
pinMode(A0, INPUT_PULLUP);
Serial.begin(9600);
myservo.attach(8);
myservo.write(0);
}

void loop() {
  if(analogRead(A0) < 600){
  delay(75);
  myservo.write(20);
  Serial.println(analogRead(A0));
  delay(200);
  myservo.write(0);
   }
}
