

int brilho = 1;
void setup() {
pinMode(13, INPUT);
pinMode(12, INPUT);
Serial.begin(9600);
pinMode(3, OUTPUT);
}

void loop() {
  analogWrite(3, brilho);
  if(digitalRead(12) == HIGH){
    brilho = brilho + 20;
    delay(200);
  }
  if(digitalRead(13) == HIGH){
    brilho = brilho - 20;
    delay(200);
  }

}
