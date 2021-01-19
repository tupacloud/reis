
String uniqueDeviceCode = "reis1312";
String nullClientID = "danonenone"; // 10 caracteres

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// Esse passo precisa ser automatizado - ex WiFiManager
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
const char* ssid = "Tenebrios";
const char* password = "r4r4l4lv";
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include <ArduinoJson.h>

#include <esp_task_wdt.h>
//variaveis que indicam o núcleo
static uint8_t taskCoreZero = 0;
static uint8_t taskCoreOne  = 1;

#include "stringArrayList.h";
stringArrayList httpQueue = stringArrayList();

void setConf(JsonObject& root);
void setOwn(JsonObject& root);

#include "handleWiFi.h"
#include "eeprom.h"
#include "mqtt.h"
#include "fun.h"
