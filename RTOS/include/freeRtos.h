#ifndef FREE_RTOS_H
#define FREE_RTOS_H
#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>
WebServer server(80); 


#define f_delay(x)   vTaskDelay(x / portTICK_PERIOD_MS)
#define BIT_0 (1 << 0)

TaskHandle_t WebHandle; 
TaskHandle_t SensorHande; 
TaskHandle_t IoHandle; 
QueueHandle_t SensorDataHandle; 
EventGroupHandle_t xEvent; 


#pragma pack(1)
typedef struct
{
    uint8_t temp;
    uint8_t humi; 
    uint8_t uv;
}SersorData_t; 

#pragma pack()


void WebTask(void * arg); 
void SensorTask(void * arg); 
void IoTask(void * arg); 

void server_handle(); 
void server_init(); 

const char * ssid = "Tran Thanh"; 
const char * pass = "12345678"; 

String jsonData; 

void freertos_init()
{
    Serial.begin(115200);
    Serial.printf("Size of Struct: %d\n", sizeof(SersorData_t )); 
    SensorDataHandle = xQueueCreate(10, sizeof(SersorData_t )); 

    xEvent = xEventGroupCreate(); 

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
    SersorData_t data; 
    while (1)
    {
        data.temp++; 
        data.humi += 2; 
        data.uv += 3; 
        xQueueSend(SensorDataHandle, &data, 1000); 
        f_delay(3000 / portTICK_PERIOD_MS); 
    }
}

void IoTask(void * arg)
{
    pinMode(2, OUTPUT); 
    while (1)
    {
        EventBits_t xBit = xEventGroupWaitBits(xEvent, BIT_0, pdTRUE, pdFALSE, portMAX_DELAY); 

        if((xBit & BIT_0) == BIT_0)
        {
            digitalWrite(2, !digitalRead(2)); 
        }
    }
}


///-------------------------------------------------------------
void server_init()
{
    server.on("/", [] {
        server.send(200, "text/html", ""); 
    }); 

    server.on("/toggleled", [] {
        server.send(200, "text/html", ""); 
        xEventGroupSetBits(xEvent, BIT_0); 
    });

    server.on("/data", [] {
        SersorData_t data; 
        xQueueReceive(SensorDataHandle, &data, 1000 / portTICK_PERIOD_MS); 

        jsonData = "{\"temp\":\""+String(data.temp)+"\",\"humi\":\""+String(data.humi)+"\",\"uv\":\""+String(data.uv)+"\"}";

        server.send(200, "text/html", jsonData); 
    }); 

    server.begin(); 

}

void server_handle()
{
    server.handleClient(); 
}




#endif 