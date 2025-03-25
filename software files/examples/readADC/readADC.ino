#include "NAU7802.h"

NAU7802 sensor;

void setup() {
  Serial.begin(115200);
  while(!Serial) {

  }
  sensor.reset();
  sensor.begin();
  //sensor.setGain(GAIN_128);
  //sensor.setSampleRate(RATE_80SPS);
  //sensor.setChannel(CHANNEL1);
  sensor.setCalibration();
  delay(1000);
}

void loop() {
  Serial.println((int32_t)sensor.readADCValue()); 
  delay(100);
}