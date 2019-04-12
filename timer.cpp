/* timer.cpp
*   (1)required memory is automatically dynamically allocated inside the xSemaphoreCreateBinary() function.
*/
#include "timer.h"

/**********timer_init***************/
hw_timer_t * timer = NULL;           //       创建一个定时器对象
volatile SemaphoreHandle_t timerSemaphore;    // 创建一个定时器信号量,volatile 限定符,防止编译器优化对设备寄存器的访问。
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;    
volatile uint32_t isrCounter = 0;


//定时服务函数
void IRAM_ATTR onTimer(){
  // Increment the counter and set the time of ISR
  portENTER_CRITICAL_ISR(&timerMux);  // 进入临界段
  isrCounter++;
  portEXIT_CRITICAL_ISR(&timerMux); //退出临界段
  // Give a semaphore that we can check in the loop
  xSemaphoreGiveFromISR(timerSemaphore, NULL);         //释放一个二值信号量
  // 硬件定时1.5h
  if( isrCounter>=5400){
     digitalWrite(32,0);                              /* 5400 秒，干电池的工作时间 */   
  }
}

//定时器配置
void timer_init()
{
    timerSemaphore = xSemaphoreCreateBinary();      /* Creates a new binary semaphore, automatically allocated memory */
    timer = timerBegin(0, 80, true);                //  初始化定时器0 80分频 向上计数
    timerAttachInterrupt(timer, &onTimer, true);    //  配置定时器中断函数
    timerAlarmWrite(timer, 1000000, true);          //  每计数1s 触发一次中断
    timerAlarmEnable(timer);                        //  使能定时器函数
}