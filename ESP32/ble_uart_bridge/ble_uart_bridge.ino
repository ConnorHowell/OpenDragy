#include "Arduino.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <HardwareSerial.h>

std::string rxValue;        // RX STRING VALUE received from BLE

HardwareSerial UART(2);

BLEServer           * pServer             = NULL;
BLECharacteristic   * pTxCharacteristic    = NULL;
BLEService          * pService             = NULL;
bool                 deviceConnected     = false;
bool                 oldDeviceConnected  = false;

#define SERVICE_UUID           "6e400001-b5a3-f393-e0a9-e50e24dcca9e" // UART service UUID
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"

int countBytes = 0;

uint8_t RXbuffer[256];
uint8_t TXbuffer[256];

class MyServerCallbacks: public BLEServerCallbacks
{
    void onConnect(BLEServer* pServer)
    {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer)
    {
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *pCharacteristic)
    {
      Serial.println("Got new value from BLE");
      rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0)  
      {
              for(int i=0; i < rxValue.length(); i++)
              {
                    TXbuffer[i] = rxValue[i];
              }
              UART.write(TXbuffer,rxValue.length());

      }
    }
};

BLEDevice *bleDevice;

void setBLE()
{
    Serial.println("Init BLE...");
    Serial.println(SERVICE_UUID);

    deviceConnected    = false;
    oldDeviceConnected = false;

    // Create the BLE Device
    bleDevice->init("DIYDragy");
    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());
    // Create the BLE Service
    pService = pServer->createService(SERVICE_UUID);
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
}

//The setup function is called once at startup of the sketch
void setup()
{
    Serial.begin(115200);
    UART.begin(9600, SERIAL_8N1, 16, 17);
    setBLE();
}


// The loop function is called in an endless loop
void loop()
{
    if (deviceConnected)
    {
        countBytes = UART.available();
        while (countBytes>=20)
        {
            UART.readBytes(RXbuffer, 20);
            pTxCharacteristic->setValue(RXbuffer,20);    // tx to BLE
            pTxCharacteristic->notify();
            countBytes-=20;
        }
        if (countBytes > 0) // rx from UART
        {
            UART.readBytes(RXbuffer, countBytes);
            pTxCharacteristic->setValue(RXbuffer,countBytes);    // tx to BLE
            pTxCharacteristic->notify();
        }
    }
    
    // disconnecting
    if (!deviceConnected && oldDeviceConnected)
    {
        Serial.println("DISCONNECT!");
        delay(500);
        pServer->startAdvertising(); // restart advertising
        oldDeviceConnected = deviceConnected;
        //rxValue.clear();
        //UART.flush();
    }
    
    // connecting
    if (deviceConnected && !oldDeviceConnected)
    {
        Serial.println("CONNECTED!");
        oldDeviceConnected = deviceConnected;
        //rxValue.clear();
        //UART.flush();
    }
}
