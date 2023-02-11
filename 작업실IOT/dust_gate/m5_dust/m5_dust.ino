//https://docs.m5stack.com/en/api/system  명령어

//이미지 데이터 메모리 업로드 툴 깃 주소( esptool)
//https://github.com/me-no-dev/arduino-esp32fs-plugin/releases

//온도 센서 확인할것
//https://github.com/espressif/arduino-esp32/issues/2360

#include <FirebaseESP32.h>
#include <Wire.h>
#include "Adafruit_PWMServoDriver.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <WiFi.h>

//웹 서버
#include <ESPAsyncWebServer.h>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

#include "SPIFFS.h"
#include "M5Stack.h"
#include "pin.h"
#include "gate.h"


//####################설정 ###################################
//wifi안쓸때 옵션 만들것
#define wifi_set 2 //0일 경우 사용 하지 않음 1일 경우 와이파이 파이어베이스 사용
//2일 경우 wifi서버 사용

//블루투스 옵션
#define ble_set 1

//더스트 게이트 수량
#define gate_val 10

btn dust_gate(gate_val);  //더스트 값을 넣어서 초기화

#if wifi_set == 1  //1일 경우 wifi사용 
FirebaseData firebaseData;
FirebaseJson json;

#elif wifi_set == 2
AsyncWebServer server(80);

#endif
int wifi_too = 0;
String ledState;




BLECharacteristic *pCharacteristic;
bool deviceConnected = false;



class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };
    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};


class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {

        for (int i = 0; i < rxValue.length(); i++) {
          Serial.print(rxValue[i]);
        }

        const char *c = rxValue.c_str();
        dust_gate.bt_gate(c);

      }

    }

};






//re24와 lcd의 응답 속도간 문제가 있을 수 있음.
//https://community.m5stack.com/topic/1686/m5stack-nrf24-lcd-slow-down/4


RF24 radio(SE, SCN);     // SPI통신을 위한 (CE, CSN) 핀 선언

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

//스타트 설정 토글
bool start_setup_val = true;

//스레드
portTickType delay_10 = 10 / portTICK_RATE_MS;
const long delayTime = 3000;
unsigned long previousMillis = 0;





void setup() {

  M5.begin(true, false, true, true); //lcd, sd카드, 직렬통신, i2c 순서로
  //나중에 써야 하는것은 켜둘것.
  M5.Power.begin();
  M5.Speaker.begin(); //Initialize the speaker
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);



#if wifi_set == 1  //1일 경우 wifi사용 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println();
  Serial.print("와이파이에 연결");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.print("IP에 연결");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  firebaseData.setResponseSize(1024);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);  //1초 *60 = 1분이란 설정
  Firebase.getInt(firebaseData, "Room_3/board_1/ang_max/0");



#elif wifi_set == 2
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println();
  Serial.print("와이파이에 연결");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.print("IP에 연결");
  Serial.println(WiFi.localIP());

  wifi_html();


#endif




  //------------------------블루투스


#if ble_set == 1
  // Create the BLE Device

  BLEDevice::init("DUST GATE"); // Give it a name
  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);
  // Create a BLE Characteristic

  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_TX,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );
  pCharacteristic->addDescriptor(new BLE2902());
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID_RX,
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());
  // Start the service
  pService->start();
  pServer->getAdvertising()->start();


#endif

  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }

  //-----------------------rf

  radio.begin();
  radio.openReadingPipe(0, address);// 데이터를 받을 송신기 주소를 설정
  radio.setPALevel(RF24_PA_HIGH); // 송신거리에 따른, 전원공급 파워레벨 설정

  //(최소) RF24_PA_MIN / RF24_PA_LOW / RF24_PA_HIGH / RF24_PA_MAX (최대) 설정가능
  //송신이 약하다고 판단될 경우 nRF24모듈의 GND와 3.3V 단자에 전해콘덴서(10uF이상:+를3.3V연결)사용권장
  radio.startListening();   // 모듈을 수신기(상태)로 설정

  //서보
  pwm.begin();
  pwm.setPWMFreq(Freq);



  //------------

  pinMode(relay_sgl, OUTPUT);
  start_app();

  if (start_setup_val == false) {

    xTaskCreatePinnedToCore(
      task1,
      "task1",
      8192,
      NULL,
      1,
      NULL,
      1
    );

    xTaskCreatePinnedToCore(
      task2,
      "task2",
      8192,
      NULL,
      1,
      NULL,
      0
    );

  }

}





