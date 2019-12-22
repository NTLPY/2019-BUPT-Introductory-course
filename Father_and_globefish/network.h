//Network Header
//Author: NTLPY
//Creation Time: 2019/12/21 15:03

#ifndef __HEADER_NETWORK
#define __HEADER_NETWORK

//Network/Network Status
#define NW_WIFI_NONE 0x00
#define NW_WIFI_READY 0x01
#define NW_WIFI_BAD_INIT 0x02
#define NW_WIFI_OPR_TO_STATION_SOFT_APP_FAILED 0x03
#define NW_WIFI_JOIN_AP_FAILED 0x04
#define NW_WIFI_DISABLE_MUX_FAILED 0x05

//Network/Wifi Module Config
#define WIFI_PIN_IN 2
#define WIFI_PIN_OUT 3
#define SERIAL_WIFI 9600

//Network/Wifi AP Config
#define NW_WIFI_SSID F("NTLPY")
#define NW_WIFI_PASSWORD F("1357924678")

//Network/TCP Connection Client Config
#define NW_TCP_HOST_NAME F("api.heclouds.com")
#define NW_TCP_HOST_PORT (80)

//Network/HTTP Message Config
#define NW_HTTP_MSG_PART_1 F("POST /devices/562232361/datapoints?type=3 HTTP/1.1\r\n"\
                             "api-key:U1g7AprTKDMSPAJXxyo0Y8uNv6M=\r\n"\
                             "Host:api.heclouds.com\r\n"\
                             "Connection:close\r\n"\
                             "Content-Length:30\r\n\r\n")
#define NW_HTTP_MSG_PART_2 F("\r\n\r\n\r\n")


namespace Network {
//Network Status
byte bNetworkStatus = NW_WIFI_NONE;

//Network Components
SoftwareSerial WifiSerial(WIFI_PIN_IN, WIFI_PIN_OUT);
ESP8266 wifi(&WifiSerial);
String PostStr;
char JsonTmp[31] = "{\"A\":\"N00000.0000W00000.0000\"}";

//Setup Network System
inline void NWSetupNetwork() {
  WifiInit(WifiSerial, SERIAL_WIFI);

  bNetworkStatus = NW_WIFI_READY;

  if (!wifi.setOprToStationSoftAP()) {
    bNetworkStatus = NW_WIFI_OPR_TO_STATION_SOFT_APP_FAILED;
    return;
  }

  if (!wifi.joinAP(NW_WIFI_SSID, NW_WIFI_PASSWORD)) {
    bNetworkStatus = NW_WIFI_JOIN_AP_FAILED;
    return;
  }

  if (!wifi.disableMUX()) {
    bNetworkStatus = NW_WIFI_DISABLE_MUX_FAILED;
    return;
  }
  return;
}

//Create Tcp Connection
inline bool CreateTcp() {
  if (bNetworkStatus != NW_WIFI_READY) return false;
  return wifi.createTCP(NW_TCP_HOST_NAME, NW_TCP_HOST_PORT);
}

//Send Data
inline bool Send() {
  PostStr = NW_HTTP_MSG_PART_1;
  PostStr += Network::JsonTmp;
  PostStr += NW_HTTP_MSG_PART_2;
  //Serial.println(PostStr);
  return wifi.send((const uint8_t*)Network::PostStr.c_str(), Network::PostStr.length());
}

}

#endif

