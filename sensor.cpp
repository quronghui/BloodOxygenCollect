/* sensor_init.cpp
*   (1)Sensor used IIC communication;
*   (2)Init wire bus protocol.
*/
#include "sensor.h"

/*sensordata Init */  
static uint8_t uch_dummy;

void sensor_init()
{
    //uint8_t uch_dummy;
    pinMode(12, INPUT);
    maxim_max30102_read_reg(REG_INTR_STATUS_1, &uch_dummy); /*IIC的配置*/
    Wire.begin();  /*Init IIC Wire*/
    maxim_max30102_reset();
    maxim_max30102_init();  
    delay(1000);
}