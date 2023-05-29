// Definições dos pinos
const int termistorPin = A0;  // Pino analógico para leitura do termistor

// Parâmetros do termistor
const float R1 = 100000.0;    // Resistência nominal do termistor em ohms
const float T1 = 25.0;        // Temperatura nominal do termistor em graus Celsius
const float beta = 3950.0;    // Coeficiente beta do termistor

void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial
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

  // Ajuste para correção da temperatura nominal
  steinhart -= steinhart - T1;

  // Imprime a temperatura no monitor serial
  Serial.print("Temperatura: ");
  Serial.print(steinhart);
  Serial.println(" °C");

  delay(1000);  // Aguarda um segundo
}
