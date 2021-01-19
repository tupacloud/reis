

#ifndef VARIABLES_HTTPRE // header guards
#define VARIABLES_HTTPRE

#include <HTTPClient.h>

//String server = "https://api.tupacloud.com/";
String server = "https://mushroom.api.tupacloud.com/";
String join = "?FLOW=";

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void sendHttpRequest(String flush_);
void queueHttpRequest(String flush_);
String encode(char *string);
String getPushDeviceInfo(String uniqueDeviceCode_);
void handleHttpRequest();
void handleHttpReply(String payload);
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void handleHttpReply(String payload){

  String payload_ = payload;
  
  StaticJsonBuffer<2000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(payload_);

  if(root.containsKey("conf")){
    
    setConf(root);  
  }
  
  jsonBuffer.clear();
}

void handleHttpRequest(){

  if(httpQueue.get_size()>0){
      
      queueHttpRequest(httpQueue.get_string(0));
      
      Serial.println();
      Serial.print("Buffer httpRequest size: ");
      Serial.println(httpQueue.get_size());
  }
  delay(1);
}

String getPushDeviceInfo(String uniqueDeviceCode_){

  /**
  Serial.println("AP MAC: " + String(WiFi.softAPmacAddress()));
  uint8_t macAddr[6];
  WiFi.softAPmacAddress(macAddr);

  int vec[6];

  for(int i=0; i<6; i++){
    vec[i] = macAddr[i];
    Serial.println(vec[i]);
  }
  /**/
  
  String input_  = "{\"payload\":";
         input_ += "{";
         input_ += "\"moduleID\":";
         input_ += "\"" + uniqueDeviceCode_ + "\"";
         input_ += "}";
         input_ += "}";

  String flushID = "%7B%22flush%22%3A%22wh1H99dTBbRp%5C%2FeM5vC%2BSv3ly%2B55FpkcCTNxSLgaFs4BKMEKtrdNyw0Ivg2n6Yw5jZrVaz2YplUPNnrDIivijiA%3D%3D%22%2C%22integrity%22%3A%22c18a5b7db56766271b382b28ed72c3d1%22%2C%22security_token%22%3A%226be14a9eebe5a8ae474ed58231bb59c7503897439e775d51ca2407ce9e39253b9ae28b12b868e13b4bbd42798721820ed3d9d4f6bccbdb8dcb0875ede3fe2f507370d5ba33bb4fcb8bff0a49906de7b613bd98b3c8cbab63e05e694e271f7970866082a0d4d6eaca242ccdcee70e1584e36dc262faaba29c025b2ad0c35acddb54451e489f194ef50ab2ad2d544b43189a8d46096309d7c4266ff2413820de11d3c222965fdf859c87407e896a612aa9032b2a12ce1c19bbf207cf69a2968957b05381a24ca66758051e015bf24bdee04927b75e9d8e1b2d1609b9545fba44fabff7b660415615b5e160e44fba870e6ae5836ca4725715a3ad4344d175366b18%22%7D";

  String flush_ = "?FLOW=" + flushID + "&INPUT=" + input_;
  
  return flush_;
}

void sendHttpRequest(String flush_){
  
  String url = server + flush_;
  
  HTTPClient http;

  http.begin(url.c_str());

  int httpResponseCode = http.GET();
  
  if (httpResponseCode == 200) {
    
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);

    handleHttpReply(payload);
  }
  else {
    
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
  
}

void queueHttpRequest(String flush_){

  String url = server + flush_;
  
  HTTPClient http;

  http.begin(url.c_str());

  int httpResponseCode = http.GET();
  
  if (httpResponseCode == 200) {
    
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
    
    handleHttpReply(payload);

    httpQueue.remove_item(0);
  }
  else {
    
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);

    String payload = http.getString();
    Serial.println(payload);
  }
  // Free resources
  http.end();
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
