int PinTrigger = 2;
int PinEcho = 3;
float TempoEcho=0;

const float VelocidadeSom_mpors = 340;//metros por segundo
const float VelocidadeSom_mporus = 0.000340;//metros por microssegundo

void setup()

{
digitalWrite (PinTrigger, LOW);
pinMode (PinEcho, INPUT); // configura pino ECHO como entrada //Inicializa a porta serial
Serial.begin(9600);

delay (100);

}
void loop()

{

//Envia pulso para o disparar o sensor

DisparaPulsoUltrassonico();

//Mede o tempo de duracao do sinal no pino de leitura (us)
TempoEcho = pulseIn (PinEcho, HIGH);
Serial.println("Distancia em metros:"); 
Serial.println (CalculaDistancia (TempoEcho));
Serial.println("Distancia em centimentros:");
Serial.println(CalculaDistancia (TempoEcho)*100);
delay (500);
}
void DisparaPulsoUltrassonico (){

digitalWrite (PinTrigger, HIGH); 
delayMicroseconds (10); 
digitalWrite (PinTrigger, LOW); 
}
float CalculaDistancia(float tempo_us){
  return((tempo_us* VelocidadeSom_mporus)/2);
}