void wifi_html() {

#if wifi_set == 2
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  // Route to set GPIO to HIGH
  server.on("/1on", HTTP_GET, [](AsyncWebServerRequest * request) {  //서버에서 1on을 가져 오면 
    Serial.println("1on");

   dust_gate.bt_gate("GA01");
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to set GPIO to LOW
  server.on("/1off", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println("1off");
    
    dust_gate.bt_gate("GA00");
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });




  // Route to set GPIO to HIGH
  server.on("/2on", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println("2on");
    dust_gate.bt_gate("GA11");
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to set GPIO to LOW
  server.on("/2off", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println("2off");
    dust_gate.bt_gate("GA10");
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });





  server.on("/3on", HTTP_GET, [](AsyncWebServerRequest * request) {  //서버에서 1on을 가져 오면 
    Serial.println("1on");

    dust_gate.bt_gate("GA21");
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to set GPIO to LOW
  server.on("/3off", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println("1off");
    
    dust_gate.bt_gate("GA20");
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });




  // Route to set GPIO to HIGH
  server.on("/4on", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println("2on");
    dust_gate.bt_gate("GA31");
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to set GPIO to LOW
  server.on("/4off", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println("2off");
    dust_gate.bt_gate("GA30");
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });



  
  // Start server
  server.begin();

  #endif
}

void start_app() {

  M5.Lcd.fillScreen(WHITE);
  M5.Lcd.drawJpgFile(SPIFFS, "/logo.jpg", 80, 35);
  delay(1000);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(4);

  M5.Lcd.drawString("1", 22, 120);
  M5.Lcd.drawString("2", 86, 120);
  M5.Lcd.drawString("3", 150, 120);
  M5.Lcd.drawString("4", 214, 120);
  M5.Lcd.drawString("5", 278, 120);
  M5.Lcd.drawString("6", 22, 190);
  M5.Lcd.drawString("7", 86, 190);
  M5.Lcd.drawString("8", 150, 190);
  M5.Lcd.drawString("9", 214, 190);
  M5.Lcd.drawString("10", 266, 190);

  M5.Lcd.drawJpgFile(SPIFFS, "/base.jpg", 0, 0);
  M5.Lcd.drawRect(0, 0, 320, 100, WHITE);
  M5.Lcd.drawRect(0, 100, 320, 140, WHITE);
  M5.Lcd.drawRect(2, 102, 64, 68, YELLOW);
  mem_set();

}


void mem_set() {

  memset(dust_gate.gate_state, 0, sizeof(int)*gate_val);
  memset(dust_gate.fire_state, 0, sizeof(int)*gate_val);
  memset(dust_gate.bluetooth_state, 0, sizeof(int)*gate_val);
  memset(dust_gate.button_state, 0, sizeof(int)*gate_val);
  memset(dust_gate.ang_min, 0, sizeof(int)*gate_val);
  memset(dust_gate.ang_max, 0, sizeof(int)*gate_val);
  memset(dust_gate.button_toogle, 0, sizeof(int)*gate_val);

  struct ang ang_get;
  EEPROM.get(0, ang_get);

  for (int i = 0; i < 10; i++) { //엥글값

    dust_gate.ang_min[i] = 300; //ang_get.ang_min[i];
    dust_gate.ang_max[i] = 102; //ang_get.ang_max[i];
    Serial.println(int(dust_gate.ang_min[i]));
    Serial.println(int(dust_gate.ang_max[i]));
  }

//int ang_min[10] = {100};

//int ang_max[10] = {550};


  //모드 설정
  graphic_set();

  //스레드 잠시 멈춤 토글
  start_setup_val = false;
}





void task1(void *pvParameters) {
  while (1) {
    TIMERG1.wdt_wprotect = TIMG_WDT_WKEY_VALUE;
    TIMERG1.wdt_feed = 1;
    TIMERG1.wdt_wprotect = 0;
    //////////////////////////1.rf값을 받아서 게이트 동작
    //값을 보고 릴레이를 동작
    //gate.state값을 릴레이로 보널것

    dust_gate.relay();
#if wifi_set == 1
    String text_1 = loop_fire(); //파이어베이스 값 스트링 변환해야 함
    dust_gate.firebase_get(text_1) ;
#endif

    vTaskDelay(delay_10);
  }
}





//코어 0번
void task2(void *pvParameters) {

  while (1) {
    TIMERG0.wdt_wprotect = TIMG_WDT_WKEY_VALUE;
    TIMERG0.wdt_feed = 1;
    TIMERG0.wdt_wprotect = 0;
    dust_gate.button_val();

    //rf통신 값
    char* text = radio_val();  //값을 읽어 온다
    //게이트에 보내서 동작 할지 안할지 확인
    dust_gate.gate_set(text);
    vTaskDelay(delay_10);
  }

}
char* radio_val() { //rf통신 값

  static char text[5] = "";
  //   Serial.println("rf값 출력");
  if (radio.available()) {
    radio.read(&text, sizeof(text)); // 수신되는 데이터 길이만큼 읽어 저장

    String string = text;  //스트링으로 변환 해줘야 if문이 인식을 한다.

    Serial.println(text);
    Serial.println(string);
    delay(50);
    return text;
  }

}

String loop_fire() {
#if wifi_set == 1
  //Serial.println("connected to WiFi");
  static String valuea = "";
  //Serial.println("LOOP_FIRE");
  if (Firebase.get(firebaseData, "Room_3/board_1")) {
    String value = firebaseData.jsonString(); //값을 문자열로 받아와서 밸류 값에 넣는다
    Serial.println(value);
    if (value != valuea) {
      valuea = value;
      delay(50);
      return value;
    }
  }
#endif
}



void graphic_set() {  //설정 문제 없이 감
  bool break_while = false;
  unsigned long nowtime = millis();
  while (break_while == false) {
    nowtime += millis();
    M5.update();
    if (nowtime - previousMillis >= delayTime) {  //10초
      if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 300)) {
        M5.Lcd.fillScreen(RED);  //셋업 모드
        delay(2000);
        setup_gate_val();  //게이트 셋업
      }
      break_while = true;
    }
  }

}


