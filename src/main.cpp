//==============================================================================
// Clock - sample for Arduino Clock class
// (c) 2019-2022 by Dirk Ohme
//==============================================================================

//---| definitions |------------------------------------------------------------

//#define TEST

//---| includes |---------------------------------------------------------------
#include "DFRobot_UI.h"
 #include "DFRobot_GDL.h"  
#include "Arduino.h"
#include "ESP32Time.h"
#include <FS.h>
#include "Icons.h"
#include "getTime.h"
#include "getWeather.h"

/*M0*/ 
#if defined ARDUINO_SAM_ZERO
#define TFT_DC  7
#define TFT_CS  5
#define TFT_RST 6
/*ESP32 and ESP8266*/
#elif defined(ESP32) || defined(ESP8266)
#define TFT_DC 1
#define TFT_CS 7
#define TFT_RST 2
#define TFT_BL 10
/*AVR series mainboard*/
#else
#define TFT_DC  2
#define TFT_CS  3
#define TFT_RST 4
#endif



DFRobot_ST7789_240x320_HW_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);

DFRobot_UI ui(&screen, NULL);

int led = 10;
uint8_t value1 = 0;
uint8_t value2 = 0;
uint8_t value3 = 0;


//------------------------------------------------------------------------------
// setup routine
//------------------------------------------------------------------------------

const char *ssid = "kronos";    //WIFI name
const char *password = "Cursed4252!"; //WIFI password
//#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
//#define TIME_TO_SLEEP  5        /* Time ESP32 will go to sleep (in seconds) */
ESP32Time rtc;
 


void setup()
{
	
	
	// start serial communication
	Serial.begin(115200);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        
    }
    Serial.println("WiFi connected!");
    // Get and set the time from the network time server
    // After the acquisition is successful, the chip will use the RTC clock to keep the time updated
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    findWeather();
    printLocalTime();
    
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    Serial.println("WiFi disconnected!");
    
     screen.setCursor(/*x=*/0,/*y=*/150);
     
    //screen.println(rtc.getTime("%A, %B %d %Y %H:%M:%S"));     
  ui.begin();
  ui.setTheme(DFRobot_UI::MODERN);
  screen.fillScreen(COLOR_RGB565_BLACK);
        
        screen.setTextSize(4);
        //Set text color 
        screen.setTextColor(COLOR_RGB565_LGRAY);
        //Set to text auto-wrap mode, true=Auto-wrap, false=No auto-wrap
        screen.setTextWrap(true);
       
 if(!WiFi.mode(WIFI_OFF))
 {
  screen.drawXBitmap(/*x=*/0,/*y=*/0,/*bitmap gImage_Bitmap=*/gImage[0],/*w=*/32,/*h=*/32,COLOR_RGB565_LGRAY);
 }
	
   
	
}

//------------------------------------------------------------------------------
// main loop
//------------------------------------------------------------------------------
void loop()
{
    int w = screen.width();
    int h = screen.height();
    
    screen.setCursor(/*x=*/w/2-(8*8),/*y=*/h/2-1);
    screen.println(rtc.getTime("%H:%M:%S"));     
    
	delay(1000);
    printLocalTime();
    
	//ui.refresh();
}

//===| eof - end of file |======================================================