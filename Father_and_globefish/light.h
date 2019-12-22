//Light Header
//Author: NTLPY
//Creation Time: 2019/12/21 17:00

#ifndef __HEADER_LIGHT
#define __HEADER_LIGHT

//Light/Light Config
#define LIGHT_PIN A0
#define NUMPIXELS 1

namespace Light {
//Light Components
ColorLED light = ColorLED(NUMPIXELS, LIGHT_PIN);

//Setup Light Device
inline void LGSetupLight() {
  light.begin();
  light.setBrightness(0xFF);
  light.show();
  return;
}

//Lit
inline void LGShow() {
  light.setPixelColor(0, 0x00FFFFFF);
  light.show();
  return;
}

//Unlit
inline void LGHide() {
  light.setPixelColor(0, 0x00000000);
  light.show();
  return;
}

}

#endif