void setup_gate_val() {

  unsigned int setup_btn = 0;

  M5.Lcd.fillRect(0, 0, 320, 240, WHITE);  //함수화 시킬것
  M5.Lcd.setTextColor(RED, WHITE);
  M5.Lcd.drawString("Motor Set", 40, 10);
  M5.Lcd.setTextColor(BLACK, WHITE);
  M5.Lcd.drawString("Motor Num", 10, 50);
  M5.Lcd.setTextColor(BLUE, WHITE);
  M5.Lcd.drawString((String)setup_btn, 270, 50);
  while (1) {
    M5.update();
    if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 300)) {
      setup_btn --;
      if (setup_btn >= -1) {
        setup_btn = 10;

      }
      if (setup_btn == 9) {
        M5.Lcd.fillRect(0, 0, 320, 240, WHITE);
      }

      M5.Lcd.setTextColor(RED, WHITE);
      M5.Lcd.drawString("Motor Set", 40, 10);
      M5.Lcd.setTextColor(BLACK, WHITE);
      M5.Lcd.drawString("Motor Num", 10, 50);
      M5.Lcd.setTextColor(BLUE, WHITE);
      M5.Lcd.drawString((String)setup_btn, 270, 50);
    }
    if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 300)) {
      setup_btn ++;
      if (setup_btn >= 11) {
        M5.Lcd.fillRect(0, 0, 320, 240, WHITE);
        setup_btn = 0;
      }
      M5.Lcd.setTextColor(RED, WHITE);
      M5.Lcd.drawString("Motor Set", 40, 10);
      M5.Lcd.setTextColor(BLACK, WHITE);
      M5.Lcd.drawString("Motor Num", 10, 50);
      M5.Lcd.setTextColor(BLUE, WHITE);
      M5.Lcd.drawString((String)setup_btn, 270, 50);
    }
    if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 300)) {
      if (setup_btn != 10) {
        setup_gate_input(setup_btn);
        M5.Lcd.setTextColor(RED, WHITE);
        M5.Lcd.drawString("Motor Set", 40, 10);
        M5.Lcd.setTextColor(BLACK, WHITE);
        M5.Lcd.drawString("Motor Num", 10, 50);
        M5.Lcd.setTextColor(BLUE, WHITE);
        M5.Lcd.drawString((String)setup_btn, 270, 50);
      } else if (setup_btn == 10) {
        struct ang ang_put;

        for (int i = 0; i < 10; i++) { //엥글값
          ang_put.ang_min[i] = int(dust_gate.ang_min[i]);
          ang_put.ang_max[i] = int(dust_gate.ang_max[i]);
        }

        EEPROM.put(0, ang_put);
        EEPROM.commit();
        M5.Lcd.fillRect(0, 0, 320, 240, WHITE);
        M5.Lcd.drawString("COMMIT", 70, 50);
        delay(1000);
        M5.Lcd.drawString("RESET...", 70, 200);
        M5.Power.reset();  //리셋
      }
    }

    //Serial.print("모터 번호 :");
    //Serial.println(setup_btn);
  }
}





