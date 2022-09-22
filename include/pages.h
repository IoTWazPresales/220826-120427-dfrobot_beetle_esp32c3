#ifndef PAGES
#define PAGES

#include "Declarations.h"

ESP32Time rtc;
int w = screen.width();
int h = screen.height();


void deviceAwake(){

    screen.setCursor(/*x=*/(w-((2*6)*9)),/*y=*/0);
    screen.print(rtc.getTime("%H:%M:%S")); 
    Serial.flush();
    screen.setCursor(/*x=*/screen.width()/2,/*y=*/screen.height()/3);
    //screen.print(myObject["main"]["humidity"]);  
    delay(1000);

}
void sethomepage()
{
   
   
      screen.setTextSize(2);
        //Set text color 
      screen.setTextColor(COLOR_RGB565_WHITE);
      screen.fillScreen(COLOR_RGB565_SKYBLUE);
        //Set to text auto-wrap mode, true=Auto-wrap, false=No auto-wrap
       screen.setTextWrap(true);
       Serial.println("Text Set");
       
        

        
    
 if(!WiFi.mode(WIFI_OFF))
 {
  screen.drawXBitmap(/*x=*/0,/*y=*/0,/*bitmap gImage_Bitmap=*/gImage[0],/*w=*/32,/*h=*/32,COLOR_RGB565_LGRAY);
 }

deviceAwake();
}



void sleep()
{



}
void appDisplay()
{




}












#endif
