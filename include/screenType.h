#ifndef SCREENTYPE
#define SCREENTYPE

#include "DFRobot_UI.h"
#include "DFRobot_GDL.h"  

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

#endif