//Flashlight Function Header
//Author: NTLPY
//Creation Time: 2019/12/22 01:05

void PGFlashLight() {
  byte iJoyState, iTouchBut;
  static bool bState = false;

  //UI
  if (bSDraw) {
    u8g.firstPage();
    do {
      if (bState)
        u8g.drawBitmapP(40, 0, 6, 48, iFlashLightOn);
      else
        u8g.drawBitmapP(40, 0, 6, 48, iFlashLightOff);
      u8g.drawBitmapP(4, 48, 15, 12, txtFlashLight);
    } while (u8g.nextPage());
    if (bState)
      LGShow();
    else
      LGHide();
    bSDraw = false;
  }

  //Work
  iTouchBut = TBGetEvent();
  iJoyState = JSGetEvent();

  if (iTouchBut == TBE_CENTER) {
    bSceneId = SID_MAINPAGE;
    bSDraw = true;
    return;
  }

  if (iJoyState != JSE_NONE) {
    bState = !bState;
    bSDraw = true;
    return;
  }
  return;
}


