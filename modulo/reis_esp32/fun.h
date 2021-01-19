
int getConfDelay = 3600000; // 1h em milisegundos
long timeGetConf = - getConfDelay;

void handleGetMyConf();
void getMyConf();

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
         input_ += "\"" + uniqueDeviceCode + "\"";
         input_ += "}";
         input_ += "}";

  String flushID = "%7B%22flush%22%3A%22wh1H99dTBbRp%5C%2FeM5vC%2BSv3ly%2B55FpkcCTNxSLgaFs4BKMEKtrdNyw0Ivg2n6Yw5jZrVaz2YplUPNnrDIivijiA%3D%3D%22%2C%22integrity%22%3A%22c18a5b7db56766271b382b28ed72c3d1%22%2C%22security_token%22%3A%226be14a9eebe5a8ae474ed58231bb59c7503897439e775d51ca2407ce9e39253b9ae28b12b868e13b4bbd42798721820ed3d9d4f6bccbdb8dcb0875ede3fe2f507370d5ba33bb4fcb8bff0a49906de7b613bd98b3c8cbab63e05e694e271f7970866082a0d4d6eaca242ccdcee70e1584e36dc262faaba29c025b2ad0c35acddb54451e489f194ef50ab2ad2d544b43189a8d46096309d7c4266ff2413820de11d3c222965fdf859c87407e896a612aa9032b2a12ce1c19bbf207cf69a2968957b05381a24ca66758051e015bf24bdee04927b75e9d8e1b2d1609b9545fba44fabff7b660415615b5e160e44fba870e6ae5836ca4725715a3ad4344d175366b18%22%7D";

  String flush_ = "?FLOW=" + flushID + "&INPUT=" + input_;

  timeGetConf = millis();
}
