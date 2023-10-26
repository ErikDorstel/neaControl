bool debug=true;
int secret=123456;

#include "relay.h"
#include "measure.h"
#include "Eth.h"
#include "HTTPServer.h"

void setup() {
  Serial.begin(115200);
  initRelay();
  initMeasure();
  initEth();
  initHTTPServer(); }

void loop() { measureWorker(); ethWorker(); httpServerWorker(); }
