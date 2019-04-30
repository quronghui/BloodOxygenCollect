/* sensor_init.cpp
*   (1)By max30102 Blood Oxygen Sensor collect AD data.
*   (2)Sensor used IIC communication transmit data to ESP32.
*   (3)Init wire bus protocol.
*   (4) 拔出传感器后，在插上能正常检测
*/
#include "sensor.h"

/*sensordata Init */  
static uint8_t uch_dummy;   // unsigned char -->__uint8_t --> uint8_t

int sensor_init()
{
    //uint8_t uch_dummy;
    pinMode(12, INPUT);         // 用INT 作为12脚的输入，没有任何的判断？？
    Wire.begin();                 /*Init IIC Wire， 初始化SDA，SCL*/        // change line17-16  
    maxim_max30102_read_reg(REG_INTR_STATUS_1, &uch_dummy);     /*IIC的配置,从adress读数据，保存到uch_dummy*/
    maxim_max30102_reset();     /*  Reset the MAX30102 */
    maxim_max30102_init();      /* Initialize the MAX30102 */
    delay(1000);
    return 1;
}