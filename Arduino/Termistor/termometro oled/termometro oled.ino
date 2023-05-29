#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Largura do display
#define SCREEN_HEIGHT 32 // Altura do display

#define SCREEN_ADDRESS 0x3C // Endereço do display (tente trocar por 0x3D se não funcionar)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Definições dos pinos
const int termistorPin = A0;  // Pino analógico para leitura do termistor

// Parâmetros do termistor
const float R1 = 100000.0;    // Resistência nominal do termistor em ohms
const float T1 = 25.0;        // Temperatura nominal do termistor em graus Celsius
const float beta = 3950.0;    // Coeficiente beta do termistor

void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial
  // Inicializa o display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("Erro na inicialização!"));
    while(1);
  }

  display.clearDisplay();

}

void loop() {
  // Leitura da tensão no pino do termistor
  int rawADC = analogRead(termistorPin);

  // Conversão para resistência em ohms
  float resistance = R1 / ((1023.0 / rawADC) - 1.0);

  // Cálculo da temperatura em graus Celsius usando a fórmula de Steinhart-Hart
  float steinhart;
  steinhart = resistance / R1;                   // (R/Ro)
  steinhart = log(steinhart);                    // ln(R/Ro)
  steinhart /= beta;                             // (1/B) * ln(R/Ro)
  steinhart += 1.0 / (T1 + 273.15);              // + (1/To)
  steinhart = 1.0 / steinhart;                    // Inverte
  steinhart -= 273.15;                           // Converte para Celsius

  // Atualiza todas as mudanças
  display.clearDisplay();
  display.setTextSize(2); // Tamanho
  display.setTextColor(1); // Cor
  display.setCursor(40, 0); // Cursor pode ir de 0,0 a 128,32
  display.print(steinhart+47);
  display.display();
  delay(500);
}
