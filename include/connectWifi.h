#ifndef CONNECTWIFI
#define CONNECTWIFI

#include <WiFi.h>

const char *ssid = "Yebo";    //WIFI name
const char *password = "Amer1ca15"; //WIFI password
uint32_t notConnectedCounter = 0;

void connectToWifi(){

WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println(ssid);
        Serial.println(password);
        Serial.print(".");
        notConnectedCounter++;
        if(notConnectedCounter > 10) { // Reset board if not connected after 15s
        Serial.println("Resetting due to Wifi not connecting...");
        ESP.restart();
    }
        
        
    }

    Serial.println("WiFi connected!");
     Serial.println(WiFi.localIP());


    
}








#endif