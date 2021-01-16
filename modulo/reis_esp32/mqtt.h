
// MYQTTHUB

#define MQTT_BROKER       "node02.myqtthub.com"
#define MQTT_BROKER_PORT  8883
#define MQTT_USERNAME     "moduleREIS"
#define MQTT_KEY          "negulosocarente"
#define MQTT_CLIENT       "id_1312"

char SUBSCRIBE[100];

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

WiFiClientSecure wifiClient;
PubSubClient client(wifiClient);

void setMqtt();
void connectWiFi();
void connectMQTT();
void callback_MQTT(char* topic, byte* payload, unsigned int length);

void setMqtt(){

  strcpy(SUBSCRIBE,uniqueDeviceCode.c_str());

  connectWiFi();
  connectMQTT();
}

void connectWiFi(){
  if (WiFi.status() == WL_CONNECTED) {
     return;
  }
        
  Serial.println("Conectando-se na rede: " + String(ssid) + " - Aguarde!");
  WiFi.begin(ssid, password); // Conecta na rede WI-FI

  int ResetTime = 10000;
  long time1 = millis();
  long time2;
  while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.print(".");
      time2 = millis();
      if(time2-time1>ResetTime){
        ESP.restart();
      }
  }
  
  Serial.println();
  Serial.println(String(ssid) + " - Conexão estabelecida - Ip: " + String(WiFi.localIP()));
  Serial.println();
}

void connectMQTT(){

  client.setServer(MQTT_BROKER, MQTT_BROKER_PORT);
  client.setCallback(callback_MQTT);

  uint16_t connectionDelay = 5000;
  while (!client.connected()){

    Serial.printf("Trace   : Attempting MQTT connection...\n");
    
    if (client.connect(MQTT_CLIENT, MQTT_USERNAME, MQTT_KEY)){
      
      Serial.printf("Trace   : Connected to Broker.\n");

      /* Subscription to your topic after connection was succeeded.*/
      //MQTTSubscribe(TOPIC);
      Serial.print("Subscribe - " + String(SUBSCRIBE) + " : ");
      Serial.println( client.subscribe( SUBSCRIBE ) );

    }else{
      
      Serial.printf("Error!  : MQTT Connect failed, rc = %d\n", client.state());
      Serial.printf("Trace   : Trying again in %d msec.\n", connectionDelay);
      delay(connectionDelay);
    }
  }
}

void callback_MQTT(char* topic, byte* payload, unsigned int length){
  
  /**/
  char payloadStr[length + 1];
  memset(payloadStr, 0, length + 1);
  strncpy(payloadStr, (char*)payload, length);
  
  Serial.printf("DataCallback - Topic : [%s]\n", topic);
  Serial.printf("Payload : %s\n\n", payloadStr);
  /**/

  if( strcmp(topic,SUBSCRIBE)==0){
    
    //String pay = payloadStr;
    //handleMqttPayload(payloadStr);    
  }

}
