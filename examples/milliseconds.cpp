/*
use the rtc to gen a 1Hz sqw to count millisecs with millis
*/
#include <Arduino.h>
#include <RTClib.h>
#include "RtcInterface.h"

#define SQW_PIN (GPIO_NUM_17)

RtcInterface rtc = RtcInterface(SQW_PIN);


void IRAM_ATTR milliCountISR()
{
  rtc.updateMillisReference();
}

void setup()
{
  Serial.begin(9600);
  Serial.println("hello");

  rtc.init();

  rtc.initMillisCounter(milliCountISR);
}

void loop()
{
  Serial.println("Seconds: " + String(rtc.getSeconds()) + "." + String(rtc.getMillis()) );
  delay(20);
}
