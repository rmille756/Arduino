#include <Ultrasonic.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TRIGGER_PIN  2
#define ECHO_PIN     3

Ultrasonic ultrasonico(TRIGGER_PIN, ECHO_PIN);
LiquidCrystal_I2C lcd(0x27,16, 2);

void setup()
  {
  lcd.begin (16,2);
  lcd.setBacklight(HIGH);
  lcd.init();
  Serial.begin(9600);
  }

void loop()
  {
  float cmMsec, inMsec;
  long microsec = ultrasonico.timing();

  cmMsec = ultrasonico.convert(microsec, Ultrasonic::CM);


  lcd.setCursor(0,0);
  lcd.print("MS:");
  lcd.setCursor(0,1);
  lcd.print(microsec);
  lcd.setCursor(6,0);
  lcd.print("CM:");
  lcd.setCursor(5,1);
  lcd.print(cmMsec);
  delay(500);
  }
