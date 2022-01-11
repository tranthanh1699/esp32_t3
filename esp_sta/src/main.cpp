#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "web.h"

WebServer server(8080); 

const char * ssid = "Tran Thanh";
const char * pass = "12345678";

IPAddress apIP(192, 168, 16, 2); 
IPAddress gateway(192, 168, 16, 2); 
IPAddress subnet(255, 255, 255, 0); 

String severD = ""; 

void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500); 

  }
  
  // WiFi.mode(WIFI_AP);
  // WiFi.softAP(ssid, pass);
  // delay(2000); 
  // WiFi.softAPConfig(apIP, gateway, subnet); 
  Serial.begin(115200); 

  Serial.println(" "); 
  Serial.print("IP Address: "); 
  // Serial.println(WiFi.softAPIP()); // 192.168.4.1
  Serial.println(WiFi.localIP()); 
  
  server.on("/", [] {
    server.send(200, "text/html", webpage); 
  }); 
  server.on("/test", [] {
    Serial.println("Request test"); 
    Serial.println(server.arg("testcode")); 
    server.send(200, "text/html", webpage); 
  }); 

  server.begin();
}
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient(); 
}
