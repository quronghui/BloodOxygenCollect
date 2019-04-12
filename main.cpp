#include "wakeup.h"
#include "sensor.h"
#include "bluetooth.h"
// #include "wifi_content.h"
#include "timer.h"
#include "body_data.h"

void setup() {
  Serial.begin(115200);
  wakeup_init();      /* provide power and LED light */
  sensor_init();      /* Init IIC */
  ble_init();       /* Open BLE server and advertising Ble address */
  // wifi_connect();   /* Over the programe size */
  timer_init();
}

void loop() {
  data_sampling();
  data_communication();
  // put your main code here, to run repeatedly:
}