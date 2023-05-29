#include "DigiKeyboard.h"
void setup () {
   DigiKeyboard.update();
}
void loop(){
  DigiKeyboard.print("texto");
  delay(1000);
}
