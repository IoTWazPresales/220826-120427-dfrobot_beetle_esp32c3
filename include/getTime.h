#include <WiFi.h>


const char *ntpServer = "0.za.pool.ntp.org";
const long gmtOffset_sec = 8 * 3600;
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
