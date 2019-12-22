//Location Header
//Author: NTLPY
//Creation Time: 2019/12/21 15:25

#ifndef __HEADER_LOCATION
#define __HEADER_LOCATION

//Location/Location Status
#define LC_NONE 0x00
#define LC_AVAILABLE 0x01

//Location/Gps Module Config
#define GPS_PIN_IN 4
#define GPS_PIN_OUT 5
#define SERIAL_GPS 9600

namespace Location {
//Location Data
uint16_t bYear;
uint8_t bMonth, bDay, bHour, bMinute, bSecond;
float flat = 0, flon = 0;
char clat = '0', clon = '0';

//Location Status
byte bLocationStatus = LC_NONE;

//Location Components
SoftwareSerial GpsSerial(GPS_PIN_IN, GPS_PIN_OUT) ;
Microduino_GPS GPS(&GpsSerial);

//Setup Location System
inline void LCSetupLocation() {
  GPS.begin(SERIAL_GPS);
  return;
}

//Check Time
inline void LCCheckTime() {
  if (bSecond >= 60) {
    bSecond %= 60;
    bMinute++;
  }
  if (bMinute >= 60) {
    bMinute %= 60;
    bHour++;
  }
  if (bHour >= 24) {
    bHour %= 24;
    bDay++;
  }
  switch (bMonth) {
    case 1:
      if (bDay > 31) {
        bDay %= 31;
        bMonth = 2;
      }
      break;
    case 2:
      if (bYear % 100 ? bYear % 4 : bYear % 400) {
        if (bDay > 28) {
          bDay %= 28;
          bMonth = 3;
        }
      }
      else {
        if (bDay > 29) {
          bDay %= 29;
          bMonth = 3;
        }
      }
      break;
    case 3:
      if (bDay > 31) {
        bDay %= 31;
        bMonth = 4;
      }
      break;
    case 4:
      if (bDay > 30) {
        bDay %= 30;
        bMonth = 5;
      }
      break;
    case 5:
      if (bDay > 31) {
        bDay %= 31;
        bMonth = 6;
      }
      break;
    case 6:
      if (bDay > 30) {
        bDay %= 30;
        bMonth = 7;
      }
      break;
    case 7:
      if (bDay > 31) {
        bDay %= 31;
        bMonth = 8;
      }
      break;
    case 8:
      if (bDay > 31) {
        bDay %= 31;
        bMonth = 9;
      }
      break;
    case 9:
      if (bDay > 30) {
        bDay %= 30;
        bMonth = 10;
      }
      break;
    case 10:
      if (bDay > 31) {
        bDay %= 31;
        bMonth = 11;
      }
      break;
    case 11:
      if (bDay > 30) {
        bDay %= 30;
        bMonth = 12;
      }
      break;
    case 12:
      if (bDay > 31) {
        bDay %= 31;
        bMonth = 1;
        bYear++;
      }
      break;
    default:
      bMonth %= 12;
      bYear++;
      break;
  }
  return;
}

//Retrive time
inline void LCGpsCheck() {
  if ((GPS.available() == GPS_TIME_READY) || (GPS.available() == GPS_DATA_READY)) {
    if (GPS.hour != 0 || GPS.minute != 0 || GPS.seconds != 0) {
      bHour = GPS.hour + 8;
      bMinute = GPS.minute;
      bSecond = GPS.seconds;
      bYear = GPS.year;
      bMonth = GPS.month;
      bDay = GPS.day;
      LCCheckTime();
    }
  }
  if (GPS.available() == GPS_DATA_READY) {
    flat = GPS.latitude;
    clat = GPS.lat;
    flon = GPS.longitude;
    clon = GPS.lon;
  }
  return;
}

//Send Gps Data
inline void LCSendData() {
  char buf[12];
  unsigned buflen;

  //Lock serial
  GpsSerial.end();
  Network::WifiSerial.begin(SERIAL_WIFI);
  Serial.print("lnk\r\n");
  if (Network::CreateTcp()) {
    for (size_t i = 6; i < 28; i++) {
      Network::JsonTmp[i] = '0';
    }
    Network::JsonTmp[2] = 'A';

    if (clat == 'N' || clat == 'S')
      Network::JsonTmp[6] = clat;

    dtostrf(flat, 5, 4, buf);
    dtostrf(flat, 5, 4, &Network::JsonTmp[7]);
    buflen = strlen(buf);
    for (size_t i = 7 + buflen; i < 17; i++)
      Network::JsonTmp[i] = '0';

    if (clon == 'W' || clon == 'E')
      Network::JsonTmp[17] = clon;

    dtostrf(flon, 5, 4, buf);
    dtostrf(flon, 5, 4, &Network::JsonTmp[18]);
    buflen = strlen(buf);
    for (size_t i = 18 + buflen; i < 28; i++)
      Network::JsonTmp[i] = '0';

    Network::JsonTmp[28] = '\"';

    if (Network::Send())
      Serial.println("sok!");

    //Restore serial
    Network::WifiSerial.end();
    GpsSerial.begin(SERIAL_GPS);
  }
  return;
}

}

#endif

