#ifndef drawing
#define drawing

#include "Declarations.h"



int drawsecond = rtc.getSecond();
int drawhours = rtc.getHour();


void refreshhours()
{
    tft.drawRect(((w/2)-(24*8)/2),/*y=*/h/2,(24*2),30,ST77XX_BLACK);
    tft.fillRect(((w/2)-(24*8)/2),/*y=*/h/2,(24*2),30,ST77XX_BLACK);

}



void refreshminutes()
{
   int drawminutes = rtc.getMinute();
     tft.drawRect(((w/2)-(24*8)/2)*4,/*y=*/h/2,(24*2),30,ST77XX_BLACK);
    tft.fillRect(((w/2)-(24*8)/2)*4,/*y=*/h/2,(24*2),30,ST77XX_BLACK);
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
    tft.drawRect(((w/2)-(24*8)/2)*7,/*y=*/h/2,(24*2),30,ST77XX_BLACK);
    tft.fillRect(((w/2)-(24*8)/2)*7,/*y=*/h/2,(24*2),30,ST77XX_BLACK);
    
      if(drawsecond<1)
      {
        delay(1000);
        refreshminutes(); 
      }
        
    
    //tft.drawRect(); 


}

void refreshhoursAw()
{
    tft.drawRect((w-((2*6)*8)),/*y=*/0,(24*2),30,ST77XX_BLACK);
    tft.fillRect((w-((2*6)*8)),/*y=*/0,(24*2),30,ST77XX_BLACK);

}



void refreshminutesAw()
{
   int drawminutes = rtc.getMinute();
     tft.drawRect((w-((2*6)*6)),/*y=*/0,(24*2),30, ST77XX_BLACK);
     tft.fillRect((w-((2*6)*6)),/*y=*/0,(24*2),30, ST77XX_BLACK);
    if(drawminutes==59)
      {
        delay(60000);
        refreshhoursAw(); 
        
        Serial.println("accessed");
      }

}
void refreshsecondsAw()
{

    int drawsecond = rtc.getSecond();
    tft.drawRect((w-((2*6)*3)),/*y=*/0,(24*2),30,ST77XX_BLACK);
    tft.fillRect(w-((2*6)*3),/*y=*/0,(24*2),30,ST77XX_BLACK);
    
      if(drawsecond<1)
      {
        delay(1000);
        refreshminutesAw(); 
      }
        
    
    //tft.drawRect(); 


}

#endif