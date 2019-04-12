/* bluetooth.h
*   (1)ble_init();
*/

#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#define SERVICE_UUID      (uint16_t)0xFFE0       //APP与蓝牙通信要求，Every service must have a unique UUID.       
#define CHARACTERISTIC_UUID  (uint16_t)0xFFE1    //APP与蓝牙通信要求，不要更改

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEClient.h>
#include <BLE2902.h>
#include <Arduino.h>

extern bool deviceConnected;                // 声明的全局变量，为了能在数据传输的带时候调用
extern BLECharacteristic* pCharacteristic;

extern void ble_init();


#endif