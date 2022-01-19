#include <Arduino.h>
#include <ArduinoJson.h>

String jsonData = "{\"loadcell\":\"12\",\"temp\":\"23\",\"data\":\"34\"}";

void setup() {
  Serial.begin(115200); 
  Serial.println(jsonData); 
  DynamicJsonDocument doc(1024); 

  DeserializationError error = deserializeJson(doc, jsonData); 

  if(error)
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
  }

  String newValue = "16";
  doc["data"] = newValue; 
  jsonData = doc.as<String>(); 
  jsonData = "[" + jsonData + "]";
  Serial.println(jsonData); 

  
}
void loop() {

}
