#include "screenType.h"
#include "connectWifi.h"


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
   
    Serial.println(&timeinfo, "%F %T %A"); // formatted output
    
}
void gettime()
{
    connectToWifi();
    configTime PROGMEM(gmtOffset_sec, daylightOffset_sec, ntpServer);// After the acquisition is successful, the chip will use the RTC clock to keep the time updated
    printLocalTime();
    //WiFi.disconnect(true);
    //WiFi.mode(WIFI_OFF);
   //Serial.println("WiFi disconnected!");
    
}
