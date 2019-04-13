/* wakeup_init.cpp  
*   (1)Power board provide wkup high level, open device, pressing two seconds.
*   (2)Init GPIO port.
*/
#include "wakeup.h"


void Gpio_init(){
   pinMode(32, OUTPUT);  //bat_en  电源控制端，timer.cpp--控制电池供电只能是1.5小时
   pinMode(33, OUTPUT);  //led_r 红色LED， 代码里面没有33 引脚的拉高
   pinMode(27, OUTPUT);  //led_b 蓝色LED
   pinMode(25, INPUT);  //wkup   开机按键
}

void wakeup_init(){
  Gpio_init();
  int cnt=0;
  while(digitalRead(25)==1){
    if(cnt++ >= 200){
       digitalWrite(27,1);
       digitalWrite(32,1);
       while(digitalRead(25));    //  这里的设置，开关的形式必须是触点模式，而不是机械模式。
       return;
    }
    delay(10);
  }
}

void check_wakeup(){    // 加一个判断，板子处于工作状态
  int cnt=0;
   while(digitalRead(25)==1){
    if(cnt++ >= 200){
       digitalWrite(27,0);
       digitalWrite(32,0);
       while(digitalRead(25));
       } 
    delay(10); 
  }
}
