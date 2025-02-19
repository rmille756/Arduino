int n1;
int n2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    Serial.print("Digite o primeiro numero para soma: ");
    n1 = Serial.read();
    Serial.print("Digite o segundo numero para soma: ");
    n2 = Serial.read();
    Serial.println(soma(n1,n2));

  }
}
int soma(int v1, int v2){
  int res;
  res = v1+v2;
  return res;
}
