#ifndef FREE_RTOS_H
#define FREE_RTOS_H
#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>
WebServer server(80); 


#define f_delay(x)   vTaskDelay(x / portTICK_PERIOD_MS)

TaskHandle_t WebHandle; 
TaskHandle_t SensorHande; 
TaskHandle_t IoHandle; 

void WebTask(void * arg); 
void SensorTask(void * arg); 
void IoTask(void * arg); 

void server_handle(); 
void server_init(); 

const char * ssid = "Tran Thanh"; 
const char * pass = "12345678"; 
void freertos_init()
{
    Serial.begin(115200);

    WiFi.mode(WIFI_STA); 
    WiFi.begin(ssid, pass); 
    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print("."); 
        delay(500); 
    }
    Serial.println(" "); 
    Serial.println(WiFi.localIP());

    xTaskCreatePinnedToCore(WebTask, "task 01", 15000, NULL, 6, &WebHandle, 0);

    xTaskCreatePinnedToCore(SensorTask, "task 02", 15000, NULL, 6, &SensorHande, 1);
    xTaskCreatePinnedToCore(IoTask, "task 03", 15000, NULL, 6, &IoHandle, 1);
    server_init(); 

}

void WebTask(void * arg)
{
    while (1)
    {
        server_handle(); 
        f_delay(1); 
    }
    
}

void SensorTask(void * arg)
{
    while (1)
    {
        /* code */
    }
}

void IoTask(void * arg)
{
    while (1)
    {
        /* code */
    }
}


///-------------------------------------------------------------
void server_init()
{
    server.on("/", [] {
        server.send(200, "text/html", " "); 
    }); 
}

void server_handle()
{
    server.handleClient(); 
}




#endif 