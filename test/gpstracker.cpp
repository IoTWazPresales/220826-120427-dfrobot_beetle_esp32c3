#include <SoftwareSerial.h> 
#include <TinyGPS++.h>
#include "screenType.h"
SoftwareSerial GpsSerial(20, 21); //RX,TX
//GPS pin VCC -> ESP32 C3 3v3
//GPS pin GND -> ESP32 C3 GND
//GPS pin TX  -> ESP32 C3 20
//GPS pin RX  -> ESP32 C3 21

TinyGPSPlus gps;
int lastSeen_lat;
int lastSeen_lon;

void print_speed()
{
  
       
  if (gps.location.isValid() == 1)
  {

    String gps_speed = String(gps.speed.kmph());
    tft.setTextSize(1);
    tft.setCursor(25, 5);
    tft.println("Lat: ");
    tft.setCursor(50, 5);
    tft.println(gps.location.lat(),6);
    tft.setCursor(25, 20);
    tft.println("Lng: ");
    tft.setCursor(50, 20);
    tft.println(gps.location.lng(),6);

    tft.setCursor(25, 35);
    tft.println("Speed: ");
    tft.setCursor(65, 35);
    tft.println(gps.speed.kmph());
    
    tft.setTextSize(1);
    tft.setCursor(0, 50);
    tft.println("SAT:");
    tft.setCursor(25, 50);
    tft.println(gps.satellites.value());

    tft.setTextSize(1);
    tft.setCursor(70, 50);
    tft.println("ALT:");
    tft.setCursor(95, 50);
    tft.println(gps.altitude.meters(), 0);
    
    
    
  }
  else
  { 
     int lastSeen_lat=gps.location.lat();
    int lastSeen_lon=gps.location.lng();
    tft.setTextSize(1);
    tft.setCursor(200, 200);
    tft.println("Last Seen:");
    tft.print(lastSeen_lat);
    tft.print(lastSeen_lon);
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
    byte gpsData = GpsSerial.read(); 
    newData = false;
    print_speed();
  }
  else
  {
   
   // Serial.setTextColor(ST77XX_WHITE);
    //Serial.setCursor(0, 0);
    //Serial.setTextSize(3);
  //  Serial.print("No Data");
    Serial.println("No Data");
    
  }  

}

void setup()
{   
  Serial.begin(115200);  //Debug Serial 
  GpsSerial.begin(9600);  //Gps Serial   
  tft.init(240,240); 
} 

void loop()
{  
 delay(1000); 
 tft.fillScreen(ST77XX_BLACK); 
 
 displayGPS();


}







