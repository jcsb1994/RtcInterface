#include "RtcInterface.h"

int8_t RtcInterface::init()
{
  if(!_rtc.begin())   { // initiates i2c comm, then sends to adr 0x68 (adr of DS1307 and DS3231)
      return -1; 
  }
  _rtc.adjust(DateTime(__DATE__, __TIME__));

  return 0;
}

uint32_t RtcInterface::getUnixTime() {
  return _rtc.now().unixtime();
}

uint8_t RtcInterface::getHour()
{
  return _rtc.now().hour();
}

uint8_t RtcInterface::getMinutes()
{
  return _rtc.now().minute();
}

uint8_t RtcInterface::getSeconds()
{
  return _rtc.now().second();
}

void RtcInterface::setHourValue(uint8_t hour)
{
  if (hour > 23)
    hour = 0;
  DateTime precedent = _rtc.now();
  DateTime newSettings = DateTime(precedent.year(), precedent.month(), precedent.day(), hour, precedent.minute(), precedent.second());
  _rtc.adjust(newSettings);
}

void RtcInterface::setMinuteValue(uint8_t minute)
{
  if (minute > 59)
    minute = 0;
  DateTime precedent = _rtc.now();
  DateTime newSettings = DateTime(precedent.year(), precedent.month(), precedent.day(), precedent.hour(), minute, precedent.second());
  _rtc.adjust(newSettings);
}

