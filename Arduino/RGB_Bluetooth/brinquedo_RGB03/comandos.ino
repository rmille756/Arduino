void acendeAzul(){
  digitalWrite(azul, HIGH);
}

void acendeVerde(){
  digitalWrite(verde, HIGH);
}
void acendeVermelho(){
  digitalWrite(vermelho, HIGH);
}
void inverteAzul(){
  AZUL = !AZUL;
  digitalWrite(azul, AZUL);
}
void inverteVerde(){
  VERDE = !VERDE;
  digitalWrite(verde, VERDE);
}
void inverteVermelho(){
  VERMELHO = !VERMELHO;
  digitalWrite(vermelho, VERMELHO);
}
void apagaTodos(){
  digitalWrite(azul, LOW);
  digitalWrite(vermelho, LOW);
  digitalWrite(verde, LOW);
}
