//***********************************************************************************
// Copyright 2021 jcsb1994
// Written by jcsb1994
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//***********************************************************************************
//
// Description:
//    This file contains a high level interface for a RTC
//
// Implementation:
//    Implemented with Arduino.h and the RTC_DS1307 type from RTClib.h by adafruit. can be added to
//    PIO project in the .ini file with: adafruit/RTClib@^<version>
//
//***********************************************************************************

#ifndef RTC_INTERFACE_H
#define RTC_INTERFACE_H

#include "Arduino.h"
#include <RTClib.h>

#define USING_DS3231_RTC 1
#define USING_DS1307_RTC 0


class RtcInterface
{
public:
  RtcInterface(int sqwPin = -1) :  _sqwPin(sqwPin) {}
  ~RtcInterface() {}

/***************************************************************************/
/*!
    @brief  Initialize the RTC
    @param  none
    @return -1 if failed, 0 if succeeded
*/
/***************************************************************************/
  int8_t init();

  void setHourValue(uint8_t hour);
  void setMinuteValue(uint8_t minute);
  uint8_t getHour();
  uint8_t getMinutes();
  uint8_t getSeconds();
  uint16_t getMillis() { return (millis() - _millisReference); }

  void initMillisCounter(void (&isr)()) {
    _rtc.writeSqwPinMode(DS3231_SquareWave1Hz);
    pinMode(_sqwPin, INPUT_PULLUP);
    attachInterrupt(_sqwPin, isr, FALLING);
  }

  void updateMillisReference() { _millisReference = millis(); }

  uint32_t getUnixTime();

protected:

#if USING_DS3231_RTC
  RTC_DS3231 _rtc;
#endif

#if USING_DS1307_RTC
  RTC_DS1307 _rtc;
#endif

int _sqwPin = -1; 

private:
  uint16_t _millisReference = 0;
};

#endif  // RTC_INTERFACE_H

