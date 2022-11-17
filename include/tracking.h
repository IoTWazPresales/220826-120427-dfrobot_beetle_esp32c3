#ifndef TRACKING
#define TRACKING

#include <Wire.h>
#include <TinyGPS++.h>
#include "screenType.h"
#include <SoftwareSerial.h> 

//#define RX 20
//#define TX 21
SoftwareSerial GpsSerial(20, 21); //RX,TX

TinyGPSPlus gps;


void print_speed()
{
  
  Serial.println("within Print speed");
  tft.setTextColor(ST77XX_WHITE);
       
  if (gps.location.isValid() == 1)
  {
   //String gps_speed = String(gps.speed.kmph());
    tft.setTextSize(1);
    tft.setCursor(25, 5);
    tft.print("Lat: ");
    tft.setCursor(50, 5);
    tft.print(gps.location.lat(),6);

    tft.setCursor(25, 20);
    tft.print("Lng: ");
    tft.setCursor(50, 20);
    tft.print(gps.location.lng(),6);

    tft.setCursor(25, 35);
    tft.print("Speed: ");
    tft.setCursor(65, 35);
    tft.print(gps.speed.kmph());
    
    tft.setTextSize(1);
    tft.setCursor(0, 50);
    tft.print("SAT:");
    tft.setCursor(25, 50);
    tft.print(gps.satellites.value());

    tft.setTextSize(1);
    tft.setCursor(70, 50);
    tft.print("ALT:");
    tft.setCursor(95, 50);
    tft.print(gps.altitude.meters(), 0);

    
    
  }
  else
  {
    
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(0, 0);
    tft.setTextSize(3);
    tft.print("No Data");
   
  }  

}



void displayGPS(){

  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (GpsSerial.available())
    {
      if (gps.encode(GpsSerial.read()))
      {
        newData = true;
      }
    }
  }

  //If newData is true
  if(newData == true)
  {
    newData = false;
    Serial.println(gps.satellites.value());
    
  }
  else
  {
   
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(0, 0);
    tft.setTextSize(3);
    tft.print("No Data");
    
  }  

print_speed();





}






#endif