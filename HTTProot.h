String httpServerRequest(String request) {
  String response="";
  static String challenge=String(random(1000000000));
  static uint64_t challengeTimer=millis();

  if (request.indexOf("/getChallenge")>=0) { response=String(random(1000000000)); challenge=response; challengeTimer=millis(); }

  else if (request.indexOf("/getVoltage")>=0) {
    response+=String(voltage.peak[0],1) + ",";
    response+=String(voltage.rms[0],1) + ",";
    response+=String(voltage.frequency[0],1) + ",";
    response+=String(voltage.condition[0]) + ",";
    response+=String((millis()-voltage.timer[0])/1000) + ",";
    response+=String(voltage.peak[1],1) + ",";
    response+=String(voltage.rms[1],1) + ",";
    response+=String(voltage.frequency[1],1) + ",";
    response+=String(voltage.condition[1]) + ",";
    response+=String((millis()-voltage.timer[1])/1000); }

  else if (request.indexOf("/getRelay")>=0) {
    response+=String(relay.state[0]) + ",";
    response+=String(relay.state[1]); }

  else if (request.indexOf("/setRelay")>=0) {
    int a=request.indexOf(",")+1; int b=request.indexOf(",",a)+1;
    if (a>0 && b>0) {
      bool allowed=true; int channel=request.substring(a,b-1).toInt(); int state=request.substring(b).toInt();
      if (channel==0 && state==1 && voltage.condition[1]==1 && checkCondition==true) { allowed=false; }
      if (channel==1 && state==0 && voltage.condition[0]==0 && checkCondition==true) { allowed=false; }
      if (channel==1 && state==1 && voltage.condition[1]==0 && checkCondition==true) { allowed=false; }
      if (debug && (!allowed)) { Serial.println("Relay State not allowed"); }
      if (allowed) { setRelay(channel,state); } }
    response+=String(relay.state[0]) + ",";
    response+=String(relay.state[1]); }

  else if (request.indexOf("/getCalibration")>=0) {
    response+=String(calibration.peak[0],4) + ",";
    response+=String(calibration.rms[0],4) + ",";
    response+=String(calibration.peak[1],4) + ",";
    response+=String(calibration.rms[1],4) + ",";
    response+=String(calibration.changed); }

  else if (request.indexOf("/setCalibration")>=0) {
    int a=request.indexOf(",")+1; int b=request.indexOf(",",a)+1; int c=request.indexOf(",",b)+1; int d=request.indexOf(",",c)+1; int e=request.indexOf(",",d)+1;
    if (a>0 && b>0 && c>0 && d>0) {
      calibration.peak[0]=request.substring(a,b-1).toFloat();
      calibration.rms[0]=request.substring(b,c-1).toFloat();
      calibration.peak[1]=request.substring(c,d-1).toFloat();
      calibration.rms[1]=request.substring(d,e-1).toFloat();
      calibration.changed=request.substring(e).toInt(); } }

  else if (request.indexOf("/defaultCalibration")>=0) { defaultCalibration(); }

  else if (request.indexOf("/readCalibration")>=0) { readCalibration(); }

  else if (request.indexOf("/writeCalibration")>=0) { writeCalibration(); }

  else if (request.indexOf("/config/" + String(secret^challenge.toInt()) + "/")>=0 && millis()<challengeTimer+2000) { response=config_html; }

  else if (request.indexOf("/" + String(secret^challenge.toInt()) + "/")>=0 && millis()<challengeTimer+2000) { response=control_html; }

  else { response=index_html; }

  return response; }
