#ifndef PAGES
#define PAGES
#include "Declarations.h"

ESP32Time rtc;

int w = tft.width();
int h = tft.height();

void sethomepage()
{     

    //drawPic();
      tft.setTextSize(2);
      tft.setTextColor(ST77XX_WHITE);
      tft.fillScreen(ST77XX_BLACK);
      tft.setTextWrap(true);
      getweather();    
      if(!WiFi.mode(WIFI_OFF))
      {
          tft.drawXBitmap(/*x=*/0,/*y=*/0,/*bitmap gImage_Bitmap=*/gImage[0],/*w=*/32,/*h=*/32,ST77XX_WHITE);
      }
      
}

#endif
