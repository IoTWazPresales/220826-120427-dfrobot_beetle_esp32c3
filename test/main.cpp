#include <SoftwareSerial.h> 

//#include <TinyGPS++.h>
#include "screenType.h"
SoftwareSerial GpsSerial(20, 21); //RX,TX

struct
{
  char GPS_DATA[80];
  bool GetData_Flag;      //Get GPS data flag bit
  bool ParseData_Flag;    //Parse completed flag bit 
  char UTCTime[11];       //UTC time
  char latitude[11];      //Latitude
  char N_S[2];            //N/S
  char longitude[12];     //Longitude
  char E_W[2];            //E/W
  bool Usefull_Flag;      //If the position information is valid flag bit 
} Save_Data;

const unsigned int gpsRxBufferLength = 600;
char gpsRxBuffer[gpsRxBufferLength];
unsigned int gpsRxLength = 0;

void Error_Flag(int num)
{
  Serial.print("ERROR");
  Serial.println(num);
  while (1)
  {
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
  }
}

void print_GpsDATA()
{
  if (Save_Data.ParseData_Flag)
  {
    Save_Data.ParseData_Flag = false;

    Serial.print("Save_Data.UTCTime = ");
    Serial.println(Save_Data.UTCTime);

    if(Save_Data.Usefull_Flag)
    {
      Save_Data.Usefull_Flag = false;
      Serial.print("Save_Data.latitude = ");
      Serial.println(Save_Data.latitude);
      Serial.print("Save_Data.N_S = ");
      Serial.println(Save_Data.N_S);
      Serial.print("Save_Data.longitude = ");
      Serial.println(Save_Data.longitude);
      Serial.print("Save_Data.E_W = ");
      Serial.println(Save_Data.E_W);
    }
    else
    {
      
    tft.println("GPS DATA is not usefull!");
      Serial.println("GPS DATA is not usefull!");
    }    
  }
}

void parse_GpsDATA()
{
  char *subString;
  char *subStringNext;
  if (Save_Data.GetData_Flag)
  {
    Save_Data.GetData_Flag = false;
    Serial.println("************************");
    Serial.println(Save_Data.GPS_DATA);

    for (int i = 0 ; i <= 6 ; i++)
    {
      if (i == 0)
      {
        if ((subString = strstr(Save_Data.GPS_DATA, ",")) == NULL)
          Error_Flag(1);    //Analysis error 
      }
      else
      {
        subString++;
        if ((subStringNext = strstr(subString, ",")) != NULL)
        {
          char usefullBuffer[2]; 
          switch(i)
          {
            case 1:memcpy(Save_Data.UTCTime, subString, subStringNext - subString);break;    //Get UTC time 
            case 2:memcpy(usefullBuffer, subString, subStringNext - subString);break;        //Get position status 
            case 3:memcpy(Save_Data.latitude, subString, subStringNext - subString);break;   //Get latitude information 
            case 4:memcpy(Save_Data.N_S, subString, subStringNext - subString);break;        //Get N/S
            case 5:memcpy(Save_Data.longitude, subString, subStringNext - subString);break;  //Get longitude information 
            case 6:memcpy(Save_Data.E_W, subString, subStringNext - subString);break;        //Get E/W

            default:break;
          }
          subString = subStringNext;
          Save_Data.ParseData_Flag = true;
          if(usefullBuffer[0] == 'A')
            Save_Data.Usefull_Flag = true;
          else if(usefullBuffer[0] == 'V')
            Save_Data.Usefull_Flag = false;
        }
        else
        {
          Error_Flag(2);    //Analysis error
        }
      }
    }
  }
}
void RST_GpsRxBuffer(void)
{
  memset(gpsRxBuffer, 0, gpsRxBufferLength);      //Clear
  gpsRxLength = 0;

}
void Read_Gps() 
{
  while (GpsSerial.available())
  {
    gpsRxBuffer[gpsRxLength++] = GpsSerial.read();
    if (gpsRxLength == gpsRxBufferLength)RST_GpsRxBuffer();
  }

  char* GPS_DATAHead;
  char* GPS_DATATail;
  if ((GPS_DATAHead = strstr(gpsRxBuffer, "$GPRMC,")) != NULL || (GPS_DATAHead = strstr(gpsRxBuffer, "$GNRMC,")) != NULL )
  {
    if (((GPS_DATATail = strstr(GPS_DATAHead, "\r\n")) != NULL) && (GPS_DATATail > GPS_DATAHead))
    {
      memcpy(Save_Data.GPS_DATA, GPS_DATAHead, GPS_DATATail - GPS_DATAHead);
      Save_Data.GetData_Flag = true;

      RST_GpsRxBuffer();
    }
  }
}








void setup()
{
  Serial.begin(115200);   //Debug Serial
  GpsSerial.begin(9600);  //Gps Serial

  Serial.println("DFRobot Gps");
  Serial.println("Wating...");
  Save_Data.GetData_Flag = false;
  Save_Data.ParseData_Flag = false;
  Save_Data.Usefull_Flag = false;
}

void loop()
{
  Read_Gps();     
  
  parse_GpsDATA();  
  
  print_GpsDATA();  
 
}



/*
TinyGPSPlus gps;

void print_speed()
{
  Serial.println("within Print speed");
  tft.setTextColor(ST77XX_WHITE);
       
  if (gps.location.isValid() == 1)
  {
   //String gps_speed = String(gps.speed.kmph());
   Serial.println("within GPS LOCATION");
    tft.setTextSize(1);
    
    tft.setCursor(25, 5);
    tft.print("Lat: ");
    tft.setCursor(50, 5);
    tft.print(gps.location.lat(),6);
    Serial.println(gps.location.lat(),6);
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
    Serial.write(gps.satellites.value());
    //print_speed();
  }
  else
  {
   
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(0, 0);
    tft.setTextSize(3);
    tft.print("No Data");
    Serial.print("No Data");
    
  }  

}

void setup()
{   
  Serial.begin(115200);  //Debug Serial 
  GpsSerial.begin(9600);  //Gps Serial   
} 

void loop()
{  
  
  delay(1000);
  displayGPS();
   tft.print(gps.location.lat(),6);
  
  //Serial.flush();
  /*while (GpsSerial.available() > 0)
  { 
    byte gpsData = GpsSerial.read(); 
   Serial.write(gpsData); 
   }



  }
*/






