/* bluetooth.cpp
*       
*/
#include "bluetooth.h"

/**********bledata_init***************/
BLEServer* pServer = NULL;                // Creat pointer for receive createServer
BLECharacteristic* pCharacteristic = NULL;  //创建一个 指针型 对象
bool deviceConnected = false;
std::string m_data=""; 
BLEAdvertisementData  pAdvertisingdata;  // 创建一个对象

 //蓝牙回调类
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };
    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
       pServer->startAdvertising();
    }
};

void ble_init()
{
    BLEDevice::init("MYESP32"); /* Creat BLE and init Device_name */
    pServer = BLEDevice::createServer();    /* Creat BLE server COM */
    pServer->setCallbacks(new MyServerCallbacks());  /* Setting BLEServer callback */

    BLEService *pService = pServer->createService(SERVICE_UUID);    /* Create ble server */
    pCharacteristic = pService->createCharacteristic(               /*Creat BLE discriptor WRITE READ inform*/
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |    
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
    pCharacteristic->addDescriptor(new BLE2902());  /*2902 是蓝牙订阅通知描述符*/

    pService->start();  /*open service*/
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising(); /*open BLE broadcast address*/
    //pAdvertising->addServiceUUID(SERVICE_UUID);

    std::string  pdata=BLEDevice::getAddress().toString().c_str();  /* Gain BLE MAC address */
    for(int i = 1; i <= pdata.length(); i++){
        if((i % 3) !=0 ) {
            m_data+=pdata[i-1];   /* Delete ':' */
        }
        if(pdata[i-1] > 96){
            pdata[i-1] = pdata[i-1] - 32;   /* small write to large  */
        }
    }
    pAdvertisingdata.setName(m_data);       /* setting BLE_Name is MAC_Adress */
    pAdvertising->setScanResponseData(pAdvertisingdata);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x00);  // set value to 0x00 to not advertise this parameter
    BLEDevice::startAdvertising();
    
    delay(5000);
    Serial.println(BLEDevice::getAddress().toString().c_str());   /*  */ 
     // Serial.println( pAdvertising->getManufacturerData().c_str());
    Serial.println( pdata.c_str() );    //打印大写的mac
    delay(1000);
}
