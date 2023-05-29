int led = 14;
int contadorA = 0;
int contadorB = 0;
int comando;
void setup() {
  Serial.begin(115200);
  ledcSetup(0, 5000, 8);
  ledcAttachPin(led, 0);
}

void loop() {
  ledcWrite(0, 10);
  if(Serial.available()>0){
    comando = Serial.read();
    if(comando == 'A'){
      contadorA = Serial.parseInt();
      Serial.print(contadorA);
      Serial.print(" ");
      Serial.println(contadorB);
    }
    else if(comando == 'B'){
      contadorB = Serial.parseInt();
      Serial.print(contadorA);
      Serial.print(" ");
      Serial.println(contadorB);
    }r

    if(contadorA == contadorB){
      ledcWrite(0, 0);
      ledcDetachPin(led);
      led = 14;
  ledcAttachPin(led, 0);}
      
    if(contadorA > contadorB){
      ledcWrite(0, 0);
      ledcDetachPin(led);
      led = 12;
  ledcAttachPin(led, 0);}
      
    if(contadorA < contadorB){
      ledcWrite(0, 0);
      ledcDetachPin(led);
      led = 13;
  ledcAttachPin(led, 0);}
  }
}
