String httpServerRequest(String request) {
  String response="";

  if (request.indexOf("/getVoltage")>=0) {
    response+=String(voltage.peak[0],2) + ",";
    response+=String(voltage.rms[0],2) + ",";
    response+=String(voltage.frequency[0],2) + ",";
    response+=String(voltage.condition[0]) + ",";
    response+=String(voltage.peak[1],2) + ",";
    response+=String(voltage.rms[1],2) + ",";
    response+=String(voltage.frequency[1],2) + ",";
    response+=String(voltage.condition[1]); }

  else if (request.indexOf("/getRelay")>=0) {
    response+=String(relay.state[0])+",";
    response+=String(relay.state[1]); }

  else if (request.indexOf("/setRelay")>=0) {
    int a=request.indexOf(",")+1; int b=request.indexOf(",",a)+1; int c=request.indexOf(",",b)+1;
    if (a>0 && b>0 && c>0) { if (request.substring(c)=="123456") {
      setRelay(request.substring(a,b-1).toInt(),request.substring(b,c-1).toInt()); } }
    response+=String(relay.state[0])+",";
    response+=String(relay.state[1]); }

  else { response=index_html; }

  return response; }
