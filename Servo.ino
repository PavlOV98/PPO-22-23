
#include "ArduinoJson.h"
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
const char* ssid = "ROBOT";
const char* password = "Robot1488";
#define HUM_PIN A0
#define SERVO D4
Servo myservo1;

//Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.1.102:8080";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;
float hg = 55;
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



void setup() {
  myservo1.attach(SERVO,544,2400);
  Serial.begin(115200);
  pinMode(HUM_PIN, INPUT);// configure D7 pin as an OUTPUT
  pinMode(SERVO, OUTPUT);
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
  if((millis()-timer)>30000)warning=false;
  hg = analogRead(HUM_PIN);
  hg = map(hg,0, 1024, 100, 0);
  Serial.print("Sensor value: ");
  Serial.println(hg);
  delay(1000);
if (isnan(hg)) {  // Проверка. Если не удается считать показания, выводится «Ошибка считывания», и программа завершает работу
    hg = 1000;
    
  } 



set ="{\"hg\":\"";
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
      Serial.print("HTTP answer code: ");
      Serial.println(httpanswer);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      Serial.print("servo: ");
      Serial.println(servo); 
      if(warning==false){
      switch(servo)
      {
          case 0:
          if(pos==c0){
             break;
          }
          if(pos>c0){
            for(int i=pos;i>c0;i-=ii){
            myservo1.write(i);
             if(analogRead(A0)>nagruzka){
              digitalWrite(D4,LOW); 
              pos=i;
                warning=true;
                timer=millis();
                break;
              }
            delay(delay_servo);
            }      
          }else{
            myservo1.write(c0);   
          }
          if(warning)break;
          pos=c0;
          delay(3000);
          digitalWrite(D4,LOW);         
                 break;     
          
          case 1:
          if(pos==c1){
             break;
          }
          if(pos>c1){
            for(int i=pos;i>c1;i-=ii){
            myservo1.write(i);
            
            if(analogRead(A0)>nagruzka){
              digitalWrite(D4,LOW); 
              pos=i;
                warning=true;
                timer=millis();
                break;
              }
            
            delay(delay_servo);
            }      
          }else{
            for(int i=pos;i<c1;i+=ii){
            myservo1.write(i); 
            
            if(analogRead(A0)>nagruzka){
              digitalWrite(D4,LOW); 
              pos=i;
                warning=true;
                timer=millis();
                break;
              }

            delay(delay_servo);
            }     
          }
          if(warning)break;
          pos=c1;
          delay(3000);
          digitalWrite(D4,LOW);                
                 break;
          
          case 2:
          if(pos==c2){
             break;
          }
                    if(pos>c2){
            for(int i=pos;i>c2;i-=ii){
            myservo1.write(i);
            
            if(analogRead(A0)>nagruzka){
              digitalWrite(D4,LOW); 
              pos=i;
                warning=true;
                timer=millis();
                break;
              }
              
            delay(delay_servo);
            }      
          }else{
            for(int i=pos;i<c2;i+=ii){
            myservo1.write(i);
            
            if(analogRead(A0)>nagruzka){
              digitalWrite(D4,LOW); 
              pos=i;
                warning=true;
                timer=millis();
                break;
              }
              
            delay(delay_servo);
            }     
          }
           if(warning)break;

          pos=c2;
          delay(3000);
          digitalWrite(D4,LOW);                      
                 break;
          
          case 3:
          if(pos==c3){
             break;
          }
                              if(pos>c3){
            for(int i=pos;i>c3;i-=ii){
            myservo1.write(i);
            
            if(analogRead(A0)>nagruzka){
              digitalWrite(D4,LOW); 
              pos=i;
                warning=true;
                timer=millis();
                break;
              }
            
            delay(delay_servo);
            }      
          }else{
            for(int i=pos;i<c3;i+=ii){
            myservo1.write(i);
            
            if(analogRead(A0)>nagruzka){
              digitalWrite(D4,LOW); 
              pos=i;
                warning=true;
                timer=millis();
                break;
              }
            
            delay(delay_servo);
            }     
          }
          if(warning)break;
          
          pos=c3; 
          delay(3000);
          digitalWrite(D4,LOW);   
                 break;
         
          case 4:
          if(pos==c4){
             break;
          }
                              if(pos>c4){
            for(int i=pos;i>c4;i-=ii){
            myservo1.write(i);
            
            if(analogRead(A0)>nagruzka){
              digitalWrite(D4,LOW); 
              pos=i;
                warning=true;
                timer=millis();
                break;
              }
              
            delay(delay_servo);
            }      
          }else{
            for(int i=pos;i<c4;i+=ii){
            myservo1.write(i);
            
            if(analogRead(A0)>nagruzka){
              digitalWrite(D4,LOW); 
              pos=i;
                warning=true;
                timer=millis();
                break;
              }
              
            delay(delay_servo);
            }     
          }
          if(warning)break;
          pos=c4 ;
          delay(3000);
          digitalWrite(D4,LOW);                
                 break;
         
      } 
      }
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
 
}
