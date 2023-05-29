// Biblioteca bluetooth low energy
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
 
#define SCAN_TIME  1
 
BLEScan* pBLEScan;
 
// String responsável por verificar e comparar o nome do dispositivo
String deviceName;
// String responsável por verificar e comparar o endereço do dispositivo
String deviceAddress;
// Váriavel signed int responsável por imprimir a potência do sinal em dB
int16_t deviceRSSI;
//Variável unsigned int responsável por fazer a contagem dos dispositivos encontrados
uint16_t countDevice;
 
// Pino responsável pelo led conectado na GPIO 2
int led = 2;
 
// Variável responsável por deixar iluminacao ligada até que outra conexão seja realizada
int pressed = 0;
 
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
    }
};
 
void setup(){
  // Variável led definida como saída 
  pinMode(led, OUTPUT);
  pinMode(12, OUTPUT);
 
  // Porta serial configurada com taxa de transmissão de 115200 b/S 
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println("APROXIME SUA SMARTBAND");
 
  // Inicia comunicação BLE e realiza nova varredura
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); 
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); 
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
}
void loop(){
  BLEScanResults foundDevices = pBLEScan->start(SCAN_TIME);
  int count = foundDevices.getCount();
  for (int i = 0; i < count; i++){
  BLEAdvertisedDevice d = foundDevices.getDevice(i);
    if (d.getName() == "Mi Smart Band 4") {
    deviceAddress = d.getAddress().toString().c_str();
    if (deviceAddress == "d1:ed:6a:d5:b6:5c" && d.getRSSI() > -40) {
      if (pressed == 0){
          digitalWrite(led, LOW);
          digitalWrite(12, LOW);
          pressed = 1;
        }
        else{
          pressed = 0;
          digitalWrite(led, HIGH);
          digitalWrite(12, HIGH);
        }}}}
  pBLEScan->clearResults();
}