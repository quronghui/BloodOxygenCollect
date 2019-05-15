/* bluetooth.h
*   (1)ble_init();
*/

#ifndef BLUETOOTH_H
#define BLUETOOTH_H


/* SERVICE_UUID  识别码，用原来的uuid的话，不能正常连接；用新的这个又不能正常发送数据 */
// #define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
// #define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
// #define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"
#define SERVICE_UUID      (uint16_t)0xFFE0       //APP与蓝牙通信要求，Every service must have a unique UUID.       
#define CHARACTERISTIC_UUID_TX  (uint16_t)0xFFE1    //APP与蓝牙通信要求，不要更改
#define CHARACTERISTIC_UUID_RX  (uint16_t)0xFFE2    // APP与蓝牙通信要求，Reveive


#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEClient.h>
#include <BLE2902.h>
#include <Arduino.h>

extern bool deviceConnected;                // 声明的全局变量，为了能在数据传输的带时候调用
extern BLECharacteristic* pCharacteristic;

extern void ble_init();


#endif