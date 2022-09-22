#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "Arduino.h"

BLEServer *pServer = NULL;
BLECharacteristic * pTxCharacteristic;
bool deviceConnected = false;
uint8_t txValue = 0;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"


//Bluetooth connect/disconnect processing. Triggered automatically when a connect/disconnect event occurs
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {   //This function will be executed when Bluetooth is connected
      Serial.println("Bluetooth connected");
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {  //This function will be executed when Bluetooth is disconnected
      Serial.println("Bluetooth disconnected");
      deviceConnected = false;
      delay(500); // give the bluetooth stack the chance to get things ready
      pServer->startAdvertising(); // restart advertising

    }
};

/****************Data receiving section*************/
/****************************************/
//Bluetooth receive data processing. Triggered automatically when data is received
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();//Receive data and assign it to rxValue

      //if(rxValue == "ON"){Serial.println("开灯");}   //Determine whether the received character is "ON"

      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Received Value: ");
        for (int i = 0; i < rxValue.length(); i++){
          Serial.print(rxValue[i]);
        }
        Serial.println();
        Serial.println("*********");
      }
    }
};
/***************************************/
/****************************************/


void sendBLEdata() {
/****************Data transmitting section*************/
/****************************************/
  if (deviceConnected) {  //If there is a Bluetooth connection, send data
    pTxCharacteristic->setValue("Hello");  //Send string
    pTxCharacteristic->notify();
    delay(10); // bluetooth stack will go into congestion, if too many packets are sent

    pTxCharacteristic->setValue("DFRobot");  //Send string
    pTxCharacteristic->notify();
    delay(10); // bluetooth stack will go into congestion, if too many packets are sent
  }
/****************************************/
/****************************************/
}


void BLEBegin(){
  // Create the BLE Device
  BLEDevice::init(/*BLE name*/"UART Service");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pTxCharacteristic = pService->createCharacteristic(
                    CHARACTERISTIC_UUID_TX,
                    BLECharacteristic::PROPERTY_NOTIFY
                  );

  pTxCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic * pRxCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_RX,
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pRxCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");
}