
String uniqueDeviceCode = "reis1312";
String nullClientID = "danonenone"; // 10 caracteres

boolean started = false;

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// Esse passo precisa ser automatizado - ex WiFiManager
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
const char* ssid = "Tenebrios";
const char* password = "r4r4l4lv";
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#define PIN_TRIGGER   4
#define PIN_ECHO      5

float vsom = 0.034; // cm por microsegundo
int triggerDelay = 10; // microsegundo

int Recuo; // centímetros
int Hmax; // centímetros
int MeasureDelay; // minutos (tempo/delay para enviar medidas para o servidor)
int *Notf; // porcentagem
int NotfSize;

#include <ArduinoJson.h>

#include <esp_task_wdt.h>
//variaveis que indicam o núcleo
static uint8_t taskCoreZero = 0;
static uint8_t taskCoreOne  = 1;

#include "stringArrayList.h";
stringArrayList httpQueue = stringArrayList();

float lastMeasure = 0;
float measure = 0;

void setConf(JsonObject& root);
void setOwn(JsonObject& root);
void updateNotf();

#include "handleWiFi.h"
#include "eeprom.h"
#include "mqtt.h"
#include "fun.h"
