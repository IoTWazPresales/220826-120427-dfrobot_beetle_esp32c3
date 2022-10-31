#include "connectWifi.h"
#include "HTTPClient.h"
#include "screenType.h"
#include <ArduinoJson.h>
#include "HTTP_Method.h"
/*
This example learns how to get weather information
*/

//Fill in the API Key you got
WiFiClient client;
char servername[]="api.openweathermap.org";
String openWeatherMapApiKey = "4de305d0a52ddaceaecba50a757e9968";
//Example:
//String openWeatherMapApiKey = "4de305d0a52ddaceaecba50a757e9968";

// Fill in your city name and country abbreviation
String city = "993800";
String countryCode = "ZA";
String result;


boolean night = false;
int  counter = 360;
String weatherDescription ="";
String weatherLocation = "";
float Temperature;

extern  unsigned char  cloud[];
extern  unsigned char  thunder[];
extern  unsigned char  wind[];
//Example：
//String city = "ChengDu";
//String countryCode = "CN";

//Set the interval for obtaining information, the following is used for testing, so it is set to 10 seconds
//You should limit the minimum interval of access time according to the upper limit of the number of times to access the data within the specified time period of the website you need to obtain the data.
unsigned long lastTime = 0;
//Set to get weather data every 10 minutes
//unsigned long timerDelay = 600000;
//Set to get weather data every 10 seconds
unsigned long timerDelay = 10000;

String jsonBuffer;



String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;

  //Connect URL
  http.begin(client, serverName);

  //Send HTTP site request
  int httpResponseCode = http.GET();

  //This array is used to store the obtained data
  String payload = "{}";

  //Put the obtained data into the array
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  //Release resources
  http.end();

  //Return the obtained data for Json processing
  return payload;
}



void cleartft()
{
    tft.fillScreen(ST77XX_BLACK);
}



void drawTheSun()
{
    tft.fillCircle(64,80,26,ST77XX_YELLOW);
}

void drawTheFullMoon()
{
    tft.fillCircle(64,80,26,ST77XX_WHITE);
}

void drawTheMoon()
{
    tft.fillCircle(64,80,26,ST77XX_WHITE);
    tft.fillCircle(75,73,26,ST77XX_BLACK);
}



void drawLightRain()
{
     tft.drawBitmap(0,35,cloud,128,90,ST77XX_WHITE);
     tft.fillRoundRect(50, 105, 3, 13, 1, ST77XX_BLUE);
     tft.fillRoundRect(65, 105, 3, 13, 1, ST77XX_BLUE);
     tft.fillRoundRect(80, 105, 3, 13, 1, ST77XX_BLUE);
}

void drawModerateRain()
{
     tft.drawBitmap(0,35,cloud,128,90,ST77XX_WHITE);
     tft.fillRoundRect(50, 105, 3, 15, 1, ST77XX_BLUE);
     tft.fillRoundRect(57, 102, 3, 15, 1, ST77XX_BLUE);
     tft.fillRoundRect(65, 105, 3, 15, 1, ST77XX_BLUE);
     tft.fillRoundRect(72, 102, 3, 15, 1, ST77XX_BLUE);
     tft.fillRoundRect(80, 105, 3, 15, 1, ST77XX_BLUE);
}

void drawHeavyRain()
{
     tft.drawBitmap(0,35,cloud,128,90,ST77XX_WHITE);
     tft.fillRoundRect(43, 102, 3, 15, 1, ST77XX_BLUE);
     tft.fillRoundRect(50, 105, 3, 15, 1, ST77XX_BLUE);
     tft.fillRoundRect(57, 102, 3, 15, 1, ST77XX_BLUE);
     tft.fillRoundRect(65, 105, 3, 15, 1, ST77XX_BLUE);
     tft.fillRoundRect(72, 102, 3, 15, 1, ST77XX_BLUE);
     tft.fillRoundRect(80, 105, 3, 15, 1, ST77XX_BLUE);
     tft.fillRoundRect(87, 102, 3, 15, 1, ST77XX_BLUE);
}

void drawThunderstorm()
{
     tft.drawBitmap(0,40,thunder,128,90,ST77XX_YELLOW);
     tft.drawBitmap(0,35,cloud,128,90,ST77XX_WHITE);
     tft.fillRoundRect(48, 102, 3, 15, 1, ST77XX_BLUE);
     tft.fillRoundRect(55, 102, 3, 15, 1, ST77XX_BLUE);
     tft.fillRoundRect(74, 102, 3, 15, 1, ST77XX_BLUE);
     tft.fillRoundRect(82, 102, 3, 15, 1, ST77XX_BLUE);
}

