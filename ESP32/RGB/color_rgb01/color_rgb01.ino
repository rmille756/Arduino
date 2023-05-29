void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
  color(0, 0, 0);
}

void loop() {
  color(1, 0, 0);
  delay(500);
  color(0, 1, 0);
  delay(500);
  color(0, 0, 1);
  delay(500);
  color(1, 1, 1);
  delay(500);
  color(0, 0, 0);
  delay(500);
}
void color(int R, int G, int B) {
  digitalWrite(13, R);
  digitalWrite(12, G);
  digitalWrite(14, B);
}
