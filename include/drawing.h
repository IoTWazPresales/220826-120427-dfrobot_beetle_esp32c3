#ifndef drawing
#define drawing

#include "Declarations.h"



int drawsecond = rtc.getSecond();

int drawhours = rtc.getHour();


void refreshhours()
{
    screen.drawRect(((w/2)-(24*8)/2),/*y=*/h/2,(24*2),30,COLOR_RGB565_BLACK);
    screen.fillRect(((w/2)-(24*8)/2),/*y=*/h/2,(24*2),30,COLOR_RGB565_BLACK);

}



void refreshminutes()
{
   int drawminutes = rtc.getMinute();
     screen.drawRect(((w/2)-(24*8)/2)*4,/*y=*/h/2,(24*2),30,COLOR_RGB565_BLACK);
    screen.fillRect(((w/2)-(24*8)/2)*4,/*y=*/h/2,(24*2),30,COLOR_RGB565_BLACK);
    if(drawminutes==59)
      {
        delay(60000);
        refreshhours(); 
        
        Serial.println("accessed");
      }

}
void refreshseconds()
{

    int drawsecond = rtc.getSecond();
    screen.drawRect(((w/2)-(24*8)/2)*7,/*y=*/h/2,(24*2),30,COLOR_RGB565_BLACK);
    screen.fillRect(((w/2)-(24*8)/2)*7,/*y=*/h/2,(24*2),30,COLOR_RGB565_BLACK);
    
      if(drawsecond<1)
      {
        delay(1000);
        refreshminutes(); 
      }
        
    
    //screen.drawRect(); 


}



#endif