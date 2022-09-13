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


//#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
//#define TIME_TO_SLEEP  5        /* Time ESP32 will go to sleep (in seconds) */
ESP32Time rtc;




void setup()
{
	
	
	// start serial communication
	Serial.begin(9600);
	
rtc.setTime(30, 24, 15, 17, 1, 2021);  // 17th Jan 2021 15:24:30
      //rtc.setTime(1609459200);  // 1st Jan 2021 00:00:00
      //rtc.offset = 7200; // change offset value

  Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S"));   // (String) returns time with specified format

 
	

	//Serial.println("Initialize clock: %s\n", (boResult) ? "ok" : "FAILED");
  
  ui.begin();
  ui.setTheme(DFRobot_UI::MODERN);
  
       

	delay(50);
	
	
	// initialize clock
	
}

//------------------------------------------------------------------------------
// main loop
//------------------------------------------------------------------------------
void loop()
{


 screen.fillScreen(COLOR_RGB565_BLACK);
   screen.setFont(&FreeMono12pt7b);//Set font to FreeMono12pt7b
        screen.setCursor(/*x=*/120,/*y=*/150);
        //Set text color 
        screen.setTextColor(COLOR_RGB565_LGRAY);
        //Set to text auto-wrap mode, true=Auto-wrap, false=No auto-wrap
        screen.setTextWrap(true);
       //screen.print("HelloWorld!");

   screen.println(rtc.getTime("%A, %B %d %Y %H:%M:%S"));
	delay(-1);
	//ui.refresh();
}

//===| eof - end of file |======================================================