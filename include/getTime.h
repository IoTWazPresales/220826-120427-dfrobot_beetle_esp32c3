#include <WiFi.h>

const char *ssid = "kronos";    //WIFI name
const char *password = "Cursed4252!"; //WIFI password
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
void getthetime()
{
    

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        
    }
    Serial.println("WiFi connected!");
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);// After the acquisition is successful, the chip will use the RTC clock to keep the time updated
    printLocalTime();
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    Serial.println("WiFi disconnected!");
    





}
