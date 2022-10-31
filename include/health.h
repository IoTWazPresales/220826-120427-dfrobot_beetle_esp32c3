#include <Wire.h>
#include "MAX30105.h"
#include "screenType.h"
#include "heartRate.h"

MAX30105 particleSensor;
const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred
float beatsPerMinute;
int beatAvg;

void heartbeatinit(){


if (particleSensor.begin(Wire, I2C_SPEED_FAST) == false) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }

   byte ledBrightness = 70; //Options: 0=Off to 255=50mA
  byte sampleAverage = 1; //Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  int sampleRate = 400; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 69; //Options: 69, 118, 215, 411
  int adcRange = 16384; //Options: 2048, 4096, 8192, 16384

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings
}

  void heartdeets()
  {


    particleSensor.begin(Wire, I2C_SPEED_FAST); //Use default I2C port, 400kHz speed
  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running

    

      long irValue = particleSensor.getIR();    //Reading the IR value it will permit us to know if there's a finger on the sensor or not
                                           //Also detecting a heartbeat
if(irValue > 7000){                                           //If a finger is detected
                                     //Clear the tft
    tft.drawBitmap(5, 5, logo2_bmp, 24, 21, ST77XX_WHITE);       //Draw the first bmp picture (little heart)
    tft.setTextSize(2);                                   //Near it tft the average BPM you can tft the BPM if you want
    tft.setTextColor(ST77XX_WHITE); 
    tft.setCursor(50,0);                
    tft.println("BPM");             
    tft.setCursor(50,18);                
    tft.println(beatAvg); 
    
    
  if (checkForBeat(irValue) == true)                        //If a heart beat is detected
  {
                                    //Clear the tft
    tft.drawBitmap(0, 0, logo3_bmp, 32, 32, ST77XX_WHITE);    //Draw the second picture (bigger heart)
    tft.setTextSize(2);                                //And still tfts the average BPM
    tft.setTextColor(ST77XX_WHITE);             
    tft.setCursor(50,0);                
    tft.println("BPM");             
    tft.setCursor(50,18);                
    tft.println(beatAvg); 
   
    tone(3,1000);                                        //And tone the buzzer for a 100ms you can reduce it it will be better
    delay(100);
    noTone(3);                                          //Deactivate the buzzer to have the effect of a "bip"
    //We sensed a beat!
    long delta = millis() - lastBeat;                   //Measure duration between two beats
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);           //Calculating the BPM

    if (beatsPerMinute < 255 && beatsPerMinute > 20)               //To calculate the average we strore some values (4) then do some math to calculate the average
    {
      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE; //Wrap variable

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }

}
  if (irValue < 7000){       //If no finger is detected it inform the user and put the average BPM to 0 or it will be stored for the next measure
     beatAvg=0;
    
     tft.setTextSize(1);                    
     tft.setTextColor(ST77XX_WHITE);             
     tft.setCursor(30,5);                
     tft.println("Please Place "); 
     tft.setCursor(30,15);
     tft.println("your finger ");  
     
     noTone(3);
     }








 }
