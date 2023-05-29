#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16, 2);// A4>SDA  A5>SCL
 
void setup(){
 lcd.begin (16,2);
 lcd.setBacklight(HIGH);
 pinMode(13, INPUT);
}
 
void loop(){
  lcd.setCursor(6,0);
  lcd.print("sim");
}
