//Clock Function Header
//Author: NTLPY
//Creation Time: 2019/12/22 01:05

void PGClock() {
  byte iJoyState, iTouchBut;

  //UI
  if (bSDraw) {
    u8g.firstPage();
    do {
      u8g.setFont(u8g_font_7x13);

      u8g.drawFrame(0, 0, 64, 64);
      u8g.drawFrame(1, 1, 62, 62);
      u8g.drawFrame(64, 0, 64, 64);
      u8g.drawFrame(65, 1, 62, 62);
      u8g.drawCircle(96, 32, 26);
      u8g.drawCircle(96, 32, 25);

      u8g.drawLine(64 + 12 + 20, 32,
                   64 + 12 + 20 + (u8g_uint_t)(8 * sin(PI * (bHour % 12) / 12 * 2 + (float)bMinute / 60 * PI / 12)),
                   32 - (u8g_uint_t)(8 * cos(PI * (bHour % 12) / 12 * 2 + (float)bMinute / 60 * PI / 12)));
      u8g.drawLine(64 + 12 + 20, 32,
                   64 + 12 + 20 + (u8g_uint_t)(16 * sin(PI * bMinute / 60 * 2)),
                   32 - (u8g_uint_t)(16 * cos(PI * bMinute / 60 * 2)));
      u8g.drawLine(64 + 12 + 20, 32,
                   64 + 12 + 20 + (u8g_uint_t)(24 * sin(PI * bSecond / 60 * 2)),
                   32 - (u8g_uint_t)(24 * cos(PI * bSecond / 60 * 2)));

      u8g.setFont(u8g_font_7x13);
      u8g.setPrintPos(4, 13);
      u8g.print((byte)(bHour % 12));
      u8g.setPrintPos(18, 13);
      u8g.print(':');
      u8g.setPrintPos(24, 13);
      u8g.print(bMinute);
      u8g.setPrintPos(37, 13);
      u8g.print(':');
      u8g.setPrintPos(43, 13);
      u8g.print(bSecond);

      if (bHour < 12)
        u8g.drawBitmapP(8, 40, 3, 12, labMorning);
      else
        u8g.drawBitmapP(8, 40, 3, 12, labAfternoon);
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
  return;
}


