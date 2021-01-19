
#include "header.h"

void setup() {

  Serial.begin(115200);

  setEEPROM();
  //resetModuleToFactory();
  /**/
  if( !checkDeviceEEPROM(uniqueDeviceCode) ){
    initDefaultDevice(uniqueDeviceCode);
  }
  /**/

  initModule();
  setMqtt();

  xTaskCreatePinnedToCore(
                    loopCoreZero,   /* função que implementa a tarefa */
                    "loopCoreZero",  /* nome da tarefa */
                    10000,         /* número de palavras a serem alocadas para uso com a pilha da tarefa */
                    NULL,          /* parâmetro de entrada para a tarefa (pode ser NULL) */
                    1,             /* prioridade da tarefa (0 a N) */
                    NULL,          /* referência para a tarefa (pode ser NULL) */
                    taskCoreZero);   /* Núcleo que executará a tarefa */
  delay(500);
}

void loop() {

}

void loopCoreZero(void * pvParameters ){
  
  while(true){

    if(started){
     
      handleHttpRequest();
      handleGetMyConf();
      handleMeasure();
      handleSendMeasure(); 
    }
    handleCommit();
  }
  
}
