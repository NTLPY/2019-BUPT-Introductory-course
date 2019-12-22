//RTC Header
//Author: NTLPY
//Creation Time: 2019/12/21 16:31

#ifndef __HEADER_RTC
#define __HEADER_RTC

namespace Rtc {
//Rtc Datas
unsigned long bOffset = millis();

//Rtc Components
RTC rtc;

//Refresh Time
inline void RTCRefreshTime() {
  rtc.getTime(&bHour, &bMinute, &bSecond);
  return;
}

}

#endif

