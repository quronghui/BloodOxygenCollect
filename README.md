# BloodOxygenCollect
The item is based on  Arduino ESP32.

## Code Compile Environment

### 环境搭建

1. VS Code 中加载组件platform。
2. 在platform 中加载ESP32的库。

### 基于ESP-IDF开发

- 使用ESP-IDF进行开发

  ![platform.png](https://github.com/quronghui/BloodOxygenCollect/blob/master/platform.png)

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

## ESP32 Code firmware flush

### 通过官方的ESP Flash Download Tool 烧录固件

+ [esp32 flush](https://blog.csdn.net/Anmore/article/details/81065875)
+ 在windows进行 C:\Users\quronghui\.platformio
+ 基于 PlatformIO arduino esp32

1. 对ESP32进行开发，将代码编译好了之后，可以提取后在其他设备使用[ESP Flash Download Tool](https://www.espressif.com/en/support/download/other-tools)直接烧录。

2. 使用ESP Flash Download Tool烧录需要提前准备四个文件
   + 其中包含两个启动引导文件`bootloader.bin``boot_app0.bin`
     + `bootloader.bin`的位置为PlatformIO安装目录下的`C:\Users\quronghui\.platformio\packages\framework-arduinoespressif32\tools\sdk\bin`目录下面，任意选择一个就行；它的对应的烧录地址为`0X1000`。
     + `boot_app0.bin`的位置为PlatformIO安装目录下的`platformio\packages\framework-arduinoespressif32\tools\partitions`目录下面，它对应的烧录地址为`0xe000` 
   + 一个flash划分文件`partitions.bin`
     + `partitions.bin`的位置为代码工程目录下的`.pioenvs\[board]`目录下面,它对应的烧录地址为`0x8000`。
   + 一个固件文件`firmware.bin`当然名字是可以更改的。
     + `firmware.bin`的位置为代码工程目录下的`.pioenvs\[board]`目录下面，这个就是代码编译出来的固件，它对应的烧录地址为`0x10000`.
     + 如果分区文件未做修改的话（人为修改，或者更换编译平台），更新固件或者重新烧录只在对应地址开始需要烧录这一个文件即可

3. 固件烧录

   ![flushtool.png](https://github.com/quronghui/BloodOxygenCollect/blob/master/flushtool.png)

   + 注意他们的分区地址
   + 点击 ERASE 擦除原先代码；
   + Start 开始烧录

4. 批量生产 -- 代码下载

   + ESP32-WROOM-32 厂家固件的烧录

     ![espwroom.png](https://github.com/quronghui/BloodOxygenCollect/blob/master/espwroom.png)

   + ESP32-WROOM-32 二维码的生成和打印

     ![QR__code.png](https://github.com/quronghui/BloodOxygenCollect/blob/master/QR__code.png)

### 其他的下载方式

+ [其他下载方式](https://blog.csdn.net/qq_24550925/article/details/85334575)