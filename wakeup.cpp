/* wakeup_init.cpp  
*   (1)The name defined need xxx.cpp. If you used xxx.c is a bug. 
*       The bug is "collect2: error: ld returned 1 exit status".
*   (2)Open device, pressing two seconds.
*   (3)Init GPIO port.
*/
#include "wakeup.h"


void Gpio_init(){
   pinMode(32, OUTPUT);  //bat_en  电源控制端
   pinMode(33, OUTPUT);  //led_r 红色LED
   pinMode(27, OUTPUT);  //led_b 蓝色LED
   pinMode(25, INPUT);  //wkup   开机按键
}

void wakeup_init(){
  Gpio_init();
  int cnt=0;
  while(digitalRead(25)==1){
    if(cnt++>=200){
       digitalWrite(27,1);
       digitalWrite(32,1);
       while(digitalRead(25));
       return;
    }
    delay(10);
  }
}

void check_wakeup(){
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
