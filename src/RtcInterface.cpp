#include "RtcInterface.h"

int8_t RtcInterface::init()
{
  _rtc.begin(); // initiates i2c comm, then sends to adr 0x68 (adr of DS1307)
  _rtc.adjust(DateTime(__DATE__, __TIME__));
  return 0;
}

uint32_t RtcInterface::getAbsTime() {
  return _rtc.now().secondstime();
}

uint8_t RtcInterface::getHour()
{
  return _rtc.now().hour();
}

uint8_t RtcInterface::getMinutes()
{
  return _rtc.now().minute();
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


