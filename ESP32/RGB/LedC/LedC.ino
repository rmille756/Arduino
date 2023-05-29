const int ledPin = 12;

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
 
void setup(){
  ledcSetup(ledChannel, freq, resolution);
  
  ledcAttachPin(ledPin, ledChannel);
}
 
void loop(){
    ledcWrite(ledPin, 15);
    delay(500);
    ledcWrite(ledPin, 50);
    delay(500);
  
}
