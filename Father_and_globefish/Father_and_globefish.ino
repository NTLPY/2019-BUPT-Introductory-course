//Father and globefish UI System
//Author: NTLPY
//Creation Time: 2019/12/21 15:02

//External Libraries
#include "constants.h"
#include "libs.h"

//Internal Libraries
//#include "rtc.h"
#include "network.h"
#include "location.h"
#include "u8g.h"
#include "light.h"
#include "joystick.h"
#include "touchbut.h"
//#include "sht2x.h"

//Namespaces
//using namespace Rtc;
using namespace Network;
using namespace Location;
using namespace U8g;
using namespace Light;
using namespace Joystick;
using namespace TouchBut;
//using namespace Sht2x;

//Global Variables
bool bSDraw = true;
byte bSceneId = SID_HOMEPAGE;

//Pages
#include "func_clock.h"
#include "func_message.h"
#include "func_flashlight.h"
#include "homepage.h"
#include "mainpage.h"

//Setup UI System
void setup() {
  //Initialize Basic Component
  Serial.begin(SERIAL_BASIC);
  while (!Serial);
  Serial.println("Setup Begin!");

  //Initialize Wire Communication
  Wire.begin();

  //Initialize Rtc

  //Initialize Network
  NWSetupNetwork();
  if (bNetworkStatus != NW_WIFI_READY) {
    Serial.println("Network load failed!");
  }

  //Initialize Location
  LCSetupLocation();

  //Initialize U8g

  //Initialize Light
  LGSetupLight();
  //Initialize Joystick
  JSSetupJoystick();

  //Initialize TouchBut
  TBSetupTouchBut();
  return;
}

//Main Loop
void loop() {
  //Before Loop
  CallBeforeLoop();
  //Within Loop
  switch (bSceneId) {
    case SID_HOMEPAGE:
      PGHome();
      break;
    case SID_MAINPAGE:
      PGMain();
      break;
    case SID_CLOCK:
      PGClock();
      break;
    case SID_MESSAGE:
      PGMessage();
      break;
    case SID_FLASHLIGHT:
      PGFlashLight();
      break;
    default:
      break;
  }
  return delay(SWITCH_DURATION);
}

//
void CallBeforeLoop() {
  unsigned long ulTimeNow = millis();
  //Gps/Time Relatives
  static unsigned long ltGpsCheck = millis();
  static unsigned long ltSendGps = millis();
  static unsigned long ltTimeClick = millis();

  GPS.available();
  if (ulTimeNow - ltGpsCheck > INTERVAL_GPS_CHECK) {
    LCGpsCheck();
    ltGpsCheck = ulTimeNow;
  }
  if (ulTimeNow - ltSendGps > INTERVAL_GPS_SEND) {
    LCSendData();
    ltSendGps = ulTimeNow;
  }
  if (ulTimeNow - ltTimeClick > INTERVAL_TIME_CLICK) {
    bSecond++;
    LCCheckTime();
    ltTimeClick = ulTimeNow;
    if ((bSceneId == SID_HOMEPAGE) || (bSceneId == SID_CLOCK)) bSDraw = true;
  }
  ////Rtc Refresh Time
  //RTCRefreshTime();

  //Refresh Joystick
  JSRefreshState();
  //Refresh TouchBut
  TBRefreshState();
  return;
}



