/* bluetooth.cpp
*    (1)Creat BLE server:
*       setting BLEServer callback funcation，
*       judging a new client connecting or disconnect, 
*       if connection, data_communication() transmit data to Phone APP.
*    (2) Creat a service:
*       Create a new BLE Characteristic associated with this service.
*    (3) Open the startAdvertising, setScanResponseData is the BLE adress.
*    (4) Serial_print ESP32 ble_mac_adress.
*/
#include "bluetooth.h"

/**********bledata_init***************/
BLEServer *pServer = NULL;                // Creat pointer for receive createServer
BLECharacteristic* pCharacteristic = NULL;  //创建一个 指针型 对象
bool deviceConnected = false;
std::string m_data=""; 
BLEAdvertisementData  pAdvertisingdata;  // 创建一个对象

 /*Setting BLEServer callback，judging a new client connecting*/
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };
    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
       pServer->startAdvertising();     /* Start advertising BLE adress*/
    }
};

/* Ble receive  */
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
 
      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Received Value: ");
 
        for (int i = 0; i < rxValue.length(); i++) {
          Serial.print(rxValue[i]);
        }
        Serial.println();
        // Do stuff based on the command received from the app
        if (rxValue.find("A") != -1) { 
            digitalWrite(4,1);
            digitalWrite(16,1);
            Serial.print("Turning ON!");
          //digitalWrite(LED, HIGH);
        }
        else if (rxValue.find("B") != -1) {
            digitalWrite(4,0);
            digitalWrite(16,0);
            Serial.print("Turning OFF!");
          //digitalWrite(LED, LOW);
        }
        Serial.println();
        Serial.println("*********");
      }
    }
};

void ble_init()
{   
    /* Creat server */
    BLEDevice::init("MYESP32"); /* Initialize the %BLE environment and Device_name */
    pServer = BLEDevice::createServer();    
    pServer->setCallbacks(new MyServerCallbacks());  /* Setting BLEServer callback，judging a new client connecting */

    /*Creat a service*/
    /* server 服务器 and service 服务： a server can offer more service*/
    BLEService *pService = pServer->createService(SERVICE_UUID); 

/*change test**********************************/
    pCharacteristic = pService->createCharacteristic(               /*Create a new BLE Characteristic associated with this service.*/
                      CHARACTERISTIC_UUID_TX,                          /* （1）UUID */
                      BLECharacteristic::PROPERTY_READ   |          /* (2) Combinatorial value = 010111 */
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
    pCharacteristic->addDescriptor(new BLE2902());  /*Associate a descriptor with this characteristic。2902 是蓝牙订阅通知描述符*/

    /* BLE reveive  */
    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                        CHARACTERISTIC_UUID_RX,
                        BLECharacteristic::PROPERTY_WRITE
                    );
    pCharacteristic->setCallbacks(new MyCallbacks());

    pService->start();  /*open service*/
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising(); /*open BLE broadcast address*/
    
    /* 不换uuid，开启这个服务，才能正常发数据 */
    pServer->getAdvertising()->start();
    Serial.println("Waiting a client connection to notify...");
    //pAdvertising->addServiceUUID(SERVICE_UUID);

    std::string  pdata = BLEDevice::getAddress().toString().c_str();  /* Gain BLE MAC address */
    for(int i = 1; i <= pdata.length(); i++){
        if((i % 3) != 0 ) {
            m_data += pdata[i-1];   /* Delete ':' */
        }
        if(pdata[i-1] > 96){
            pdata[i-1] = pdata[i-1] - 32;   /* small write charge to large  */
        }
    }

    /* Open the startAdvertising, setScanResponseData is the BLE adress*/
    pAdvertisingdata.setName(m_data);       
    pAdvertising->setScanResponseData(pAdvertisingdata);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x00);  // set value to 0x00 to not advertise this parameter
    BLEDevice::startAdvertising();
    delay(5000);
    
    Serial.println(BLEDevice::getAddress().toString().c_str()); /* 为了显示小写的mac地址 */ 
     // Serial.println( pAdvertising->getManufacturerData().c_str());
    Serial.println( pdata.c_str() );    //打印大写的mac
    delay(1000);
}

