
#ifndef VARIABLES_WIFI // header guards
#define VARIABLES_WIFI

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// Factory WiFi
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#include <WiFi.h>
#include "httpRequest.h"

const char* ssid_fac = "Tenebrios";
const char* password_fac = "r4r4l4lv";
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
boolean factoryWiFi();
void disconnectWiFi();
boolean connectWiFi(char* ssid, char* key);
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

boolean connectWiFi(char* ssid, char* key){
  
  /**/
  if (WiFi.status() == WL_CONNECTED) {
   return true;
  }
  /**/
    
  Serial.println("Conectando-se na rede: " + String(ssid) + " - Aguarde!");
  WiFi.begin(ssid, key); // Conecta na rede WI-FI

  int ResetTime = 10000;
  long time1 = millis();
  long time2;
  while (WiFi.status() != WL_CONNECTED) {
    
    delay(100);
    Serial.print(".");
    time2 = millis();
    if(time2-time1>ResetTime){
      
    return false;
    delay(500);
    ESP.restart();
    }
  }

  Serial.println();
  Serial.println(String(ssid) + " - Conexão estabelecida - Ip: " + String(WiFi.localIP()));
  Serial.println();
  
  return true;
}

void disconnectWiFi(){
  
  WiFi.disconnect();
}

boolean factoryWiFi(){
  
  int n = WiFi.scanNetworks();
  boolean taok = false;
  
  //Serial.printf("Avaliable WiFi networks\n<Num> <SSID> <RSSI>\n");
  for(int i=0; i<n; i++){
    
    //Serial.printf("%d - %s\t: %d\n",i+1,WiFi.SSID(i),WiFi.RSSI(i));
    if(strcmp(ssid_fac,WiFi.SSID(i).c_str())==0){
      
      taok = true;
      break;
    }
  }
  
  WiFi.scanDelete();
  
  if(taok){
    
    return connectWiFi((char *)ssid_fac,(char *)password_fac);
  }
  
  return false;
}


#endif
