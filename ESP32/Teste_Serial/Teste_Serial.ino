String site = "";
void setup() {
  Serial.begin(9600);
  while(Serial.available()){};
  site =  "texto 1\n";
  site += "texto 2\n";
  site += "texto 3\n";
  site += "texto 4\n";
  site += "texto 5\n";

  Serial.print(site);

  site = "";
}
void loop() {
  // put your main code here, to run repeatedly:

}
