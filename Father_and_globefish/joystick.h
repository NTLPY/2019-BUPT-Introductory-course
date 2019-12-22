//Hoystick Header
//Author: NTLPY
//Creation Time: 2019/12/21 17:13

#ifndef __HEADER_JOYSTICK
#define __HEADER_JOYSTICK

//Joystick/Joystick Config
#define JOYSTICK_PIN A2
#define JSC_CLICKDELAY 90

//Joystick/Joystick Events
#define JSE_NONE 0xFF
#define JSE_CENTER 0x01
#define JSE_DOWN 0x02
#define JSE_LEFT 0x03
#define JSE_UP 0x04
#define JSE_RIGHT 0x05

namespace Joystick {
//Joystick Data
unsigned long ulJSStateLastTime;
byte iJSRetrievedEvent;
byte iJSState;
bool bJSIsFirst;

//TranslateData
inline byte JSTranslateData() {
  int iData = analogRead(JOYSTICK_PIN);
  if (iData < 64)
    return JSE_CENTER;
  else if ((330 - 64) < iData && iData < (330 + 64))
    return JSE_DOWN;
  else if ((512 - 64) < iData && iData < (512 + 64))
    return JSE_LEFT;
  else if ((700 - 64) < iData && iData < (700 + 64))
    return JSE_UP;
  else if ((860 - 64) < iData && iData < (860 + 64))
    return JSE_RIGHT;
  else
    return JSE_NONE;
  return;
}

//Setup Joystick Device
inline void JSSetupJoystick() {
  pinMode(JOYSTICK_PIN, INPUT);
  ulJSStateLastTime = millis();
  iJSRetrievedEvent = JSE_NONE;
  iJSState = JSTranslateData();
  bJSIsFirst = true;
  return;
}

//Refresh Joystick State
inline void JSRefreshState() {
  byte iNewData;
  iNewData = JSTranslateData();
  if (iNewData == iJSState) {
    if (((millis() - ulJSStateLastTime) > JSC_CLICKDELAY) && bJSIsFirst) {
      ulJSStateLastTime = millis();
      iJSRetrievedEvent = iJSState;
      bJSIsFirst = false;
    }
  }
  else {
    ulJSStateLastTime = millis();
    iJSState = iNewData;
    bJSIsFirst = true;
  }
  return;
}

//Get Event
inline byte JSGetEvent() {
  byte iTarEvent = iJSRetrievedEvent;
  iJSRetrievedEvent = JSE_NONE;
  return iTarEvent;
}

}

#endif


