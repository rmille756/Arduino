#include <IRremote.h>

#define PinoSensor 8//define pino do sensor

#define positivo 5//define pinos dos motores
#define negativo 6

#define azul 13
#define verde 3//define pinos dos LEDs
#define vermelho 4

#define UM 16580863
#define DOIS 16613503//variaveis para as teclas dos LEDs
#define TRES 16597183

#define MEIO 16614013
#define CIMA 16627783
#define BAIXO 16622173//variaveis para as teclas do motor
#define DIREITA 16597693
#define ESQUERDA 16581373

bool AZUL = false;
bool VERDE = false;//variaveis para o estado dos leds
bool VERMELHO = false;

bool POSITIVO = false;//variaveis para o estado do motor
bool NEGATIVO = false;

IRrecv irsens(PinoSensor);//declara o pino do sensor

decode_results results;

void setup()
{
  Serial.begin(9600);
  pinMode(azul, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(vermelho, OUTPUT);
  pinMode(positivo, OUTPUT);
  pinMode(negativo, OUTPUT);
  
  irsens.enableIRIn();//inicia o sensor para o recebimento
}

void loop() {
    digitalWrite(azul, AZUL);
    digitalWrite(verde, VERDE);
    digitalWrite(vermelho, VERMELHO);
    digitalWrite(positivo, POSITIVO);
    digitalWrite(negativo, NEGATIVO);
    
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

      case BAIXO:
    POSITIVO = false;
    NEGATIVO = true;
      break;

      case MEIO:
    POSITIVO = !POSITIVO;
      break;

      case CIMA:
    POSITIVO = true;
    NEGATIVO = false;
      break;
      
      case DIREITA:
    POSITIVO = true;
    NEGATIVO = false;
    digitalWrite(positivo, POSITIVO);
    digitalWrite(negativo, NEGATIVO);
    delay(1000);
    POSITIVO = !POSITIVO;
      break;
      
      case ESQUERDA:
    POSITIVO = false;
    NEGATIVO = true;
    digitalWrite(positivo, POSITIVO);
    digitalWrite(negativo, NEGATIVO);
    delay(1000);
    POSITIVO = !POSITIVO;
      break;
      
    }
    irsens.resume(); // Receive the next value
  }

  delay(10);
}
