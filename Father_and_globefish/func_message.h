//Message Function Header
//Author: NTLPY
//Creation Time: 2019/12/22 01:05

inline void PGMSGSendData(char iMsg) {
  char buf[12];
  unsigned buflen;

  //Lock serial
  GpsSerial.end();
  Network::WifiSerial.begin(SERIAL_WIFI);
  Serial.print("lnk2\r\n");
  if (Network::CreateTcp()) {
    Network::JsonTmp[2] = 'D';
    Network::JsonTmp[6] = iMsg;

    if (Network::Send())
      Serial.println("sok2!");

    //Restore serial
    Network::WifiSerial.end();
    GpsSerial.begin(SERIAL_GPS);
  }
  return;
}

void PGMessage() {
  byte iJoyState, iTouchBut;
  static char focus = 0;

  //UI
  if (bSDraw) {
    u8g.firstPage();
    do {
      switch (focus) {
        case 0:
          u8g.drawBox(12, 0, 56, 12);
          u8g.setDefaultBackgroundColor();
          u8g.drawBitmapP(12, 0, 7, 12, msg1);
          u8g.setDefaultForegroundColor();
          u8g.drawBitmapP(12, 12, 9, 12, msg2);
          u8g.drawBitmapP(12, 24, 9, 12, msg3);
          u8g.drawBitmapP(12, 36, 9, 12, msg4);
          u8g.drawBitmapP(12, 48, 10, 12, msg5);
          break;
        case 1:
          u8g.drawBox(12, 12, 72, 12);
          u8g.drawBitmapP(12, 0, 7, 12, msg1);
          u8g.setDefaultBackgroundColor();
          u8g.drawBitmapP(12, 12, 9, 12, msg2);
          u8g.setDefaultForegroundColor();
          u8g.drawBitmapP(12, 24, 9, 12, msg3);
          u8g.drawBitmapP(12, 36, 9, 12, msg4);
          u8g.drawBitmapP(12, 48, 10, 12, msg5);
          break;
        case 2:
          u8g.drawBox(12, 24, 72, 12);
          u8g.drawBitmapP(12, 0, 7, 12, msg1);
          u8g.drawBitmapP(12, 12, 9, 12, msg2);
          u8g.setDefaultBackgroundColor();
          u8g.drawBitmapP(12, 24, 9, 12, msg3);
          u8g.setDefaultForegroundColor();
          u8g.drawBitmapP(12, 36, 9, 12, msg4);
          u8g.drawBitmapP(12, 48, 10, 12, msg5);
          break;
        case 3:
          u8g.drawBox(12, 36, 72, 12);
          u8g.drawBitmapP(12, 0, 7, 12, msg1);
          u8g.drawBitmapP(12, 12, 9, 12, msg2);
          u8g.drawBitmapP(12, 24, 9, 12, msg3);
          u8g.setDefaultBackgroundColor();
          u8g.drawBitmapP(12, 36, 9, 12, msg4);
          u8g.setDefaultForegroundColor();
          u8g.drawBitmapP(12, 48, 10, 12, msg5);
          break;
        case 4:
          u8g.drawBox(12, 48, 80, 12);
          u8g.drawBitmapP(12, 0, 7, 12, msg1);
          u8g.drawBitmapP(12, 12, 9, 12, msg2);
          u8g.drawBitmapP(12, 24, 9, 12, msg3);
          u8g.drawBitmapP(12, 36, 9, 12, msg4);
          u8g.setDefaultBackgroundColor();
          u8g.drawBitmapP(12, 48, 10, 12, msg5);
          u8g.setDefaultForegroundColor();
          break;
        default:
          break;
      }
    } while (u8g.nextPage());
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

  switch (iJoyState) {
    case JSE_CENTER:
      switch (focus) {
        default:
          PGMSGSendData('A' + focus);
          bSceneId = SID_MAINPAGE;
          bSDraw = true;
          break;
      }
      bSDraw = true;
      break;
    case JSE_UP:
      focus --;
      focus %= 5;
      bSDraw = true;
      break;
    case JSE_DOWN:
      focus ++;
      focus %= 5;
      bSDraw = true;
      break;
    default:
      break;
  }
  return;
}


