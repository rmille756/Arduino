//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

uint8_t heart[8] = {0x0,0x0,0xa,0x1f,0xe,0x4,0x0};
byte batlow[8] = {
B01110,
B11011,
B10001,
B10001,
B10001,
B10001,
B10001,
B11111
};
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();
  lcd.createChar(1, heart);
  lcd.createChar(2, batlow);
  lcd.setBacklight(HIGH);
  lcd.setCursor(2,0);
  lcd.write((byte)1);
  lcd.write((byte)2);
  lcd.setCursor(6,1);
  lcd.print(":p");
}


void loop()
{
}
