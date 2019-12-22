//MainPage Header
//Author: NTLPY
//Creation Time: 2019/12/21 19:23

#define FUNC_CLOCK 0x0
#define FUNC_MESSAGE 0x1
#define FUNC_FLASHLIGHT 0x2

void PGMain() {
  byte iJoyState, iTouchBut;
  static char focus = 0;

  //UI
  if (bSDraw) {
    u8g.firstPage();
    do {
      switch (focus) {
        case FUNC_CLOCK:
          u8g.drawFrame(0, 0, 64, 32);
          u8g.drawBitmapP(8, 8, 8, 16, smiClock);
          u8g.drawBitmapP(0, 32, 8, 16, smiMessage);
          u8g.drawBitmapP(0, 48, 8, 16, smiFlashLight);
          u8g.drawBitmapP(72, 8, 6, 48, iClock);
          break;
        case FUNC_MESSAGE:
          u8g.drawFrame(0, 16, 64, 32);
          u8g.drawBitmapP(0, 0, 8, 16, smiClock);
          u8g.drawBitmapP(8, 24, 8, 16, smiMessage);
          u8g.drawBitmapP(0, 48, 8, 16, smiFlashLight);
          u8g.drawBitmapP(72, 8, 6, 48, iMessage);
          break;
        case FUNC_FLASHLIGHT:
          u8g.drawFrame(0, 32, 64, 32);
          u8g.drawBitmapP(0, 0, 8, 16, smiClock);
          u8g.drawBitmapP(0, 16, 8, 16, smiMessage);
          u8g.drawBitmapP(8, 40, 8, 16, smiFlashLight);
          u8g.drawBitmapP(72, 8, 6, 48, iFlashLight);
          break;
        default:
          break;
      }

      u8g.drawFrame(64, 0, 64, 64);
    } while (u8g.nextPage());
    bSDraw = false;
  }

  //Work
  iTouchBut = TBGetEvent();
  iJoyState = JSGetEvent();

  if (iTouchBut == TBE_CENTER) {
    bSceneId = SID_HOMEPAGE;
    bSDraw = true;
    return;
  }

  switch (iJoyState) {
    case JSE_CENTER:
      switch (focus) {
        case FUNC_CLOCK:
          bSceneId = SID_CLOCK;
          break;
        case FUNC_MESSAGE:
          bSceneId = SID_MESSAGE;
          break;
        case FUNC_FLASHLIGHT:
          bSceneId = SID_FLASHLIGHT;
          break;
        default:
          break;
      }
      bSDraw = true;
      break;
    case JSE_UP:
      focus --;
      focus %= 3;
      bSDraw = true;
      break;
    case JSE_DOWN:
      focus ++;
      focus %= 3;
      bSDraw = true;
      break;
    default:
      break;
  }
  return;
}


