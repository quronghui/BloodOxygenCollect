# BloodOxygenCollect
The item is based on  Arduino ESP32.

## Code Compile Environment

### 环境搭建

1. VS Code 中加载组件platform。
2. 在platform 中加载ESP32的库。

### 基于ESP-IDF开发

- 使用ESP-IDF进行开发

  ![platform.png](https://github.com/quronghui)

- 例子的参考 [[espressif](https://github.com/espressif)/**esp-idf**  ]()

### 基于Arduino 开发

- Framework 选择arduino，这样就可以直接开发了
- arduino 的文件代码的命名格式
  + The name defined need xxx.cpp. If you used xxx.c is a bug. 
  + The bug is "collect2: error: ld returned 1 exit status".

## Code  Structure 

/*

\* Arduino ESP32 for BloodOxygenCollect:

\*    By max30102 Blood Oxygen Sensor collect AD data.

\*    Max30102 transmit data to ESP32 by I2C communication.

\*    Esp32 open BLE_Server and service, advertising Ble_Mac_Adress, waiting connection.

\*    Phone app connect tht esp32 device, accept datas and show fitting data waveform.         

*/

## ESP32 Code firmware

