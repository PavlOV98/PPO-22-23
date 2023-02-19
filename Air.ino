/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  
  Code compatible with ESP8266 Boards Version 3.0.0 or above 
  (see in Tools > Boards > Boards Manager > ESP8266)
*/
#include "DHT.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Adafruit_Sensor.h>
#define DHTPIN D4
#define HUM_PIN A0
DHT dht(DHTPIN, DHT11);
const char* ssid = "ROBOT";
const char* password = "Robot1488";

//Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.1.102:8080";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;
float t = 0;
float hu =0;
float hg = 0;
String set ="";

void setup() {
  pinMode(HUM_PIN, INPUT);
  Serial.begin(115200);
  dht.begin();
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
  hu = dht.readHumidity();
  t = dht.readTemperature();
  hg = analogRead(HUM_PIN);
  hg = map(hg,0, 1024, 100, 0);

  delay(1000);

 if (isnan(hu) || isnan(t)) {  // Проверка. Если не удается считать показания, выводится «Ошибка считывания», и программа завершает работу
    t = 1000;
    hu = 1000;
    
  }  


  
  Serial.print("Влажность воздуха: ");
  Serial.print(hu);
  Serial.print(" %\t");
  Serial.print("Температура: ");
  Serial.print(t);
  Serial.println(" *C ");
  Serial.print("Влажность почвы: ");
  Serial.println(hg);
  Serial.print(" %");
set ="{\"t\":\"";
set+=t;
set+="\",\"ha\":\"";
set+=hu;
set+="\",\"hg\":\"";
set+=hg;
set+="\"}";

Serial.println(set);

  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client,"http://192.168.1.102:8080/Thingworx/Things/air2/Services/IOS/");
  
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
      Serial.print("HTTP answer code: ");
      Serial.println(httpanswer);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