void drawLightSnowfall()
{
     tft.drawBitmap(0,30,cloud,128,90,ST77XX_WHITE);
     tft.fillCircle(50, 100, 3, ST77XX_WHITE);
     tft.fillCircle(65, 103, 3, ST77XX_WHITE);
     tft.fillCircle(82, 100, 3, ST77XX_WHITE);
}

void drawModerateSnowfall()
{
     tft.drawBitmap(0,35,cloud,128,90,ST77XX_WHITE);
     tft.fillCircle(50, 105, 3, ST77XX_WHITE);
     tft.fillCircle(50, 115, 3, ST77XX_WHITE);
     tft.fillCircle(65, 108, 3, ST77XX_WHITE);
     tft.fillCircle(65, 118, 3, ST77XX_WHITE);
     tft.fillCircle(82, 105, 3, ST77XX_WHITE);
     tft.fillCircle(82, 115, 3, ST77XX_WHITE);
}

void drawHeavySnowfall()
{
     tft.drawBitmap(0,35,cloud,128,90,ST77XX_WHITE);
     tft.fillCircle(40, 105, 3, ST77XX_WHITE);
     tft.fillCircle(52, 105, 3, ST77XX_WHITE);
     tft.fillCircle(52, 115, 3, ST77XX_WHITE);
     tft.fillCircle(65, 108, 3, ST77XX_WHITE);
     tft.fillCircle(65, 118, 3, ST77XX_WHITE);
     tft.fillCircle(80, 105, 3, ST77XX_WHITE);
     tft.fillCircle(80, 115, 3, ST77XX_WHITE);
     tft.fillCircle(92, 105, 3, ST77XX_WHITE);     
}

void drawCloudSunAndRain()
{
     tft.fillCircle(73,70,20,ST77XX_YELLOW);
     tft.drawBitmap(0,32,cloud,128,90,ST77XX_BLACK);
     tft.drawBitmap(0,35,cloud,128,90,ST77XX_WHITE);
     tft.fillRoundRect(50, 105, 3, 13, 1, ST77XX_BLUE);
     tft.fillRoundRect(65, 105, 3, 13, 1, ST77XX_BLUE);
     tft.fillRoundRect(80, 105, 3, 13, 1, ST77XX_BLUE);
}

void drawCloudAndTheMoon()
{
     tft.fillCircle(94,60,18,ST77XX_WHITE);
     tft.fillCircle(105,53,18,ST77XX_BLACK);
     tft.drawBitmap(0,32,cloud,128,90,ST77XX_BLACK);
     tft.drawBitmap(0,35,cloud,128,90,ST77XX_WHITE);
}

void drawCloudTheMoonAndRain()
{
     tft.fillCircle(94,60,18,ST77XX_WHITE);
     tft.fillCircle(105,53,18,ST77XX_BLACK);
     tft.drawBitmap(0,32,cloud,128,90,ST77XX_BLACK);
     tft.drawBitmap(0,35,cloud,128,90,ST77XX_WHITE);
     tft.fillRoundRect(50, 105, 3, 11, 1, ST77XX_BLUE);
     tft.fillRoundRect(65, 105, 3, 11, 1, ST77XX_BLUE);
     tft.fillRoundRect(80, 105, 3, 11, 1, ST77XX_BLUE);
}

void drawWind()
{  
     tft.drawBitmap(0,35,wind,128,90,ST77XX_WHITE);   
}

void drawFog()
{
  tft.fillRoundRect(45, 60, 40, 4, 1, ST77XX_WHITE);
  tft.fillRoundRect(40, 70, 50, 4, 1, ST77XX_WHITE);
  tft.fillRoundRect(35, 80, 60, 4, 1, ST77XX_WHITE);
  tft.fillRoundRect(40, 90, 50, 4, 1, ST77XX_WHITE);
  tft.fillRoundRect(45, 100, 40, 4, 1, ST77XX_WHITE);
}

void clearIcon()
{
     tft.fillRect(0,40,128,100,ST77XX_BLACK);
}

void drawCloud()
{
     tft.drawBitmap(0,35,cloud,128,90,ST77XX_WHITE);
}

void drawCloudWithSun()
{
     tft.fillCircle(73,70,20,ST77XX_WHITE);
     tft.drawBitmap(0,36,cloud,128,90,ST77XX_BLACK);
     tft.drawBitmap(0,40,cloud,128,90,ST77XX_WHITE);
}

void drawLightRainWithSunOrMoon()
{
  if(night)
  {
    drawCloudTheMoonAndRain();
  }else
  {
    drawCloudSunAndRain();
  }
}



void drawClearWeather()
{
  if(night)
  {
    drawTheMoon();
  }else
  {
    drawTheSun();
  }
}

