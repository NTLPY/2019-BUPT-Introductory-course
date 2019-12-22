//TouchBut Header
//Author: NTLPY
//Creation Time: 2019/12/21 18:50

#ifndef __HEADER_TOUCHBUT
#define __HEADER_TOUCHBUT

//TouchBut/TouchBut Config
#define TOUCHBUT_PIN 8
#define TBC_CLICKDELAY 90

//TouchBut/TouchBut Events
#define TBE_NONE 0xFF
#define TBE_CENTER 0x01

namespace TouchBut {
//TouchBut Data
unsigned long ulTBStateLastTime;
byte iTBRetrievedEvent;
byte iTBState;
bool bTBIsFirst;

//TranslateData
inline byte TBTranslateData() {
  int iData = digitalRead(TOUCHBUT_PIN);
  if (iData == 0)
    return TBE_CENTER;
  else
    return TBE_NONE;
}

//Setup TouchBut Device
inline void TBSetupTouchBut() {
  pinMode(TOUCHBUT_PIN, INPUT);
  ulTBStateLastTime = millis();
  iTBRetrievedEvent = TBE_NONE;
  iTBState = TBTranslateData();
  bTBIsFirst = true;
}

//Refresh TouchBut State
inline void TBRefreshState() {
  byte iNewData;
  iNewData = TBTranslateData();
  if (iNewData == iTBState) {
    if (((millis() - ulTBStateLastTime) > TBC_CLICKDELAY) && bTBIsFirst) {
      ulTBStateLastTime = millis();
      iTBRetrievedEvent = iTBState;
      bTBIsFirst = false;
    }
  }
  else {
    ulTBStateLastTime = millis();
    iTBState = iNewData;
    bTBIsFirst = true;
  }
  return;
}

//Get Event
inline byte TBGetEvent() {
  byte iTarEvent = iTBRetrievedEvent;
  iTBRetrievedEvent = TBE_NONE;
  return iTarEvent;
}

}

#endif


