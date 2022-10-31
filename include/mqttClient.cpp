#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <string.h>
//https://www.e-tinkers.com/2020/01/do-you-know-arduino-sprintf-and-floating-point/
//Sends integer,long integer,float and double as strings 
//send integer and float as buffer
//subscribe to test/# to view
// Update these with values suitable for your network.
const char* ssid = "kronos";
const char* pass = "Cursed4252!";
const char* brokerUser = "warren.eliason";
const char* brokerPass = "123456";
const char* broker = "test.mosquitto.org";
const char* outTopic = "/warrenserver/out";

WiFiClient espClient;
PubSubClient client(espClient);
long currentTime, lastTime;
int count = 0;
char messages[50];


void setupWifi(){

delay(100);
Serial.print("\nConnecting to");
Serial.println(ssid);

WiFi.begin(ssid, pass);

while(WiFi.status() != WL_CONNECTED){
  delay(1000);
  Serial.print("-");
}
Serial.print("\nConnected to");
Serial.println(ssid);

}


void reconnect(){
  while(!client.connected()){
    Serial.print("nConnected to");
    Serial.println(broker);
    if(client.connect("koikoikoi", brokerUser, brokerPass)){
      Serial.print("\nConnected to");
      Serial.println(broker);
    }
    else{
      Serial.println("\nTrying to connect");
      delay(5000);
    }
  }
}
 

void setup()
{
  Serial.begin(115200);
  setupWifi();
  client.setServer(broker, 1883);




}

  void loop()
  {
    //
    if (!client.connected()){
      reconnect();

    }
    client.loop();

currentTime = millis();
if(currentTime - lastTime > 2000){
  count++;
  snprintf(messages, 75, "Count: %ld", count);
  Serial.print("Sending Messages: ");
  Serial.println(messages);
  client.publish(outTopic, messages);
  lastTime = millis();





}




  }
  //end while
    
  
