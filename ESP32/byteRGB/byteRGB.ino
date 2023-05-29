int conta; //
#define qtlnh 8
byte displaySeteSeg[qtlnh][3] = { //valor1== quantidade de linhas && valor2== quantiadade de colunas
 { 0,1,0 },  //0 VERMELHO
 { 1,1,0 },  //1 AMARELO
 { 1,0,0 },  //2 VERDE
 { 1,0,1 },  //3 CIANO
 { 0,0,1 },  //4 AZUL
 { 0,1,1 },  //5 ROXO
 { 1,1,1 },  //6 TODOS ACESOS
 { 0,0,0 }, //7 TODOS APAGADOS
};
String cores[qtlnh]{
  "VERMELHO",
  "AMARELO",
  "VERDE",
  "CIANO",
  "AZUL",
  "ROXO",
  "TODOS ACESOS",
  "TODOS APAGADOS",
};
  
void setup(){
 
  //Definindo pinos como saída
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
 Serial.begin(115200);
  //inicializa display com número 0
  conta = 0;
  ligaSegmentosDisplay(conta);
  Serial.println(cores[conta]);
}
 
void loop() {
  if(Serial.read() == 'a'){ //Se o botão for pressionado soma +1 no display
    conta++; //incremento
    Serial.println(cores[conta]);
    if(conta == qtlnh){ //Se passar de 9 reseta o display para 0==============================================
      conta = 0; 
      ligaSegmentosDisplay(conta);
      Serial.println(cores[conta]);
    }
    else{ //Se não mostra no display o próximo número
      ligaSegmentosDisplay(conta);
    }
  }
}
 
void ligaSegmentosDisplay(byte digito){ //função para acionar o display com o digito correspondente
   
  int pino = 12;
   
  //Liga os segmentos de acordo com o digito correspondente
  for (byte contadorSegmentos = 0; contadorSegmentos < qtlnh; ++contadorSegmentos){ //==================================================
    digitalWrite(pino, displaySeteSeg[digito][contadorSegmentos]);
    ++pino; 
  }
}