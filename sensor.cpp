/* sensor_init.cpp
*   (1)Sensor used IIC communication;
*   (2)Init wire bus protocol.
*/
#include "sensor.h"

/*sensordata Init */  
static uint8_t uch_dummy;   // unsigned char -->__uint8_t --> uint8_t

void sensor_init()
{
    //uint8_t uch_dummy;
    pinMode(12, INPUT);         // 用INT 作为12脚的输入，没有任何的判断？？
    maxim_max30102_read_reg(REG_INTR_STATUS_1, &uch_dummy);     /*IIC的配置,从adress读数据，保存到uch_dummy*/
    Wire.begin();                 /*Init IIC Wire， 初始化SDA，SCL*/
    maxim_max30102_reset();     /*  Reset the MAX30102 */
    maxim_max30102_init();      /* Initialize the MAX30102 */
    delay(1000);
}