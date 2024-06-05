
void Firebase_a() {  //테스트 완료
  if (Firebase.getString(firebaseData, "Room_2/Fan_01")) {  //창고 팬
    String value = firebaseData.stringData(); //값을 문자열로 받아와서 밸류 값에 넣는다.
    Serial.println(value);
    if (value.indexOf("Fan_01") != -1) {
      //기본
      bumo = 1;
      Serial.println("1번");
    }
    else if (value.indexOf("Fan_02") != -1) {
      //팬 on
      bumo = 2;
      Serial.println("2번");
    }
    else if (value.indexOf("Fan_03") != -1) {
      //팬 off
      bumo = 3;
      Serial.println("3번");
    }
    //기본값 "Fan_01";
    //on == Fan_02;
    //off == Fan_03;
  }
}
