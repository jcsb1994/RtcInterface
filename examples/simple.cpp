#include <Arduino.h>
#include "RtcInterface.h"

RtcInterface myClock;

void setup() {
  Serial.begin(9600);
  Serial.println("hello");
  myClock.init();
}

void loop() { 
  Serial.println(myClock.getSeconds());
}