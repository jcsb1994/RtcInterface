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

class RtcInterface
{
public:
  RtcInterface()  {}
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
  uint32_t getAbsTime();

private:
  RTC_DS1307 _rtc;
};

#endif  // RTC_INTERFACE_H

