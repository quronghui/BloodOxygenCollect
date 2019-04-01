/* data_sampling.cpp
*
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
    for(i=0;i<5;i++){
          while(digitalRead(12)==1);  //wait until the interrupt pin asserts
           maxim_max30102_read_fifo((aun_red_buffer), (aun_ir_buffer));  //read from MAX30102 FIFO
           aun_red_buffer[4]+= aun_red_buffer[0];
           aun_ir_buffer[4] += aun_ir_buffer[0];
    }
    serial_data();
}

/* data_convert */
void data_convert(){
    aun_red_buffer[4] = 21000000 - aun_red_buffer[4];
    aun_ir_buffer[4] = 21000000 - aun_ir_buffer[4];

    itoa(aun_red_buffer[4],datavalue1,10);  /* data convert to string */
    itoa(aun_ir_buffer[4],datavalue2,10);

    strcat(datavalue1,datavalue2);          /* combination string */
    strcat(datavalue1,datavalue3);
    // Serial.println(datavalue1);
}

/* data_communication with phone */
void data_communication(){  
    if (deviceConnected) {
        pCharacteristic->setValue(datavalue1);
        pCharacteristic->notify();
        Serial.println(datavalue1);
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