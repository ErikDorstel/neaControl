String httpServerRequest(String request) {
  String response="";
  static String challenge=String(random(1000000000));
  static uint64_t challengeTimer=millis();

  if (request.indexOf("/getChallenge")>=0) { response=String(random(1000000000)); challenge=response; challengeTimer=millis(); }

  else if (request.indexOf("/getVoltage")>=0) {
    response+=String(voltage.peak[0],2) + ",";
    response+=String(voltage.rms[0],2) + ",";
    response+=String(voltage.frequency[0],2) + ",";
    response+=String(voltage.condition[0]) + ",";
    response+=String(voltage.peak[1],2) + ",";
    response+=String(voltage.rms[1],2) + ",";
    response+=String(voltage.frequency[1],2) + ",";
    response+=String(voltage.condition[1]); }

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
      if (allowed) { setRelay(channel,state); } }
    response+=String(relay.state[0]) + ",";
    response+=String(relay.state[1]); }

  else if (request.indexOf("/" + String(secret^challenge.toInt()) + "/")>=0 && millis()<challengeTimer+10000) { response=control_html; }

  else { response=index_html; }

  return response; }
