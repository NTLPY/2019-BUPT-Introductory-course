*** 2019 BUPT 导论课 作品展示 ***
*** 硬件端代码说明            ***
*** 组号：108                 ***
*** NTLPY 2019/12/22 20:43:22 ***

Files:
\Father_and_globefish					//Project Directory
\Father_and_globefish\Father_and_globefish.ino		//Core Codes

\Father_and_globefish\libs.h				//External Libraries
\Father_and_globefish\constants.h			//Basic Constants and image data

\Father_and_globefish\rtc.h				//RTC Module		[unused]
\Father_and_globefish\network.h				//Network(Wifi) Module
\Father_and_globefish\location.h			//Location(GPS) Module
\Father_and_globefish\u8g.h				//Display(U8g) Module
\Father_and_globefish\light.h				//FlashLight(ColorLED) Module
\Father_and_globefish\joystick.h			//Control(Joystick) Module
\Father_and_globefish\touchbut.h			//Control(TouchBut) Module
\Father_and_globefish\sht2x.h				//Tem&Hum Module	[unused]

\Father_and_globefish\homepage.h			//Home Page
\Father_and_globefish\mainpage.h			//Main Page (Functions)
\Father_and_globefish\func_clock.h			//Clock
\Father_and_globefish\func_message.h			//Message
\Father_and_globefish\func_flashlight.h			//FlashLight

\Father_and_globefish\OS_PIC				//Image Data Archive Directory

Global Variables:
byte Network::bNetworkStatus;				//Network Status (NW_WIFI_ macros)
SoftwareSerial Network::WifiSerial;			//ESP8266 Serial
ESP8266 Network::wifi;					//ESP8266 Module
String Network::PostStr;				//HTTP Message
char Network::JsonTmp[31];				//Json Message

uint16_t Location::bYear;				//Date & Time
uint8_t Location::bMonth, Location::bDay,
	Location::bHour, Location::bMinute,
	Location::bSecond;
float Location::flat, Location::flon;			//Location
char Location::clat, Location::clon;
byte Location::bLocationStatus;				//Location Status [unused]
SoftwareSerial Location::GpsSerial;			//GPS Serial
Microduino_GPS Location::GPS(&GpsSerial);		//GPS Module

ColorLED Light::light;					//ColorLED Module

unsigned long Joystick::ulJSStateLastTime;		//Current State Start Time
byte Joystick::iJSRetrievedEvent;			//Event
byte Joystick::iJSState;				//Current State
bool Joystick::bJSIsFirst;				//

unsigned long TouchBut::ulTBStateLastTime;		//Current State Start Time
byte TouchBut::iTBRetrievedEvent;			//Event
byte TouchBut::iTBState;				//Current State
bool TouchBut::bTBIsFirst;				//

bool bSDraw;						//Redraw Flag (true/false)
byte bSceneId;						//Scene Id	(SID_ macros)
