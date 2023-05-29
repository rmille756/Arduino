const int redPin = 3;
int red;
const int greenPin = 5;
int green;
const int bluePin = 6;
int blue;
void setup() {
  Serial.begin(9600);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  color(red, green, blue);
  
  if(Serial.available() > 0){ 
    switch(Serial.read()){
      case 'R':
       red = Serial.parseInt();
       constrain(red, 0, 255);
       Serial.println(red, HEX);
      break;
      case 'G':
       green = Serial.parseInt();
       constrain(green, 0, 255);
       Serial.println(green, HEX);
      break;
      case 'B':
       blue = Serial.parseInt();
       constrain(blue, 0, 255);
       Serial.println(blue, HEX);
      break;
    } 
  }
}
void color (unsigned char red, unsigned char green, unsigned char blue) // the color generating function 
{ 
analogWrite(redPin, red); 
analogWrite(greenPin, green); 
analogWrite(bluePin, blue); 
}
