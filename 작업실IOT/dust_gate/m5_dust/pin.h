//핀에 대한 설정 






//wifi

#define FIREBASE_HOST "rpi-arduino-bc957.firebaseio.com"  //
#define FIREBASE_AUTH "FlowlqsCBeqdvMJxdgxbmEyeiWi2CbSX3KStpCUW"  //
#define WIFI_SSID "hangmini"
#define WIFI_PASSWORD "cookiebox!1"  //작업실은 cookiebox, 집은 !1
#define AP_SSID  "daft work"


//송신기 주소 통일
const byte address[6] = "00001"; // 송신기와 수신기가 동일한 값으로 주소 설정함(5자리)
//
#define Freq 55  //전류 값

//re24 설정
#define SCN 26
#define SE 25


#define relay_sgl 35                                                                                          



//블루투스 

#define SERVICE_UUID           "37f7f9c6-a9b4-11ec-b909-0242ac120002" // UART service UUID
#define CHARACTERISTIC_UUID_RX "37f7f9c6-a9b4-11ec-b909-0242ac120002"
#define CHARACTERISTIC_UUID_TX "37f7f9c6-a9b4-11ec-b909-0242ac120002"


////eeprom
#include "EEPROM.h"
#define EEPROM_SIZE 128
  struct ang {
    int ang_min[10];
    int ang_max[10];
  };




//서보 각도 
//int ang_min[10] = {100};

//int ang_max[10] = {550};




/*
 이미지 출처 
https://unsplash.com/@wopeflight
Copyright Peter Wormstetter
*/
