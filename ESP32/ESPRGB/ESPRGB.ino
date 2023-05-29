#include <BluetoothSerial.h>
BluetoothSerial SerialBT; 


#define Red     1
#define Green   2
#define Blue    3

#define TIMER  8

#define FREQ     12000


const int redPin = 13;
int red;//DECLARANDO AS VARIÁVEIS DA COR VERMELHA
bool Vermeio = false;

const int greenPin = 12;
int green;//DECLARANDO AS VARIÁVEIS DA COR VERDE
bool Vredi = false;

const int bluePin = 14;
int blue;//DECLARANDO AS VARIÁVEIS DA COR AZUL
bool Azu = false;

void setup() {

  ledcAttachPin(redPin, Red);
  ledcAttachPin(greenPin, Green);
  ledcAttachPin(bluePin, Blue);
  
  ledcSetup(Red, FREQ, TIMER);
  ledcSetup(Green, FREQ, TIMER);
  ledcSetup(Blue, FREQ, TIMER);
  
Serial.begin(9600);         
SerialBT.begin("Mille");
  
  ledcWrite(Red, 255); 
  ledcWrite(Green, 255); 
  ledcWrite(Blue, 255); 
  delay(100);
  ledcWrite(Red, 0); 
  ledcWrite(Green, 0); 
  ledcWrite(Blue, 0); 
       } 
void loop() { 
  
  if(SerialBT.available() > 0){ 
    switch(SerialBT.read()){
      case 'R':
       red = SerialBT.parseInt();
       constrain(red, 0, 255);
  color(red, green, blue);
       Serial.println(red, HEX);
      break;
      
      case 'G':
       green = SerialBT.parseInt();
       constrain(green, 0, 255);
  color(red, green, blue);
       Serial.println(green, HEX);
      break;
      
      case 'B':
       blue = SerialBT.parseInt();
       constrain(blue, 0, 255);
  color(red, green, blue);
       Serial.println(blue, HEX);
      break;
      
      case 'Q':
       Vermeio = !Vermeio;
  boolcolor(Vermeio, Vredi, Azu);
      break;
      
      case 'J':
       Vredi = !Vredi;
  boolcolor(Vermeio, Vredi, Azu);
      break;
      
      case 'K':
       Azu = !Azu;
  boolcolor(Vermeio, Vredi, Azu);
      break;
      
      case 'A':
       Vermeio = false;
       Vredi = false;
       Azu = false;
  boolcolor(Vermeio, Vredi, Azu);
      break;
    } 
  }
        }
        
void color (unsigned char red, unsigned char green, unsigned char blue){ 
  
ledcWrite(Red, red); 
ledcWrite(Green, green); 
ledcWrite(Blue, blue); 
}
void boolcolor (unsigned char verm, unsigned char verd, unsigned char azul){ 
  if(verm == true){
ledcWrite(Red, 255); 
  }
  else if(verm == false){
ledcWrite(Red, 0);
  }
  if(verd == true){
ledcWrite(Green, 255); 
  }
  else if(verd == false){
ledcWrite(Green, 0);
  }
  if(azul == true){
ledcWrite(Blue, 255); 
  }
  else if(azul == false){
ledcWrite(Blue, 0);
  }
}
