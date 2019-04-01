/* wifi_connect.cpp */
#include "wifi_content.h"
void wifi_connect()
{
    const char* ssid ="water";          /*yourNetworkName*/
    const char* password = "12345678";   /*yourNetworkPass*/
    WiFi.begin(ssid, password);
    while (WiFi.status()!= WL_CONNECTED){
        delay(500);
        Serial.println("Connectingto WiFi..");
  }
  Serial.println("Connectedto the WiFi network");
}