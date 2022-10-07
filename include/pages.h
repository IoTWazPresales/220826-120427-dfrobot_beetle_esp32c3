#ifndef PAGES
#define PAGES
#include "images.h"
#include "Declarations.h"

ESP32Time rtc;

int w = screen.width();
int h = screen.height();

void sethomepage()
{
      screen.setTextSize(2);
      screen.setTextColor(COLOR_RGB565_WHITE);
      screen.fillScreen(COLOR_RGB565_BLACK);
      screen.setTextWrap(true);    
      if(!WiFi.mode(WIFI_OFF))
      {
          screen.drawXBitmap(/*x=*/0,/*y=*/0,/*bitmap gImage_Bitmap=*/gImage[0],/*w=*/32,/*h=*/32,COLOR_RGB565_LGRAY);
      }

}

#endif
