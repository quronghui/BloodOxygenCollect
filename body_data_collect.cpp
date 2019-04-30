/* 
* data_sampling.cpp
*   (1) Before sampling data, check_wakeup() funcation check the Esp32 is normal power supply.
*   (2) Setting the samping_frequency by max30102.cpp
*   (3) data_convert():data convert to string
*   (4) data_communication()：transmit to APP
*/
#include "body_data.h"

/*****variable_init******/
uint8_t value = 0;
uint32_t un_min, un_max, un_prev_data, un_brightness;  //variables to calculate the on-board LED brightness that reflects the heartbeats
int32_t i;
uint32_t aun_ir_buffer[500]; //infrared LED sensor data
uint32_t aun_red_buffer[500];  //red LED sensor data

char datavalue1[20]={};     /* 全局变量只能在头文件中声明，不能定义 */
char datavalue2[9]={};
char datavalue3[5]={"\r\n"};   //

/*Serial_debug println output message*/
void serial_data(){
    Serial.print(F("red="));           
    Serial.print(aun_red_buffer[4], DEC);
    Serial.print(F(", ir="));
    Serial.println(aun_ir_buffer[4], DEC);
}


/*配置采样频率为200Hz 5次叠加 相当于40Hz*/
void sampling_frequency(){
    for(i=0;i<5;i++){                         //if(!maxim_max30102_write_reg(REG_SPO2_CONFIG,0x2a))  
        while(digitalRead(12)==1);            //When have new data, the pin charge to LOW, 
        maxim_max30102_read_fifo((aun_red_buffer), (aun_ir_buffer));  //read from MAX30102 FIFO
        aun_red_buffer[4] += aun_red_buffer[0];         /* 这里每次只能读首地址的数据，aun_red_buffer[0] */
        aun_ir_buffer[4] += aun_ir_buffer[0];           /* 将这个数值叠加放大，放大波形的作用*/
    }
    serial_data();
}

/* data_convert */
void data_convert(){
    aun_red_buffer[4] = 21310715 - aun_red_buffer[4];   /* 翻转波形，测得的数据越大，需要显示的波形越小 */
    aun_ir_buffer[4] = 21310715 - aun_ir_buffer[4];     /* APP设置max30102脱落的下限值10000 */

    itoa(aun_red_buffer[4],datavalue1,10);  /*stdlib_noniso.c---nonstandard (but usefull) conversion functions.*/
    itoa(aun_ir_buffer[4],datavalue2,10);   /* data convert to string  */

    strcat(datavalue1,datavalue2);          /* combination string */
    strcat(datavalue1,datavalue3);
    // Serial.println(datavalue1);
}

/* data_communication with phone */
void data_communication(){  
    if (deviceConnected) {
        pCharacteristic->setValue(datavalue1);
        pCharacteristic->notify();
        //Serial.println(datavalue1);
    } 
    aun_red_buffer[4]=10000000;
    aun_ir_buffer[4]=10000000;
}

void data_sampling()
{
    check_wakeup();
    sampling_frequency();
    data_convert();
}