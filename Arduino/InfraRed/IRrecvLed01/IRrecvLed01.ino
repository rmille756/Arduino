#include <IRremote.h>

#define PinoSensor 8//define pino do sensor

#define azul 13
#define verde 3//define pinos dos LEDs
#define vermelho 4

#define UM 16580863
#define DOIS 16613503//variaveis para as teclas dos LEDs
#define TRES 16597183

bool AZUL = false;
bool VERDE = false;//variaveis para o estado dos leds
bool VERMELHO = false;

IRrecv irsens(PinoSensor);//declara o pino do sensor

decode_results results;

void setup()
{
  Serial.begin(9600);
  pinMode(azul, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(vermelho, OUTPUT);
  
  irsens.enableIRIn();//inicia o sensor para o recebimento
}

void loop() {
    digitalWrite(azul, AZUL);
    digitalWrite(verde, VERDE);
    digitalWrite(vermelho, VERMELHO);
    
  if (irsens.decode(&results)) {
    Serial.println(results.value, DEC);
    
    switch(results.value){
      case UM:
    AZUL = !AZUL;
      break;

      case DOIS:
    VERDE = !VERDE;
      break;

      case TRES:
    VERMELHO = !VERMELHO;
      break;
      
    }
    irsens.resume(); // Receive the next value
  }

  delay(10);
}
