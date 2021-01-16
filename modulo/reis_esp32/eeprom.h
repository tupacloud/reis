
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
void writeString(int _add,String data);
void resetModuleToFactory();
void handleCommit();
void initDeviceInServer(String uniqueCode);

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
    
  }else{
    taok = true;
  }
  
  return taok;
}

void setEEPROM(){

  EEPROM.begin(512);
}

void writeString(int _add,String data){
  int _size = data.length();
  int i;
  for(i=0;i<_size;i++){
    
    EEPROM.write(_add+i,data[i]);
  }
  EEPROM.write(_add+_size,'\0');   //Add termination null character for String Data
  EEPROM.commit();
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

void initDeviceInServer(String uniqueCode){
          
  EEPROM.write(WBEE_CONF_POSITION    , 40); // defaut wBeetle delay : minutos
  EEPROM.write(WBEE_CONF_POSITION + 1, 0);  // defaut wBeetle notf size
  
  for(int i = 0; i<9; i++){
    EEPROM.write(WBEE_CONF_POSITION + 2 + i, 0);  // defaut wBeetle notf values
  }
  
  EEPROM.write(WBEE_CONF_POSITION + 11, 120);  // defaut wBeetle bitola : centímetros
  
  EEPROM.commit();
  
  if(factoryWiFi()){
    sendHttpRequest(getPushDeviceInfo(uniqueCode));
    disconnectWiFi(); 
  } 
}

#endif
