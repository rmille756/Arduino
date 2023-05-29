void setup() {
pinMode(13, INPUT);
Serial.begin(9600);
pinMode(12, OUTPUT);
}

void loop() {
  if(digitalRead(13) == HIGH){
    Serial.println("sinal");
    digitalWrite(12, HIGH);
    delay(200);
    digitalWrite(12, LOW);
  }

}
