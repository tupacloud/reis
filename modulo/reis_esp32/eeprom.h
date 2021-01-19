
#ifndef VARIABLES_EEPROM // header guards
#define VARIABLES_EEPROM

#include <EEPROM.h>

#define DEVICE_ID_POSITION   10 // deprecated ?
#define CLIENT_ID_POSITION   30
#define TOPIC_SBS_POSITION   50
#define MOM_ADDRS_POSITION   70
#define MACS_ADRS_POSITION   90
#define WBEE_CONF_POSITION   400

boolean toCommit = false;

void commitEEPROM();
boolean checkDeviceEEPROM(String uniqueCode);
void setEEPROM();
void writeString(int _add, String data);
void resetModuleToFactory();
void handleCommit();
void initDefaultDevice(String uniqueCode);
String getClientID();
boolean saveRecuo(int recuo);
boolean saveHmax(int hmax);
boolean saveMeasureDelay(int measureDelay);
boolean saveNotf(JsonArray& notf);
int readRecuo();
int readHmax();
int readMeasureDelay();
int readNotfSize();
void readNotf(int notf[]);

int readRecuo(){

  uint8_t val_ = EEPROM.read(WBEE_CONF_POSITION);
  int val = val_;
  
  return val;
}

int readHmax(){
  
  uint8_t val_ = EEPROM.read(WBEE_CONF_POSITION + 1);
  int val = val_;
  
  return val;
}

int readMeasureDelay(){
  
  uint8_t val_ = EEPROM.read(WBEE_CONF_POSITION + 2);
  int val = val_;
  
  return val;
}

int readNotfSize(){
  
  uint8_t val_ = EEPROM.read(WBEE_CONF_POSITION + 3);
  int val = val_;
  
  return val;
}

void readNotf(int notf[]){

  int pos = WBEE_CONF_POSITION + 4;
  for(int i=0; i<11; i++){

    uint8_t val = EEPROM.read(pos + i);
    notf[i] = val;
  }
}

boolean saveRecuo(int recuo){

  boolean taok = false;
  int recuo_ = readRecuo();

  if( recuo != recuo_ ){

    EEPROM.write(WBEE_CONF_POSITION    , recuo);
    taok = true;

    Recuo = recuo;
  }

  return taok;
}

boolean saveHmax(int hmax){
  
  boolean taok = false;
  int hmax_ = readHmax();

  if( hmax != hmax_ ){

    EEPROM.write(WBEE_CONF_POSITION    , hmax);
    taok = true;

    Hmax = hmax;
  }

  return taok;
}

boolean saveMeasureDelay(int measureDelay){
  
  boolean taok = false;
  int measureDelay_ = readMeasureDelay();

  if( measureDelay != measureDelay_ ){

    EEPROM.write(WBEE_CONF_POSITION    , measureDelay);
    taok = true;

    MeasureDelay = measureDelay;
  }

  return taok;
}

boolean saveNotf(JsonArray& notf){

  boolean taok = false;
  
  int size  = notf.size();
  int size_ = readNotfSize();

  int notf_[11];
  readNotf(notf_);

  /*
   * notf -> vetor com as porcentagens
   * ex: [20,50,90]
   * 
   * notf_ -> vetor com 0 e 1 mapeando as notificações salvas
   * ex:
   * [0,1,0,0,0,0,0,0,0,0,0] -> só temos nofificação de 10%
   * [1,0,0,0,0,0,0,0,0,0,0] -> só temos nofificação de 0%
   * [0,0,0,0,0,0,0,0,0,0,1] -> só temos nofificação de 100%
   * [0,1,0,1,0,0,1,0,0,1,0] -> temos nofificações em 10%, 30%, 60% e 90%
  */

  int pos = WBEE_CONF_POSITION + 4;

  // save values
  for(int i=0; i<size; i++){

    int val_ = notf[i];
    int val = val_/10;

    if( notf_[val] == 0 ){

      EEPROM.write(pos + val, 1);
      taok = true;
    }
  }

  // delete values
  for(int i=0; i<11; i++){

    int val = notf_[i];

    if( val == 1 ){

      boolean check = false;
      for(int j=0; j<size; j++){

        int val_ = notf[j];

        if( val * 10 == val_ ){

          check = true;
          break;
        }
      }

      if( !check ){

        EEPROM.write(pos + i, 0);
        taok = true;
      }
    }
  }

  if( taok ){

    EEPROM.write(pos - 1, size);
    NotfSize = size;

    updateNotf();
  }

  return taok;
}

