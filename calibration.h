#include <Preferences.h>

Preferences flash;

struct calibrationStruct { double peak[2]; double rms[2]; double peakDefault=121; double rmsDefault=295; } calibration;

void readCalibration() {
  flash.begin("neaControl",true);
  calibration.peak[0]=flash.getDouble("peak0",calibration.peakDefault);
  calibration.peak[1]=flash.getDouble("peak1",calibration.peakDefault);
  calibration.rms[0]=flash.getDouble("rms0",calibration.rmsDefault);
  calibration.rms[1]=flash.getDouble("rms1",calibration.rmsDefault);
  flash.end();
  if (debug) {
    Serial.println("Calibration EVU Peak: " + String(calibration.peak[0],2) + " RMS: " + String(calibration.rms[0],2));
    Serial.println("Calibration NEA Peak: " + String(calibration.peak[1],2) + " RMS: " + String(calibration.rms[1],2)); } }

void writeCalibration() {
  flash.begin("neaControl",false);
  flash.putDouble("peak0",calibration.peak[0]);
  flash.putDouble("peak1",calibration.peak[1]);
  flash.putDouble("rms0",calibration.rms[0]);
  flash.putDouble("rms1",calibration.rms[1]);
  flash.end();
  readCalibration(); }

void resetCalibration() {
  calibration.peak[0]=calibration.peakDefault;
  calibration.peak[1]=calibration.peakDefault;
  calibration.rms[0]=calibration.rmsDefault;
  calibration.rms[1]=calibration.rmsDefault;
  writeCalibration(); }