void setup_gate_input(int setup_btn) {
  M5.Lcd.drawString("max", 10, 100);
  M5.Lcd.drawString("min", 150, 100);
  int val = 0;

  M5.Lcd.drawString("MAX ANG   ", 10, 200);




  while (1) {
    M5.update();
    if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 300)) {
      if (val == 0) { //max값 수정
        dust_gate.ang_max[setup_btn] -= 2;

        M5.Lcd.drawString((String)dust_gate.ang_max[setup_btn], 10, 150);

      } else if (val == 1) {
        dust_gate.ang_min[setup_btn] -= 2;

        M5.Lcd.drawString((String)dust_gate.ang_min[setup_btn], 150, 150);
      } else if (val == 2) {
        M5.Lcd.fillRect(0, 0, 320, 240, WHITE);
        break;
      }

    }
    if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 300)) {

      if (val == 0) { //max값 수정
        dust_gate.ang_max[setup_btn] += 2;
        M5.Lcd.drawString((String)dust_gate.ang_max[setup_btn], 10, 150);
      } else if (val == 1) {
        dust_gate.ang_min[setup_btn] += 2;

        M5.Lcd.drawString((String)dust_gate.ang_min[setup_btn], 150, 150);
        ;
      } else if (val == 2) {
        M5.Lcd.fillRect(0, 0, 320, 240, WHITE);
        break;
      }
    }
    if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 300)) {
      val++;
      switch (val) {
        case 0:
          M5.Lcd.drawString("MAX ANG   ", 10, 200);
          break;
        case 1:
          M5.Lcd.drawString("MIN ANG   ", 10, 200);
          break;
        case 2:
          M5.Lcd.drawString("MOTOR SET", 10, 200);
          break;
      }

      if (val == 3) {
        val = 0;
      }


    }

  }
}


//서버 테스트용
// Replaces placeholder with LED state value
String processor(const String& var) {
  //현제 스테이트 값
  Serial.println(var);
  if (var == "STATE") {

    if (wifi_too == 0) {
      ledState = "ON";
      wifi_too = 1;
    }
    else {
      ledState = "OFF";
      wifi_too = 0;
    }
    Serial.print(ledState);
    return ledState;
  }
  return String();
}


void loop() {

}
