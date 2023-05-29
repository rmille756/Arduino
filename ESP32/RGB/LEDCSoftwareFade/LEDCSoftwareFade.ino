
#define Red     0
#define Green   1
#define Blue    2

#define TIMER  13

#define FREQ     5000

#define R            13
#define G            12
#define B            14

void setup() {
  ledcSetup(Red, FREQ, TIMER);
  ledcSetup(Green, FREQ, TIMER);
  ledcSetup(Blue, FREQ, TIMER);
  
  ledcAttachPin(R, Red);
  ledcAttachPin(G, Green);
  ledcAttachPin(B, Blue);
}

void loop() {
  ledcWrite(Red, 150);
  delay(500);
  ledcWrite(Red, 0);
  ledcWrite(Green, 150);
  delay(500);
  ledcWrite(Green, 0);
  ledcWrite(Blue, 150);
  delay(500);
  ledcWrite(2, 0);
}
