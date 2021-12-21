#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "web.h"

WebServer server(80); 

const char * ssid = "Huan Nhi";
const char * pass = "19961996";

const int ledPin = 2; // GPIO2 

const int freq = 5000; // Hz 
const int ledChannel = 0; // Timer0
const int resolution = 8; // Timer 8 bit 

String severD = ""; 
void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, pass);
  Serial.begin(115200); 
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");

  }
  Serial.println(" "); 
  Serial.print("IP Address: "); 
  Serial.println(WiFi.localIP()); 

  ledcSetup(ledChannel, freq, resolution); 
  ledcAttachPin(ledPin, ledChannel);

  server.on("/", [] {
    server.send(200, "text/html", webpage); 
  }); 

  server.on("/onoff", [] {
    Serial.println("ONOFF");
    server.send(200, "text/html", webpage); 
  }); 

  server.on("/getdata", [] {
    server.send(200, "text/html", severD); 
  }); 


  server.on("/adcvalue", [] {
    String serverData = server.arg("adc"); // A123B
    int timA, timB = -1; 
    timA = serverData.indexOf("A"); 
    timB = serverData.indexOf("B"); 
    if(timA >= 0 && timB >= 0)
    {
      String value = serverData.substring(timA, timB + 1); 
      int pwm_value = value.toInt(); 
      Serial.printf("pwm_value: %d\n", pwm_value); 
      ledcWrite(2, pwm_value); 
    }
    Serial.println(serverData); 
    server.send(200, "text/html", webpage); 
  }); 
  server.begin();
}

int temp, humi, light = 0; 
uint32_t last_time = 0; 
void jsonData(int a, int b, int c); 
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient(); 
  if(millis() - last_time >= 2000)
  {
    temp++; 
    humi += 2; 
    light = random(1,5); 

    jsonData(temp, humi, light); 
    
    last_time = millis(); 
  }
}

void jsonData(int a, int b, int c)
{
  severD = ""; 
  severD ="{\"temp\":\""+String(a)+"\",\"humi\":\""+String(b)+"\",\"light\":\""+String(c)+"\"}";
  Serial.print("JsonData: "); 
  Serial.println(severD); 
}