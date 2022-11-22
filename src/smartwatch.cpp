#include "Declarations.h"


int counterweather = 360;
int wakeup_count = 0;
int count = 0;
int led = 10;
bool Awake=false;
int sleepCount=0;
String currentTime;


void clearTimeAwake(){

  tft.setTextColor(ST77XX_BLACK);
  tft.setCursor(/*x=*/(w-((2*6)*9)),/*y=*/0);
  tft.print(currentTime);

}
void clearTimeSleep(){

  tft.setTextColor(ST77XX_BLACK);
  tft.setCursor((240-150)/2, (240-40) / 2);
  tft.println(currentTime);

}
void deviceDeepSleep(){
digitalWrite(10, LOW); // turn off backlight
  digitalWrite(2, LOW); // set RS LOW
  digitalWrite(3, LOW); // set RS LOW
  tft.enableSleep(true);

  Serial.flush();
  esp_deep_sleep_start();

}
void deviceSleep(){

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.println(rtc.getTime("%F %A"));
  tft.setTextSize(5);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor((240-150)/2, (240-40) / 2);
  tft.println(rtc.getTime("%H:%M"));
  currentTime = rtc.getTime("%H:%M");
  delay(1000);
  clearTimeSleep();
  sleepCount++;
  while(sleepCount>1000)
    {
      deviceDeepSleep();
    }
}

void deviceAwake(){

  tft.setTextSize(2);//6 pixels wide by 8 pixels high x 2
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(/*x=*/(w-((2*6)*9)),/*y=*/0);
  tft.print(rtc.getTime("%H:%M:%S"));
  currentTime = rtc.getTime("%H:%M:%S");
  delay(1000);
  clearTimeAwake();
  if(count==36000)
    {
      getweather();
      count=0;
    }
  count++;
  if (deviceConnected) {  //If there is a Bluetooth connection, send data
   tft.drawBitmap(/*x=*/0,/*y=*/0,/*bitmap gImage_Bitmap=*/image_data_bluetooth232,/*w=*/16,/*h=*/16,ST77XX_WHITE);
    pTxCharacteristic->setValue("Hello");  //Send string
    pTxCharacteristic->notify();
    delay(10); // bluetooth stack will go into congestion, if too many packets are sent

    pTxCharacteristic->setValue("DFRobot");  //Send string
    pTxCharacteristic->notify();
    delay(10); // bluetooth stack will go into congestion, if too many packets are sent
  }
  //heartdeets();
}

void onWake(){

  Awake=true;
  sethomepage();
  deviceAwake();
}

void IRAM_ATTR isr(){

  onWake();
  //sethomepage();
  //getweather();
}

void IRAM_ATTR isr1(){

  onWake();
  //sethomepage();
  //getweather();
}

void setup(){

	Serial.begin(115200);
  delay(1000);
  //attachInterrupt(2, isr, FALLING);
  //attachInterrupt(5, isr, FALLING);
  //attachInterrupt(0, isr, FALLING);
  delay(1000);
  tft.init(240,240);
  lv_init();
  delay(1000);
  BLEBegin();
  delay(1000);
  gettime();
  //connectMQTT(); 
  sethomepage();
  //heartbeatinit();
  getweather();
 // initimages();
}

void loop(){


  while(wakeup_count<1000)
  {
    deviceAwake();
    wakeup_count++;
    if(wakeup_count==999)
      {
        tft.fillScreen(ST77XX_BLACK);
      }
  }
  deviceSleep();
}