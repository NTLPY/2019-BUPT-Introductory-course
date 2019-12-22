//HomePage Header
//Author: NTLPY
//Creation Time: 2019/12/21 17:11

void PGHome() {
  byte iJoyState, iTouchBut;

  //UI
  if (bSDraw) {
    u8g.firstPage();
    do {
      u8g.setFont(u8g_font_7x13);

      //Draw clock border
      u8g.drawFrame(64, 0, 64, 64);
      //Draw left func border
      u8g.drawFrame(0, 16, 16, 32);
      //Draw right func border
      u8g.drawFrame(48, 16, 16, 32);
      //Draw top func border
      u8g.drawFrame(16, 0, 32, 16);
      //Draw bottom func border
      u8g.drawFrame(16, 48, 32, 16);
      //Draw center func border
      u8g.drawFrame(16, 16, 32, 32);

      //Draw clock
      u8g.drawCircle(64 + 12 + 20, 0 + 4 + 20, 20);
      u8g.drawLine(64 + 12 + 20, 0 + 4 + 20,
                   64 + 12 + 20 + (u8g_uint_t)(8 * sin(PI * (bHour % 12) / 12 * 2 + (float)bMinute / 60 * PI / 12)),
                   0 + 4 + 20 - (u8g_uint_t)(8 * cos(PI * (bHour % 12) / 12 * 2 + (float)bMinute / 60 * PI / 12)));
      u8g.drawLine(64 + 12 + 20, 0 + 4 + 20,
                   64 + 12 + 20 + (u8g_uint_t)(16 * sin(PI * bMinute / 60 * 2)),
                   0 + 4 + 20 - (u8g_uint_t)(16 * cos(PI * bMinute / 60 * 2)));
      if (bHour < 12)
        u8g.drawBitmapP(64 + 4, 48 + 2, 3, 12, labMorning);
      else
        u8g.drawBitmapP(64 + 4, 48 + 2, 3, 12, labAfternoon);

      u8g.setPrintPos(96 + (-2), 63 - 2);
      u8g.print((byte)(bHour % 12));
      u8g.setPrintPos(96 + (-2) + 12, 63 - 2);
      u8g.print(':');
      u8g.setPrintPos(96 + (-2) + 18, 63 - 2);
      u8g.print(bMinute);

      //Draw left func button
      u8g.drawBitmapP(0 + 2, 16 + 4, 2, 24, labLnk1);
      //Draw right func button
      u8g.drawBitmapP(48 + 2, 16 + 4, 2, 24, labLnk2);
      //Draw top func button
      u8g.drawBitmapP(16 + 4, 0 + 2, 3, 12, labLnk3);
      //Draw center func button
      u8g.drawBitmapP(16 + 4, 16 + 10, 3, 12, labLnk0);
    } while (u8g.nextPage());
    bSDraw = false;
  }

  //Work
  iTouchBut = TBGetEvent();
  iJoyState = JSGetEvent();

  switch (iJoyState) {
    case JSE_CENTER:
      bSceneId = SID_MAINPAGE;
      bSDraw = true;
      break;
    case JSE_LEFT:
      bSceneId = SID_CLOCK;
      bSDraw = true;
      break;
    case JSE_RIGHT:
      bSceneId = SID_MESSAGE;
      bSDraw = true;
      break;
    case JSE_UP:
      bSceneId = SID_FLASHLIGHT;
      bSDraw = true;
      break;
    default:
      break;
  }
  return;
}

