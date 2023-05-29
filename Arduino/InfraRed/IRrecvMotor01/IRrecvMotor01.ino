#include <IRremote.h>

#define PinoSensor 8//define pino do sensor

#define positivo 5//define pinos dos motores
#define negativo 6

#define MEIO 16614013
#define CIMA 16627783
#define BAIXO 16622173//variaveis para as teclas do motor
#define DIREITA 16597693
#define ESQUERDA 16581373

bool POSITIVO = false;//variaveis para o estado do motor
bool NEGATIVO = false;

IRrecv irsens(PinoSensor);//declara o pino do sensor

decode_results results;

void setup()
{
  Serial.begin(9600);
  pinMode(positivo, OUTPUT);
  pinMode(negativo, OUTPUT);
  
  irsens.enableIRIn();//inicia o sensor para o recebimento
}

void loop() {
    digitalWrite(positivo, POSITIVO);
    digitalWrite(negativo, NEGATIVO);
    
  if (irsens.decode(&results)) {
    Serial.println(results.value, DEC);
    
    switch(results.value){
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
