#define trigPin 9
#define echoPin 10

 

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

 

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW); // Limpa o pino Trig
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // Envia pulso de 10 microssegundos
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); // Limpa o pino Trig
  duration = pulseIn(echoPin, HIGH); // Lê o tempo do pulso
  distance = duration / 58.2; // Calcula a distância em centímetros
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(500); // Aguarda meio segundo
}