void drawFewClouds()
{
  if(night)
  {
    drawCloudAndTheMoon();
  }else
  {
    drawCloudWithSun();
  }
}
void printWeatherIcon(int id)
{
 switch(id)
 {
  case 800: drawClearWeather(); break;
  case 801: drawFewClouds(); break;
  case 802: drawFewClouds(); break;
  case 803: drawCloud(); break;
  case 804: drawCloud(); break;
  
  case 200: drawThunderstorm(); break;
  case 201: drawThunderstorm(); break;
  case 202: drawThunderstorm(); break;
  case 210: drawThunderstorm(); break;
  case 211: drawThunderstorm(); break;
  case 212: drawThunderstorm(); break;
  case 221: drawThunderstorm(); break;
  case 230: drawThunderstorm(); break;
  case 231: drawThunderstorm(); break;
  case 232: drawThunderstorm(); break;

  case 300: drawLightRain(); break;
  case 301: drawLightRain(); break;
  case 302: drawLightRain(); break;
  case 310: drawLightRain(); break;
  case 311: drawLightRain(); break;
  case 312: drawLightRain(); break;
  case 313: drawLightRain(); break;
  case 314: drawLightRain(); break;
  case 321: drawLightRain(); break;

  case 500: drawLightRainWithSunOrMoon(); break;
  case 501: drawLightRainWithSunOrMoon(); break;
  case 502: drawLightRainWithSunOrMoon(); break;
  case 503: drawLightRainWithSunOrMoon(); break;
  case 504: drawLightRainWithSunOrMoon(); break;
  case 511: drawLightRain(); break;
  case 520: drawModerateRain(); break;
  case 521: drawModerateRain(); break;
  case 522: drawHeavyRain(); break;
  case 531: drawHeavyRain(); break;

  case 600: drawLightSnowfall(); break;
  case 601: drawModerateSnowfall(); break;
  case 602: drawHeavySnowfall(); break;
  case 611: drawLightSnowfall(); break;
  case 612: drawLightSnowfall(); break;
  case 615: drawLightSnowfall(); break;
  case 616: drawLightSnowfall(); break;
  case 620: drawLightSnowfall(); break;
  case 621: drawModerateSnowfall(); break;
  case 622: drawHeavySnowfall(); break;

  case 701: drawFog(); break;
  case 711: drawFog(); break;
  case 721: drawFog(); break;
  case 731: drawFog(); break;
  case 741: drawFog(); break;
  case 751: drawFog(); break;
  case 761: drawFog(); break;
  case 762: drawFog(); break;
  case 771: drawFog(); break;
  case 781: drawFog(); break;

  default:break; 
 }
}
void printData(String temperature, int weatherID)
{
 
 

  printWeatherIcon(weatherID);

  tft.setCursor(tft.width()/3,tft.height()/2);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.print(temperature);
  tft.print("C");
}

void getweather() {
  //Send HTTP get request
  //connectToWifi();
    //Check if WIFI is connected
    if(WiFi.status()== WL_CONNECTED){
      String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey;

      //Put the combined URL into the httpGETRequest function to get the text through HTTP get request.
     



    Serial.println("Getting Weather Data");
  if (client.connect(servername, 80)) {  //starts client connection, checks for connection
    client.println("GET /data/2.5/forecast?id="+ city +"&units=metric&cnt=1&APPID="+ openWeatherMapApiKey);
    client.println("Host: api.openweathermap.org");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();
  } 
  else {
    Serial.println("connection failed"); //error message if no client connect
    Serial.println();
  }


  while(client.connected() && !client.available()) delay(1); //waits for data
 
    Serial.println("Waiting for data");

  while (client.connected() || client.available()) { //connected or data available
    char c = client.read(); //gets byte from ethernet buffer
      result = result+c;
    }

  client.stop(); //stop client
  result.replace('[', ' ');
  result.replace(']', ' ');
  Serial.println(result);


  char jsonArray [result.length()+1];
result.toCharArray(jsonArray,sizeof(jsonArray));
jsonArray[result.length() + 1] = '\0';

DynamicJsonDocument doc(1024);
deserializeJson(doc, jsonArray);

String location = doc["city"]["name"];
String temperature = doc["list"]["main"]["temp"];
String weather = doc["list"]["weather"]["main"];
String description = doc["list"]["weather"]["description"];
String idString = doc["list"]["weather"]["id"];
String timeS = doc["list"]["dt_txt"];


int length = temperature.length();
if(length==5)
{
  temperature.remove(length-1);
}

Serial.println(location);
Serial.println(weather);
Serial.println(temperature);
Serial.println(description);
Serial.println(temperature);
Serial.println(timeS);
int weatherID = idString.toInt();
printData(temperature, weatherID);

    }
    else {
      Serial.println("WiFi Disconnected");
    }
   
  
}
