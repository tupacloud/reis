
int getConfDelay = 3600000; // 1h em milisegundos
long timeGetConf = - getConfDelay;

int getMeasureDelay = 10000;
long timeGetMeasure = - getMeasureDelay;

long timeSendMeasure = - MeasureDelay;

void handleGetMyConf();
void getMyConf();
void initModule();
void handleMeasure();
void getMeasure();
float readUltrasonicDistance();
void handleNotification();
void sendNotification(int trigger, String status_);
void handleSendMeasure();
void sendMeasure();

void sendMeasure(){

  String input_  = "{\"payload\":";
         input_ += "{";
         input_ += "\"mid\":";
         input_ += "\"" + uniqueDeviceCode + "\"";
         input_ += ",";
         input_ += "\"cid\":";
         input_ += "\"" + getClientID() + "\"";
         input_ += ",";
         input_ += "\"measure\":";
         input_ += String(measure);
         input_ += "}";
         input_ += "}";

  String flushID = "blablabla";

  String flush_ = "?FLOW=" + flushID + "&INPUT=" + input_;

  httpQueue.add_string((char *)flush_.c_str());

  timeSendMeasure = millis();
}

void sendNotification(int trigger, String status_){
  
  String input_  = "{\"payload\":";
         input_ += "{";
         input_ += "\"mid\":";
         input_ += "\"" + uniqueDeviceCode + "\"";
         input_ += ",";
         input_ += "\"cid\":";
         input_ += "\"" + getClientID() + "\""; 
         input_ += ",";
         input_ += "\"trigger\":";
         input_ += trigger;
         input_ += ",";
         input_ += "\"status\":";
         input_ += "\"";
         input_ += status_;
         input_ += "\"";
         input_ += "}";
         input_ += "}";

  String flushID = "blablabla";

  String flush_ = "?FLOW=" + flushID + "&INPUT=" + input_;

  httpQueue.add_string((char *)flush_.c_str());

}

void handleNotification(){
  
  for(int i=0; i<NotfSize; i++){

    int trigger = Notf[i];

    if( lastMeasure > trigger && measure < trigger ){

      sendNotification(trigger, "descendo");
      break;
    }

    if( lastMeasure < trigger && measure > trigger ){

      sendNotification(trigger, "subindo");
      break;
    }
  }
}

void handleSendMeasure(){
  
  long timeNow = millis();
  if(timeNow - timeSendMeasure > MeasureDelay) sendMeasure();
  delay(1); // alimenta o watchdog
}

float readUltrasonicDistance(){

  // Clear the trigPin by setting it LOW:
  digitalWrite(PIN_TRIGGER, LOW);
  
  delayMicroseconds(10);
  // Trigger the sensor by setting the trigPin high for "triggerDelay" microseconds:
  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(triggerDelay);
  digitalWrite(PIN_TRIGGER, LOW);
  
  // Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds:
  long duration = pulseIn(PIN_ECHO, HIGH);

  // Calculate the distance:
  float distance = duration * vsom / 2;

  return distance;
}

void getMeasure(){

  int N = 10;

  int count_1 = 0;
  int count_2 = 0;
  int medidas[N];

  do{

    int dist = readUltrasonicDistance();
    //Serial.println("Dist " + String(dist));

    if(dist <= Recuo + Hmax&& dist >= Recuo){

      medidas[count_1] =  dist;
      count_1 ++;
    }

    count_2 ++;
    delay(20);
    
  }while( count_1<N && count_2<2*N );

  //Serial.println("Medidas coletadas. Count: " + String(count_1));

  if(count_1 != 0){

    if(count_1 < N){
     
     for(int i=count_1; i<N; i++){
        medidas[i] = medidas[count_1-1];
      } 
    }

    float soma = 0;
    for(int i=0; i<N; i++){
      soma += medidas[i];
    }

    float media = soma/N;

    lastMeasure = measure; 
    measure = media;

    handleNotification();
    
    //Serial.println("Measure: " + String(measure) + "%" + " | " + String(media));
  }

  timeGetMeasure = millis();
}

void handleMeasure(){

  long timeNow = millis();
  if(timeNow - timeGetMeasure > getMeasureDelay) getMeasure();
  delay(1); // alimenta o watchdog
}

void updateNotf(){

   NotfSize = readNotfSize();

  if(Notf!=NULL)
  free(Notf);
  Notf = (int*) calloc(NotfSize,sizeof(int));

  int notf[11];
  readNotf(notf);

  int count = 0;
  for(int i=0; i<11; i++){

    if( notf[i] == 1 ){

      Notf[count] = i * 10;
      count ++;
    }
  }
}

void initModule(){

  Recuo = readRecuo();
  Hmax = readHmax();
  MeasureDelay = readMeasureDelay();

  updateNotf();

  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  String clientID = getClientID();

  if( !clientID.equals(nullClientID) ){

    started = true;
  }
}

void handleGetMyConf(){

  String clientID = getClientID();
  boolean taok = !clientID.equals(nullClientID);

  if(taok){
  
    long timeNow = millis();
    if(timeNow - timeGetConf > getConfDelay) getMyConf();    
  }

  delay(1); // alimenta o watchdog
    
}

void getMyConf(){

  Serial.println("getMyConf");

  String input_  = "{\"payload\":";
         input_ += "{";
         input_ += "\"mid\":";
         input_ += "\"" + uniqueDeviceCode + "\"";
         input_ += ",";
         input_ += "\"cid\":";
         input_ += "\"" + getClientID() + "\"";
         input_ += "}";
         input_ += "}";

  String flushID = "%7B%22flush%22%3A%22wh1H99dTBbRp%5C%2FeM5vC%2BSv3ly%2B55FpkcCTNxSLgaFs4BKMEKtrdNyw0Ivg2n6Yw5jZrVaz2YplUPNnrDIivijiA%3D%3D%22%2C%22integrity%22%3A%22c18a5b7db56766271b382b28ed72c3d1%22%2C%22security_token%22%3A%226be14a9eebe5a8ae474ed58231bb59c7503897439e775d51ca2407ce9e39253b9ae28b12b868e13b4bbd42798721820ed3d9d4f6bccbdb8dcb0875ede3fe2f507370d5ba33bb4fcb8bff0a49906de7b613bd98b3c8cbab63e05e694e271f7970866082a0d4d6eaca242ccdcee70e1584e36dc262faaba29c025b2ad0c35acddb54451e489f194ef50ab2ad2d544b43189a8d46096309d7c4266ff2413820de11d3c222965fdf859c87407e896a612aa9032b2a12ce1c19bbf207cf69a2968957b05381a24ca66758051e015bf24bdee04927b75e9d8e1b2d1609b9545fba44fabff7b660415615b5e160e44fba870e6ae5836ca4725715a3ad4344d175366b18%22%7D";

  String flush_ = "?FLOW=" + flushID + "&INPUT=" + input_;

  httpQueue.add_string((char *)flush_.c_str());

  timeGetConf = millis();
}

//
