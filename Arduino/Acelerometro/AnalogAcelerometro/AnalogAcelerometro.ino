//Programa: Acelerometro MMA8452
//Autor: Arduino e Cia
//Baseado no programa exemplo da biblioteca Sparkfun SFE_MMA8452

#include <Wire.h>
#include <SFE_MMA8452Q.h>

//Cria uma instancia do MMA8452 chamada acelerometro
//com endereco I2C 0x1C (pino SA0 em LOW/Desligado)
MMA8452Q acelerometro(0x1C);
float green;

int mapped1;
int mapped2;

void setup()
{
  pinMode(10, OUTPUT);  
  pinMode(11, OUTPUT);
  Serial.begin(9600);
  Serial.println("Teste de comunicacao MMA8452");
  //Inicializa o acelerometro com o valores padrao de +/-2g e
  //saida de 800 Hz
  acelerometro.init();
  //Utilize a linha abaixo para inicializar o acelerometro com
  //+/-2g, 4g, or 8g, usando SCALE_2G, SCALE_4G, ou SCALE_8G
  //acelerometro.init(SCALE_4G);
  //Utilize a linha abaixo para determinar tambem a frequencia
  //de saida do acelerometro (padrao de 800 Hz), utilizando
  //como segundo parametro ODR_800 (800 Hz), ODR_400 (400 Hz),
  //ODR_200 (200 Hz), ODR_100 (100 Hz), ODR_50 (50 Hz),
  //ODR_12 (12.5 Hz), ODR_6 (6.25 Hz), ou ODR_1 (1.56 Hz)  
  //acelerometro.init(SCALE_8G, ODR_6);
}

void loop()
{
  //A linha abaixo aguarda o envio de novos dados pelo acelerometro
  if (acelerometro.available())
  {
    //Efetua a leitura dos dados do sensor
    acelerometro.read();
    //acelerometro.read() atualiza dois grupos de variaveis:
    //* int x, y, e z armazena o valor de 12 bits lido do
    //acelerometro
    // * float cx, cy, e cz armazena o calculo da aceleracao
    //dos valores de 12 bits. Essas variaveis estao em
    //unidades de "g"
    
    //Mostra as coordenadas lidas do sensor
    printCalculatedAccels();
    
    //Selecione a linha abaixo para mostra os valores digitais
    //printAccels();
    
    //Mostra a orientacao (retrato/paisagem/flat)
    green = mapToPositive(acelerometro.cx*80);
    
mapToRange(green, green, mapped1, mapped2);
    analogWrite(11, mapped1);
    analogWrite(10, mapped2);
  }
}
int mapToPositive(int value) {
  // Mapeia o valor de -100 a 100 para 0 a 200
  int mappedValue = map(value, -100, 100, 0, 200);
  // Mapeia o valor de 0 a 200 para 0 a 100
  mappedValue = map(mappedValue, 0, 200, 0, 50);
  return mappedValue;
}
void mapToRange(int value1, int value2, int& mappedValue1, int& mappedValue2) {
  // Mapeia o valor1 de 0 a 50 para 50 a 0
  mappedValue1 = map(value1, 0, 25, 50, 0);

  if (mappedValue1 < 0) {
    mappedValue1 = 0;
  } 
  // Mapeia o valor2 de 51 a 100 para 0 a 50
  mappedValue2 = map(value1, 25, 50, 0, 50);
  if (mappedValue2 < 0 ) {
    mappedValue2 = 0;
  } 
}
void printCalculatedAccels()
{ 
  Serial.print(acelerometro.cx, 3);
  Serial.print("t     ");
  Serial.print(acelerometro.cy, 3);
  Serial.print("t     ");
  Serial.print(acelerometro.cz, 3);
  Serial.print("t     ");
}
