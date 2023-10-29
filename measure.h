#include <Wire.h>
#include <Adafruit_ADS1X15.h>

#define adcAlert 25

Adafruit_ADS1115 ads1115;

volatile bool newData=false;
void IRAM_ATTR newDataISR() { newData=true; }

struct measureStruct {
  hw_timer_t* phaseTimer=NULL;
  uint64_t timer;
  int16_t rawCur;
  int16_t rawMax;
  int16_t rawMin;
  int64_t rawSum;
  int channel;
  int counter;
  int polarity;
  int phases;
  uint64_t phaseDuration; } measure;

void resetMeasure() {
  detachInterrupt(adcAlert);
  if (measure.channel==0) { ads1115.readADC_Differential_0_1(); }
  else { ads1115.readADC_Differential_2_3(); }
  attachInterrupt(adcAlert,newDataISR,FALLING);
  if (measure.channel==0) { ads1115.startADCReading(ADS1X15_REG_CONFIG_MUX_DIFF_0_1,true); }
  else { ads1115.startADCReading(ADS1X15_REG_CONFIG_MUX_DIFF_2_3,true); }
  measure.timer=millis()+1000;
  measure.rawMax=0;
  measure.rawMin=0;
  measure.rawSum=0;
  measure.counter=0;
  measure.polarity=0;
  measure.phases=0;
  measure.phaseDuration=0; }

struct voltageStruct {
  double peak[2];
  double rms[2];
  double frequency[2];
  bool condition[2];
  uint64_t timer[2]; } voltage;

void initMeasure() {

  // hardware timer 0
  measure.phaseTimer=timerBegin(0,80,true);
  timerStart(measure.phaseTimer);

  // ads1115 voltage adc
  if (!ads1115.begin()) { Serial.println("Failed to initialize ADS1115."); }
  ads1115.setGain(GAIN_TWO); ads1115.setDataRate(RATE_ADS1115_860SPS);
  pinMode(adcAlert,INPUT);
  resetMeasure(); }

void measureWorker() {

  if (newData) {
    newData=false; measure.counter++;
    measure.rawCur=ads1115.getLastConversionResults();
    measure.rawSum+=abs(measure.rawCur);
    if (measure.rawCur>measure.rawMax) { measure.rawMax=measure.rawCur; }
    if (measure.rawCur<measure.rawMin) { measure.rawMin=measure.rawCur; }
    if (measure.rawCur>1000 && measure.polarity<=0) { measure.polarity=1; measure.phases++;
      if (measure.phases>2) { measure.phaseDuration=timerRead(measure.phaseTimer); } else { timerWrite(measure.phaseTimer,0x0ULL); } }
    if (measure.rawCur<-1000 && measure.polarity>=0) { measure.polarity=-1; } }

  if (millis()>=measure.timer) {
    double voltagePeak=(ads1115.computeVolts(measure.rawMax)-ads1115.computeVolts(measure.rawMin))*121;
    double voltageRMS=ads1115.computeVolts(measure.rawSum/measure.counter)*295;
    double voltageFrequency=0; if (measure.phases>2) { voltageFrequency=1000000/((double)measure.phaseDuration/(measure.phases-2)); }
    if (debug) {
      Serial.print("Voltage Chan: " + String(measure.channel) + ", ");
      Serial.print("Peak: " + String(voltagePeak,2) + " V, ");
      Serial.print("RMS: " + String(voltageRMS,2) + " V, ");
      Serial.print("Freq: " + String(voltageFrequency,2) + " Hz, ");
      Serial.println("Count: " + String(measure.counter)); }
    if (measure.counter>=840) {
      voltage.peak[measure.channel]=voltagePeak;
      voltage.rms[measure.channel]=voltageRMS;
      voltage.frequency[measure.channel]=voltageFrequency;
      if (voltagePeak>300 && voltagePeak<350 && voltageRMS>210 && voltageRMS<250 && voltageFrequency>48 && voltageFrequency<52) {
        if (voltage.condition[measure.channel]==false) { voltage.timer[measure.channel]=millis(); } voltage.condition[measure.channel]=true; }
      else { if (voltage.condition[measure.channel]==true) { voltage.timer[measure.channel]=millis(); } voltage.condition[measure.channel]=false; }
      if (measure.channel==0) { measure.channel=1; } else { measure.channel=0; } }
    resetMeasure(); } }
