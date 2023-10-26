bool debug=true;
int secret=123456;
bool ethDHCP=true;
uint8_t ethIP[]={192,168,100,100};
uint8_t ethGW[]={192,168,100,1};
uint8_t ethDNS[]={192,168,100,1};
uint8_t ethNM[]={255,255,255,0};

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