void setConf(JsonObject& root){

  int recuo = root["conf"]["recuo"];
  int hmax  = root["conf"]["hmax"];

  int delay_ = root["conf"]["delay"];

  JsonArray& notf = root["conf"]["notf"];

  boolean taok1 = saveRecuo(recuo);
  boolean taok2 = saveHmax(hmax);
  boolean taok3 = saveMeasureDelay(delay_);
  boolean taok4 = saveNotf(notf);

  if( taok1 || taok2 || taok3 || taok4 ){

      commitEEPROM();
  }
  
}

void setOwn(JsonObject& root){

  String clientID  = root["own"];
  String clientID_ = getClientID();

  if( !clientID.equals(clientID_) ){

    writeString(CLIENT_ID_POSITION,clientID);
  }

  setConf(root);

  started = true;
}

void commitEEPROM(){
  
  toCommit = true;
}

boolean checkDeviceEEPROM(String uniqueCode){
  
  boolean taok = false;
  
  unsigned char buff[7];
  char signature[7];
  int temp[7];
  
  char* beetle = "beetle";
  
  for(int i=0; i<7; i++){
    temp[i]=EEPROM.read(i);
    buff[i]=temp[i];
    signature[i]=buff[i];
  }
  
  if(!strcmp(signature,beetle)==0){
    
    writeString(0,beetle);
    //writeString(DEVICE_ID_POSITION,uniqueCode);
    writeString(CLIENT_ID_POSITION,nullClientID);
    
  }else{
    taok = true;
  }
  
  return taok;
}

void setEEPROM(){

  EEPROM.begin(512);
}

void writeString(int _add, String data){
  int _size = data.length();
  int i;
  for(i=0;i<_size;i++){
    
    EEPROM.write(_add+i,data[i]);
  }
  EEPROM.write(_add+_size,'\0');   //Add termination null character for String Data
  
  //EEPROM.commit();
  commitEEPROM();
}

String getClientID(){
  
  int i;
  char data[20];
  int len=0;
  
  unsigned char k;
  k=EEPROM.read(CLIENT_ID_POSITION);
  
  while(k != '\0' && len<20){
        
    k=EEPROM.read(CLIENT_ID_POSITION+len);
    data[len]=k;
    len++;
  }
  
  data[len]='\0';
  return String(data);
}

void resetModuleToFactory(){
  
  String clearMem = "acab";
  writeString(0, clearMem);
}

void handleCommit(){
  
  if(toCommit){
    
    EEPROM.commit();
    toCommit = false;
  }
  delay(1); // alimenta o watchdog
}

void initDefaultDevice(String uniqueCode){

  EEPROM.write(WBEE_CONF_POSITION    , 25); // default recuo: centímetros
  EEPROM.write(WBEE_CONF_POSITION +1 , 75); // default hmax: centímetros
  EEPROM.write(WBEE_CONF_POSITION +2 , 60); // default measure delay: minutos

  EEPROM.write(WBEE_CONF_POSITION +3 , 0);  // default notification size

  for(int i = 0; i<10; i++){
    EEPROM.write(WBEE_CONF_POSITION + 4 + i, 0);  // default wBeetle notf values
  }

  /**
  EEPROM.write(WBEE_CONF_POSITION    , 40); // defaut wBeetle delay : minutos
  EEPROM.write(WBEE_CONF_POSITION + 1, 0);  // defaut wBeetle notf size
  
  for(int i = 0; i<9; i++){
    EEPROM.write(WBEE_CONF_POSITION + 2 + i, 0);  // defaut wBeetle notf values
  }
  
  EEPROM.write(WBEE_CONF_POSITION + 11, 120);  // defaut wBeetle bitola : centímetros
  /**/
  EEPROM.commit();
  
  if(factoryWiFi()){
    sendHttpRequest(getPushDeviceInfo(uniqueCode));
    disconnectWiFi(); 
  } 
}

#endif
