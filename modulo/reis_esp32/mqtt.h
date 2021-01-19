
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

WiFiClientSecure wifiClient;
PubSubClient client(wifiClient);

void setMqtt();
void connectMQTT();
void callback_MQTT(char* topic, byte* payload, unsigned int length);
void handleMqttPayload(String payload);

void handleMqttPayload(String payload){

  String payload_ = payload;
  
  StaticJsonBuffer<2000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(payload_);
  
  if(root.containsKey("own")){
    
    setOwn(root);  
  }

  jsonBuffer.clear();
}

void setMqtt(){

  strcpy(SUBSCRIBE,uniqueDeviceCode.c_str());

  connectWiFi((char *)ssid,(char *)password);
  connectMQTT();
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
    
    String pay = payloadStr;
    handleMqttPayload(payloadStr);    
  }

}
