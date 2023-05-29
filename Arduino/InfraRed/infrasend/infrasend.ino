#include<IRremote.h>
#define bt1 8
#define bt2 9
unsigned long valor;
IRsend irsend;
decode_results res;
decode_type_t tipo;
void setup(){
 Serial.begin(9600);
 pinMode(bt1,INPUT_PULLUP);
 pinMode(bt2,INPUT_PULLUP);}
void loop(){
 if(digitalRead(bt1)== 0){// Esquerda
   valor = 0xFF22DD;
    irsend.sendRC5(valor,12);
    Serial.println(valor,HEX);
    tipo-res.decode_type;
    Serial.println(tipo);}
 else if(digitalRead(bt2)== 0){// Direita
   valor = 0xFFC23D;
    irsend.sendRC5(valor,12);
    Serial.println(valor,HEX);
    tipo-res.decode_type;
    Serial.println(tipo);
}
}
