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

struct PreciseTimeStamp {
  uint32_t unix;
  int milliseconds;
  PreciseTimeStamp(uint32_t unixTime = 0, int milliSeconds = 0) 
  : unix(unixTime), milliseconds(milliSeconds)   {}
};

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

  void initMillisCounter(void (&isr)());
  void updateMillisReference() { _millisReference = millis(); }
  
  void setHourValue(uint8_t hour);
  void setMinuteValue(uint8_t minute);
  void setUnix(uint32_t unix);
  void setTimezone(int8_t hourOffset) { _hrZoneOffset = hourOffset; }

  uint8_t getHour();
  uint8_t getMinutes();
  uint8_t getSeconds();
  uint32_t getUnixTime();
  /*! @warning To get milliseconds, updateMillisReference() must be called at 1Hz following the SQW output of the RTC */
  int getMillis();
  /*! @brief Get Unix+milliseconds timestamp */
  PreciseTimeStamp getPreciseTime();


protected:

#if USING_DS3231_RTC
  RTC_DS3231 _rtc;
#endif

#if USING_DS1307_RTC
  RTC_DS1307 _rtc;
#endif

int _sqwPin = -1; 

private:
  int _millisReference = 0;
  int8_t _hrZoneOffset = 0;
};

#endif  // RTC_INTERFACE_H

