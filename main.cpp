/*
* Arduino ESP32 for BloodOxygenCollect:
*    By max30102 Blood Oxygen Sensor collect AD data.
*    Max30102 transmit data to ESP32 by I2C communication.
*    Esp32 open BLE_Server and service, advertising Ble_Mac_Adress, waiting connection.
*    Phone app connect tht esp32 device, accept datas and show fitting data waveform.         
*/

#include "wakeup.h"
#include "sensor.h"
#include "bluetooth.h"
// #include "wifi_content.h"
#include "timer.h"
#include "body_data.h"


void setup() {
  Serial.begin(115200);
  wakeup_init();      /* provide power and init gpio */
  sensor_init();      /* Init IIC */
  ble_init();       /* Open BLE server and advertising Ble address */
  // wifi_connect();   /* Over the programe size */
  //timer_init();
} 

void loop() {
    data_sampling();
    data_communication();
  // put your main code here, to run repeatedly:
}