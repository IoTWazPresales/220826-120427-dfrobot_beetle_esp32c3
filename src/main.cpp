
//---| definitions |------------------------------------------------------------

//#define TEST

//---| includes |---------------------------------------------------------------
#include "Declarations.h"


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
	Serial.begin(115200);
    getthetime();// Get and set the time from the network time server
    findWeather();
    
    
    
    
    
    
    
    
     
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
    ui.drawString(/*x=*/w/5,/*y=*/h/2,"Page of loading",COLOR_RGB565_WHITE,ui.bgColor,/*fontsize =*/2,/*Invert=*/0);
	delay(1000);
    printLocalTime();
    
	//ui.refresh();
}

//===| eof - end of file |======================================================