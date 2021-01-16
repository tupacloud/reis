

#ifndef VARIABLES_HTTPRE // header guards
#define VARIABLES_HTTPRE

#include <HTTPClient.h>

String server = "https://api.tupacloud.com/";
String join = "?FLOW=";

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void sendHttpRequest(String cmd);
String encode(char *string);
String getPushDeviceInfo(String uniqueDeviceCode);
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

String getPushDeviceInfo(String uniqueDeviceCode){
  
  Serial.println("AP MAC: " + String(WiFi.softAPmacAddress()));
  uint8_t macAddr[6];
  WiFi.softAPmacAddress(macAddr);

  int vec[6];

  for(int i=0; i<6; i++){
    vec[i] = macAddr[i];
    Serial.println(vec[i]);
  } 
  
  String cmd =  "var file = {};\n";
         cmd += "file._id = \"";
         cmd += uniqueDeviceCode + "\"\n";
         cmd += "file.own = \"danone\";\n";
         cmd += "file.macAdd = [";
         cmd += String(vec[0]) + ",";
         cmd += String(vec[1]) + ",";
         cmd += String(vec[2]) + ",";
         cmd += String(vec[3]) + ",";
         cmd += String(vec[4]) + ",";
         cmd += String(vec[5]);
         cmd += "];\n";
         cmd += "\n";
         cmd += "setMongo(\"besouro\",\"waterBeetles\");\n";
         cmd += "\n";
         cmd += "mongo.insert(file).then(function(items){\n";
         cmd += "  besouro.print(\"modulo inserido com sucesso\");\n";
         cmd += "});";
  
  return cmd;
}

void sendHttpRequest(String cmd){
  
  //Serial.println(cmD);

  String url = server + join + encode((char *)cmd.c_str());;

  HTTPClient http;

  http.begin(url.c_str());

  int httpResponseCode = http.GET();
  if (httpResponseCode>0) {
    
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    
    /**
    delay(2000);
    sendHttpRequest(cmd);
    /**/
  }
  // Free resources
  http.end();
  /**/
}

String encode(char *string){

  // 17 caracteres
  char special[] = {';',':','@','&','=','+','$',',','/','\\','?','#','[',']',' ','\n','"'};

  String encoded = "";

  int i=0;
  while(string[i] != '\0'){

    boolean ok = false;
    int j = 0;
    for(j=0; j<17; j++){

      if(string[i] == special[j]){

        ok = true;
        break;
      }
    }

    if(ok){
        char converted[3];

        sprintf((char*)(converted),"%02X", string[i]);
        converted[2] = '\0';

        encoded += "%";
        encoded += converted;
      }else{

        encoded += string[i];
      }

    i ++;
  }

  return encoded;
}


#endif
