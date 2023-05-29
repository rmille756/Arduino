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
 
// Relé reponsável pela trava conectado na GPIO 32
int travaPin = 32;
// Relé responsável pela iluminação conectado na GPIO 33
int ilumPin = 33;
 
// Variável responsável por deixar iluminacao ligada até que outra conexão seja realizada
int pressed = 0;
 
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
    }
};
 
void setup()
{
  // Variáveis travaPin e ilumPin definidas como saída 
  pinMode(travaPin, OUTPUT);
  pinMode(ilumPin, OUTPUT);
 
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
void loop()
{
  // Inicia uma busca por dispositivos cadastrados
  BLEScanResults foundDevices = pBLEScan->start(SCAN_TIME);
  int count = foundDevices.getCount();
  for (int i = 0; i < count; i++)
  {
    BLEAdvertisedDevice d = foundDevices.getDevice(i);
    // Compara o nome do dispositivo cadastrado
    // Insira aqui o nome que foi cadastrado no aplicativo miFit
    if (d.getName() == "myBand 4") {
      digitalWrite(travaPin, HIGH);
      char deviceBuffer[100];
      deviceName = d.getName().c_str();
      deviceAddress = d.getAddress().toString().c_str();
      // Verifica a potência do sinal
      deviceRSSI = d.getRSSI();
      // Compara e verifica o endereço cadastrado
      // Nas configurações de sua pulseira ache a opção bluetooth address 
      // Ajuste da potência do sinal para -60dB 
      if (deviceAddress == "XX:XX:XX:XX:XX:XX" && deviceRSSI > -60) {
        // Variável que garante mudança de estado do pino, somente quando houver uma nova conexão
        if (pressed == 0)
        {
          // Liga iluminação do ambiente desejado
          digitalWrite(ilumPin, LOW);
          pressed = 1;
        }
        else
        {
          pressed = 0;
          digitalWrite(ilumPin, HIGH);
        }
        // Aciona solenoide da trava da porta
        digitalWrite(travaPin, LOW);
        sprintf(deviceBuffer, "Name: %s| Address: %s| RSSI: %d\n", deviceName.c_str(), deviceAddress.c_str(), deviceRSSI);
        Serial.print(deviceBuffer);
        // Tempo predefinido para abrir a porta
        delay(2000);
      }
    }
  }
  pBLEScan->clearResults();
}