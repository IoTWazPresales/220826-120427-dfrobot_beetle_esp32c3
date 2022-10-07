
//---| definitions |------------------------------------------------------------

//#define TEST

//---| includes |---------------------------------------------------------------
#include "Declarations.h"
#include "esp_sleep.h"

//------------------------------------------------------------------------------
// setup routine
//------------------------------------------------------------------------------
int  counterweather = 360;
bool Awake=false;
int lastState = LOW;  // the previous state from the input pin
int lastState1 = LOW;
int lastState2 = LOW;
int currentState; 
int currentState1; 
int currentState2; 
int count=0;

ezButton button1(2, INPUT_PULLUP);  // create ezButton object that attach to pin 6;
ezButton button2(5, INPUT_PULLUP);  // create ezButton object that attach to pin 7;
ezButton button3(0, INPUT_PULLUP);  // create ezButton object that attach to pin 8;
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  5        /* Time ESP32 will go to sleep (in seconds) */

 
//char *thetime  = atoi (rtc.getTime().substring(1, 3).c_str ());
 int led = 10;
 
 String tw = rtc.getTime("%H:%M:%S");
 String th = rtc.getTime("%H:%M:%S");




void deviceSleep(){
    
        
        screen.setTextSize(3); 
        screen.setCursor(/*x=*/(w/2)-((24*8)/2),/*y=*/h/2);
        screen.print(rtc.getTime("%H:%M:%S"));
        printLocalTime();
        delay(1000);
        refreshseconds();
        
        
}
void deviceAwake(){

    
    screen.setTextSize(2);
    screen.setCursor(/*x=*/(w-((2*6)*9)),/*y=*/0);
    screen.print(rtc.getTime("%H:%M:%S")); 
    refreshsecondsAw();

    if(count==3600)
      {
      getweather();
      count=0;
      }
      count++;
      delay(1000);
      Serial.println("INDEVICEAWAKE");
   
   
    //heartdeets();
    
}
void onWake()
{

    Awake=true;
    sethomepage();
    getweather();
    deviceAwake();

}
void IRAM_ATTR isr() 
{
  onWake();
  
  //sethomepage();
  getweather();
}
void setup()
{
        
	Serial.begin(115200);
  attachInterrupt(2, isr, FALLING);
  attachInterrupt(5, isr, FALLING);
  attachInterrupt(0, isr, FALLING);
  screen.begin();
  button1.setDebounceTime(50); // set debounce time to 50 milliseconds
  button2.setDebounceTime(50); // set debounce time to 50 milliseconds
  button3.setDebounceTime(50); // set debounce time to 50 milliseconds
  screen.fillScreen(COLOR_RGB565_BLACK);
  //BLEBegin();
  gettime();
  //connectMQTT();
  sethomepage();
  //heartbeatinit();
 	
}

//------------------------------------------------------------------------------
// main loop
//------------------------------------------------------------------------------
void eventListener()
{
  button1.loop(); // MUST call the loop() function first
  button2.loop(); // MUST call the loop() function first
  button3.loop(); // MUST call the loop() function first

  int btn1State = button1.getState();
  int btn2State = button2.getState();
  int btn3State = button3.getState();
  Serial.print("button 1 state: ");
  Serial.println(btn1State);
  Serial.print("button 2 state: ");
  Serial.println(btn2State);
  Serial.print("button 3 state: ");
  Serial.println(btn3State);




   if(button1.isPressed()){
    Serial.println("The button 1 is pressed");
 
    digitalWrite(led,HIGH);  }
  if(button1.isReleased()){
    Serial.println("The button 1 is released");
    digitalWrite(led, LOW);}
  if(button2.isPressed()){
    Serial.println("The button 2 is pressed");
    digitalWrite(led,HIGH);}
  if(button2.isReleased()){
    Serial.println("The button 2 is released");
    digitalWrite(led,HIGH);}
  if(button3.isPressed()){
    Serial.println("The button 3 is pressed");
    digitalWrite(led,HIGH);  
  }

  if(button3.isReleased()){
    Serial.println("The button 3 is released");
    digitalWrite(led,HIGH);
  }
   /* currentState = analogRead(BUTTON_PIN);
    currentState1 = analogRead(BUTTON_PIN1);
    currentState2 = analogRead(BUTTON_PIN2);
    
    if (currentState == HIGH)
      {
          Awake=true;
          sethomepage();
          
      }          
      if (currentState1 == HIGH)
      {
          Serial.println("The button is pressed 2");
      }       
      if (currentState2 == HIGH)
      {
          Serial.println("The button is pressed 3");
      }*/
      
}

void loop(){


while(Awake==false)
{
   deviceSleep();
}
      deviceAwake();
      Serial.println("Awake");
}

//===| eof - end of file |======================================================