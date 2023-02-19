
#include "ArduinoJson.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
const char* ssid = "ROBOT";
const char* password = "Robot1488";
#define POWER_PIN D3
#define SIGNAL_PIN A0
#define POMP D4
#define HUM_POWER D5
#define HUM_SIGNAL D2


//Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.1.102:8080";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;
int value = 0;
int level = 0;
int pomp = 0;
int hum = 0;
bool hum_start = 0;
String set ="";

void setup() {
  Serial.begin(115200);
  digitalWrite(HUM_SIGNAL, HIGH);
  digitalWrite(HUM_POWER, LOW);  
  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(HUM_POWER, LOW);
  pinMode(HUM_POWER, OUTPUT);
  pinMode(HUM_SIGNAL, OUTPUT);
  pinMode(SIGNAL_PIN, INPUT);// configure D7 pin as an OUTPUT
  pinMode(POMP, OUTPUT);
  digitalWrite(POWER_PIN, LOW);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
digitalWrite(POWER_PIN, HIGH); // turn the sensor ON
   delay(10); // wait 10 milliseconds
 value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(POWER_PIN, LOW); // turn the sensor OFF
 level =map(value,0,521,0,100);
  Serial.print("Sensor value: ");
  Serial.println(level);
delay(1000);

 if (isnan(level)){  // Проверка. Если не удается считать показания, выводится «Ошибка считывания», и программа завершает работу
    level = 100000;
    
  } 

set ="{\"wl\":\"";
set+=level;
set+="\"}";

Serial.println(set);

  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client,"http://192.168.1.102:8080/Thingworx/Things/wp/Services/IOS");
  
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
  
      // Specify content-type header
      http.addHeader("Content-Type", "application/json");
      http.addHeader("appKey", "c064b736-4939-45a6-9a8b-d0b63412702b");
      http.addHeader("Accept", "application/json");
      http.addHeader("Host", "192.168.1.102");         
      // Send HTTP POST request
      int httpResponseCode = http.POST(set);
      //
      String httpanswer = http.getString();
      StaticJsonDocument<300> parsed;
       DeserializationError error = deserializeJson(parsed, httpanswer);
      pomp = parsed["p"];
      hum = parsed["h"];
      Serial.print("HTTP answer code: ");
      Serial.println(httpanswer);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      Serial.print("pomp: ");
      Serial.println(pomp); 
      Serial.println(hum); 
       if(pomp == 0){
        digitalWrite(POMP, HIGH);
      }
      else{
        digitalWrite(POMP, LOW);
      } 
       if(hum == 0){
        digitalWrite(HUM_POWER, HIGH);
        hum_start = 0;
      }
      if((hum == 1)&&(hum_start == 0)){
        digitalWrite(HUM_POWER, LOW);
        delay(1000);
        digitalWrite(HUM_SIGNAL, LOW);
        delay(100);
        digitalWrite(HUM_SIGNAL, HIGH);
        hum_start = 1;
      }      
      
      // Free resources
      
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
 
}
