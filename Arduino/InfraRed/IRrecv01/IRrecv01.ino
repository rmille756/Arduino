
#include <IRremote.h>

int RECV_PIN = 8;
long int UM = 16580863;
long int DOIS = 16613503;
long int TRES = 16597183;

bool AZUL = false;
bool VERDE = false;
bool VERMELHO = false;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, DEC);
  if(results.value == UM){ 
    AZUL = !AZUL;
    digitalWrite(13, AZUL);
  }
  if(results.value == DOIS){
    VERDE = !VERDE;
    digitalWrite(3, VERDE);
  }
  if(results.value == TRES){
    VERMELHO = !VERMELHO;
    digitalWrite(4, VERMELHO);
  }
  
    irrecv.resume(); // Receive the next value
  }

  delay(100);
}
