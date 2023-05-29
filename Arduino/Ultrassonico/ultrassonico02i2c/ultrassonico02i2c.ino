int PinTrigger = 2;
int PinEcho = 3;
float TempoEcho=0;

const float VelocidadeSom_mpors = 340;//metros por segundo
const float VelocidadeSom_mporus = 0.000340;//metros por microssegundo

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16, 2);
 

 

void setup()

{
   lcd.begin (16,2);
 lcd.setBacklight(50);
digitalWrite (PinTrigger, LOW);
pinMode (PinEcho, INPUT); // configura pino ECHO como entrada //Inicializa a porta serial
Serial.begin(9600);
lcd.init();
delay (100);

}
void loop()

{

//Envia pulso para o disparar o sensor

DisparaPulsoUltrassonico();

//Mede o tempo de duracao do sinal no pino de leitura (us)
TempoEcho = pulseIn (PinEcho, HIGH);
  lcd.setCursor(0,0);
lcd.print("Distancia:");
lcd.setCursor(0,1);
lcd.print(CalculaDistancia (TempoEcho)*100 );
lcd.setCursor(4,1);
lcd.print("cm");
delay (200);

}
void DisparaPulsoUltrassonico (){

digitalWrite (PinTrigger, HIGH); 
delayMicroseconds (10); 
digitalWrite (PinTrigger, LOW); 
}
float CalculaDistancia(float tempo_us){
  return((tempo_us* VelocidadeSom_mporus)/2);
}
