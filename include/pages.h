#ifndef PAGES
#define PAGES
#include "Declarations.h"
#include "Icons.h"
#include "images.h"
#include "lvgl.h"




ESP32Time rtc;

lv_obj_t *home_page;
lv_obj_t *home_page_background;

lv_obj_t *FissionBlack_img;


int w = tft.width();
int h = tft.height();



void sethomepage()
{     
    lv_init();

    LV_IMG_DECLARE(FissionBlack);
    lv_obj_t * FissionBlack_img = lv_img_create(lv_scr_act());//lv_scr_act()
    lv_img_set_src(FissionBlack_img, &FissionBlack);
    lv_obj_set_size(FissionBlack_img, 240, 240);

    //drawPic();
      tft.setTextSize(2);
      tft.setTextColor(ST77XX_WHITE);
      tft.fillScreen(ST77XX_BLACK);
      tft.setTextWrap(true);
      
     // tft.drawRGBBitmap(/*x=*/0,/*y=*/0,/*bitmap gImage_Bitmap=*/backgroundImage,/*w=*/240,/*h=*/240);
      
      getweather();    
      if(!WiFi.mode(WIFI_OFF))
      {
          tft.drawXBitmap(/*x=*/0,/*y=*/0,/*bitmap gImage_Bitmap=*/gImage[0],/*w=*/32,/*h=*/32,ST77XX_WHITE);
      }
      lv_scr_load(home_page);
      
}

#endif
