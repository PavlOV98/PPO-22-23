
#include "ArduinoJson.h"
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
const char* ssid = "ROBOT";
const char* password = "Robot1488";
#define SERVO D4
Servo myservo1;

int zakr=1000;
int otkr=2000;
int st=1500;
int ugol_0=938;
int ugol_30=860;
int ugol_45=728;
int ugol_90=532;
int ugol_110=452;
int analog=0;

//Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.1.102:8080";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;
int pos = 0;
int servo = 0;
String set ="";
int delay_servo=35;
int ii=2;
int delay_servo_case=3000;
int c0=8;
int c1=40;
int c2=60;
int c3=115;
int c4=133;
long timer=0;
bool warning=false;
int nagruzka=0;
int servo_liv = 1;



void setup() {
  myservo1.attach(SERVO,544,4800);
  Serial.begin(115200);
  //pinMode(SERVO_READ, INPUT);// configure D7 pin as an OUTPUT
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
 // if((millis()-timer)>30000)warning=false;
   



set ="{\"servo_liv\":\"";
set+=servo_liv;;
set+="\"}";

Serial.println(set);

  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client,"http://192.168.1.102:8080/Thingworx/Things/Servo/Services/IOS");
  
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
      servo = parsed["ass"];
      servo=int(servo);
      Serial.print("HTTP answer code: ");
      Serial.println(httpanswer);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      Serial.print("servo: ");
      Serial.println(servo);
      
  
     
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
  // if(warning==false){
      switch(servo)
      {
          case 0:
          analog=analogRead(A0);
if(analog<ugol_0-4){
myservo1.writeMicroseconds(zakr);
delay(22);
myservo1.writeMicroseconds(1500);
delay(100);
  while(analog<ugol_0-4){
  myservo1.writeMicroseconds(zakr);
  delay(18);
  myservo1.writeMicroseconds(1500);
  analog=analogRead(A0);
  Serial.print(" d ");
  Serial.println(analog);
  delay(100);
  }
}  
break;
          
          case 1:
          analog=analogRead(A0);
          if(analog<ugol_30-4){
myservo1.writeMicroseconds(zakr);
delay(22);
myservo1.writeMicroseconds(1500);
delay(100);
  while(analog<ugol_30-4){
  myservo1.writeMicroseconds(zakr);
  delay(18);
  myservo1.writeMicroseconds(1500);
  analog=analogRead(A0);
  Serial.print(" d ");
  Serial.println(analog);
  delay(100);
  }
}else if(analog>ugol_30+4){
myservo1.writeMicroseconds(otkr);
delay(22);
myservo1.writeMicroseconds(1500);
delay(100);
  while(analog>ugol_30+4){
  myservo1.writeMicroseconds(otkr);
  delay(18);
  myservo1.writeMicroseconds(1500);
  analog=analogRead(A0);
  Serial.print(" d ");
  Serial.println(analog);
  delay(100);
  }
}
break;
          
          case 2:
          analog=analogRead(A0);
         if(analog<ugol_45-4){
myservo1.writeMicroseconds(zakr);
delay(22);
myservo1.writeMicroseconds(1500);
delay(100);
  while(analog<ugol_45-4){
  myservo1.writeMicroseconds(zakr);
  delay(18);
  myservo1.writeMicroseconds(1500);
  analog=analogRead(A0);
  Serial.print(" d ");
  Serial.println(analog);
  delay(100);
  }
}else if(analog>ugol_45+4){
myservo1.writeMicroseconds(otkr);
delay(22);
myservo1.writeMicroseconds(1500);
delay(100);
  while(analog>ugol_45+4){
  myservo1.writeMicroseconds(otkr);
  delay(18);
  myservo1.writeMicroseconds(1500);
  analog=analogRead(A0);
  Serial.print(" d ");
  Serial.println(analog);
  delay(100);
  }
}
break;
          
          case 3:
          analog=analogRead(A0);
         if(analog<ugol_90-8){
myservo1.writeMicroseconds(zakr);
delay(22);
myservo1.writeMicroseconds(1500);
delay(100);
  while(analog<ugol_90-8){
  myservo1.writeMicroseconds(zakr);
  delay(18);
  myservo1.writeMicroseconds(1500);
  analog=analogRead(A0);
  Serial.print(" d ");
  Serial.println(analog);
  delay(100);
  }
}else if(analog>ugol_90+8){
myservo1.writeMicroseconds(otkr);
delay(22);
myservo1.writeMicroseconds(1500);
delay(100);
  while(analog>ugol_90+8){
  myservo1.writeMicroseconds(otkr);
  delay(18);
  myservo1.writeMicroseconds(1500);
  analog=analogRead(A0);
  Serial.print(" d ");
  Serial.println(analog);
  delay(100);
  }
}
break;
         
          case 4:
         analog=analogRead(A0);
        if(analog>ugol_110+8){
myservo1.writeMicroseconds(otkr);
delay(22);
myservo1.writeMicroseconds(1500);
delay(100);
  while(analog>ugol_110+8){
  myservo1.writeMicroseconds(otkr);
  delay(18);
  myservo1.writeMicroseconds(1500);
  analog=analogRead(A0);
  Serial.print(" d ");
  Serial.println(analog);
  delay(100);
  }
}
break;
         
      } 
      //}
 
}
