#ifndef SCREENTYPE
#define SCREENTYPE

  
#include <Adafruit_GFX.h>         // Core graphics library
#include "Adafruit_ST7789.h"    // Hardware-specific library
#include "Adafruit_ST77xx.h"

#include <SPI.h>

#ifdef ADAFRUIT_HALLOWING
  #define TFT_CS        39 // Hallowing display control pins: chip select
  #define TFT_RST       37 // Display reset
  #define TFT_DC        38 // Display data/command select
  #define TFT_BACKLIGHT  7 // Display backlight pin

#elif defined(ARDUINO_FEATHER_ESP32) // Feather Huzzah32
  #define TFT_CS         14
  #define TFT_RST        15
  #define TFT_DC         32

#elif defined(ESP8266)
  #define TFT_CS         4
  #define TFT_RST        16                                            
  #define TFT_DC         5

#else
  // For the breakout board, you can use any 2 or 3 pins.
  // These pins will also work for the 1.8" TFT shield.
  #define TFT_CS        2
  #define TFT_RST       3 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC        8
#endif

#define SerialDebugging true

// OPTION 1 (recommended) is to use the HARDWARE SPI pins, which are unique
// to each board and not reassignable. For Arduino Uno: MOSI = pin 11 and
// SCLK = pin 13. This is the fastest mode of operation and is required if
// using the breakout board's microSD card.

// For 1.44" and 1.8" TFT with ST7735 (including HalloWing) use:
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);





#endif