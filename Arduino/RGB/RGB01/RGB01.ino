const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;
int red;
int green;
int blue;
void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

}

void loop() {
   color(100, 0, 0);
   delay(1000);
   color(0, 100, 0);
   delay(1000);
   color(0, 0, 100);
   delay(1000);
   red = 100;
   green = 100;
   blue = 100;
   color(red, green, blue);
   delay(2000);
}
void color (unsigned char red, unsigned char green, unsigned char blue) // the color generating function 
{ 
analogWrite(redPin, red); 
analogWrite(greenPin, green); 
analogWrite(bluePin, blue); 
}
