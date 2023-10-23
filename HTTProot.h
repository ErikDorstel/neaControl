String httpServerRequest(String request) {
  String response="";

  if (request.indexOf("/getVoltage")>=0) {
    response+=String(voltage.peak[0],2) + ",";
    response+=String(voltage.rms[0],2) + ",";
    response+=String(voltage.frequency[0],2) + ",";
    response+=String(voltage.peak[1],2) + ",";
    response+=String(voltage.rms[1],2) + ",";
    response+=String(voltage.frequency[1],2); }

  else if (request.indexOf("/getRelay")>=0) {
    response+=String(relay.state[0],2) + ",";
    response+=String(relay.state[1],2); }

  else if (request.indexOf("/setRelay")>=0) {
    int a=request.indexOf(",")+1; int b=request.indexOf(",",a)+1;
    if (a>0 && b>0) { setRelay(request.substring(a,b-1).toInt(),request.substring(b).toInt()); }
    response+=String(relay.state[0],2) + ",";
    response+=String(relay.state[1],2); }

  else { response=index_html; }

  return response; }
