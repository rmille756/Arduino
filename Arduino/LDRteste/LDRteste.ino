void setup() {
  // put your setup code here, to run once:
pinMode(A0, INPUT_PULLUP);
pinMode(6, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(A0));
  delay(200);
  if(analogRead(A0) <60){
    digitalWrite(6, LOW);
  }
  else{
    digitalWrite(6, HIGH);
  }

}
