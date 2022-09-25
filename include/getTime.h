#include <WiFi.h>
#include "screenType.h"


const char *ssid = "kronos";    //WIFI name
const char *password = "Cursed4252!"; //WIFI password
const char *ntpServer = "ntp.is.co.za";
const long gmtOffset_sec = 2 * 3600;
const int daylightOffset_sec = 0;
const bool icon_on=false;




void printLocalTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return;
    }
   
    //Serial.println(&timeinfo, "%F %T %A"); // formatted output
    
}
void gettime()
{
    
    
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        
        
        
    }

    Serial.println("WiFi connected!");
     Serial.println(WiFi.localIP());
     
    configTime(gmtOffset_sec, daylightOffset_sec, "ntp.is.co.za");// After the acquisition is successful, the chip will use the RTC clock to keep the time updated
    printLocalTime();
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
   Serial.println("WiFi disconnected!");
    
}
//int keepthetime() 
//{ 
//	strcpy(distime, tw.c_str()); 
    
//	for (int i = 0; i < tw.length(); i++) 
//		distime[i]; 

//	return 0; 
    //ui.drawString(/*x=*/33,/*y=*/screen.height()/5*4,distime,COLOR_RGB565_WHITE,ui.bgColor,/*fontsize =*/2,/*Invert=*/0);
//} 


