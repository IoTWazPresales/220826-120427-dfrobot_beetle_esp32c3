#include "WiFi.h"
#include "HTTPClient.h"
#include "Arduino_JSON.h"

#include "HTTP_Method.h"
/*
This example learns how to get weather information
*/

//Fill in the API Key you got
String openWeatherMapApiKey = "4de305d0a52ddaceaecba50a757e9968";
//Example:
//String openWeatherMapApiKey = "4de305d0a52ddaceaecba50a757e9968";

// Fill in your city name and country abbreviation
String city = "Johannesburg";
String countryCode = "ZA";

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

void getweather() {
  //Send HTTP get request
  
    //Check if WIFI is connected
    if(WiFi.status()== WL_CONNECTED){
      String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey;

      //Put the combined URL into the httpGETRequest function to get the text through HTTP get request.
      jsonBuffer = httpGETRequest(serverPath.c_str());
      Serial.println(jsonBuffer);

      //Store the parsed Json object value in the Jsonu buffer
      JSONVar myObject = JSON.parse(jsonBuffer);

      //Determine if the parsing was successful
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }

      Serial.print("JSON object = ");
      Serial.println(myObject);
      Serial.print("Temperature: ");
      //The obtained temperature is actually Kelvin.
      //Kelvin = Celsius + 273.15
      double c = myObject["main"]["temp"];
      c = c-273.15;
      Serial.println(c);
      Serial.print("Pressure: ");
      //myObject["main"]["pressure"], the front is the content of the quotation marks before {}, and the latter is the data after that quotation mark is read
      Serial.println(myObject["main"]["pressure"]);
      Serial.print("Humidity: ");
      Serial.println(myObject["main"]["humidity"]);
      Serial.print("Wind Speed: ");
      Serial.println(myObject["wind"]["speed"]);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
   
  
}

