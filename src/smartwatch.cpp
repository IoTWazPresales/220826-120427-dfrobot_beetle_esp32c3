
//---| definitions |------------------------------------------------------------

//#define TEST

//---| includes |---------------------------------------------------------------
#include "Declarations.h"


//------------------------------------------------------------------------------
// setup routine
//------------------------------------------------------------------------------
int counterweather = 360;
int wakeup_count = 0;
int count = 0;
int led = 10;
bool Awake=false;
 int16_t x1;
  int16_t yy1;
  uint16_t width;
  uint16_t height;

  

 String currentTime;


void clearTimeAwake(){

        tft.setTextColor(ST77XX_BLACK);
        tft.setCursor(/*x=*/(w-((2*6)*9)),/*y=*/0);
        tft.print(currentTime);

}
void clearTimeSleep(){
        tft.getTextBounds(rtc.getTime("%H\n%M"), 0, 0, &x1, &yy1, &width, &height);
        tft.setTextColor(ST77XX_BLACK);
        tft.setCursor((w - width) / 2, (h - height) / 2);
        tft.println(currentTime);

}
void deviceSleep(){




        tft.getTextBounds(rtc.getTime("%H\n%M"), 0, 0, &x1, &yy1, &width, &height);
        tft.setTextSize(5); 
        tft.setTextColor(ST77XX_WHITE);
        tft.setCursor((w - width) / 2, (h - height) / 2);
        tft.println(rtc.getTime("%H\n%M"));
        currentTime = rtc.getTime("%H\n%M");
        delay(1000);
        clearTimeSleep();

        
}

void deviceAwake(){

    
    tft.setTextSize(2);
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(/*x=*/(w-((2*6)*9)),/*y=*/0);
    tft.print(rtc.getTime("%H:%M:%S")); 
    
    currentTime = rtc.getTime("%H:%M:%S");
        delay(1000);
        clearTimeAwake();

    
    /*Read_Gps();         //Get GPS data 
    parse_GpsDATA();    //Analyze GPS data 
    print_GpsDATA();    //Output analyzed data */
    if(count==36000)
      {
      getweather();
      count=0;
      }
      count++;
   
   
    //heartdeets();
    
}
void onWake()
{

    Awake=true;
    sethomepage();
    deviceAwake();

}
void IRAM_ATTR isr() 
{
  onWake();
  
  //sethomepage();
  //getweather();
}
void IRAM_ATTR isr1() 
{
  onWake();
  
  //sethomepage();
  //getweather();
}
void setup()
{
    
	Serial.begin(115200);
  delay(1000);
  GpsSerial.begin(9600);
 //initGPS();  //Gps Serial  
  //attachInterrupt(2, isr, FALLING);
  //attachInterrupt(5, isr, FALLING);
  //attachInterrupt(0, isr, FALLING);
  delay(1000);
  tft.init(240,240);    
  delay(1000);
  //screen.fillScreen(COLOR_RGB565_BLACK);
  //BLEBegin();
  gettime();
  //connectMQTT();
  sethomepage();
  //heartbeatinit();
  getweather();
 // initimages();
 	
}
//------------------------------------------------------------------------------
// main loop
//------------------------------------------------------------------------------


void loop(){
      //deviceSleep();

      while(wakeup_count<10){
      deviceAwake();
      wakeup_count++;
      if(wakeup_count==9)
      {
        tft.fillScreen(ST77XX_BLACK);
      }
      }
      deviceSleep();
      
      
      Serial.println("Awake");
    
}

//===| eof - end of file |======================================================