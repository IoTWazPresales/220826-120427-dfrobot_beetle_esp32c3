
//---| definitions |------------------------------------------------------------

//#define TEST

//---| includes |---------------------------------------------------------------
#include "Declarations.h"


int led = 10;

float batteryLevel = map(analogRead(A0), 0.0f, 4095.0f, 0, 100);
//------------------------------------------------------------------------------
// setup routine
//------------------------------------------------------------------------------


//#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
//#define TIME_TO_SLEEP  5        /* Time ESP32 will go to sleep (in seconds) */

 
//char *thetime  = atoi (rtc.getTime().substring(1, 3).c_str ());
 
 String tw = rtc.getTime("%H:%M:%S");
 String th = rtc.getTime("%H:%M:%S");
int wakeup_count = 0;
int batteryPercentage = 100;

void setup()
{
	
	// start serial communication
    
	Serial.begin(115200);
    //ui.begin();
   // ui.setTheme(DFRobot_UI::MODERN);
    screen.begin();
    screen.fillScreen(COLOR_RGB565_BLACK);
    
    // Get and set the time from the network time server
    gettime();
    connectMQTT();
    //printLocalTime();
    getweather();
    //BLEBegin();  //Initialize Bluetooth
    sethomepage();
    
	delay(1000);
	
}

//------------------------------------------------------------------------------
// main loop
//------------------------------------------------------------------------------



void deviceSleep()
{

                 

        screen.setCursor(/*x=*/(w/2)-((24*8)/2),/*y=*/h/2);
        screen.print(rtc.getTime("%H")); 
        screen.print(rtc.getTime("%M"));
        screen.print(rtc.getTime("%S"));
        
        //client.loop();
        //printLocalTime();
        delay(1000);
        refreshseconds();
    
       


}

void loop()
{
    
    //deviceSleep();
      
   deviceAwake();
      
    //ui.refresh();
}


//===| eof - end of file |======================================================