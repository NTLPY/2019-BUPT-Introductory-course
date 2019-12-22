//U8g Header
//Author: NTLPY
//Creation Time: 2019/12/21 16:56

#ifndef __HEADER_U8G
#define __HEADER_U8G

//U8g/U8g Config
#define INTERVAL_LCD 20

namespace U8g {
//U8g Components
U8GLIB_SSD1306_128X64 u8g = U8GLIB_SSD1306_128X64(U8G_I2C_OPT_NONE);

}

#endif

