
//팬 설정 


void fan_to(int fan_toogle) {

  if (fan_toogle == 1 ) {
    if (one_min < 60) {
      time_a();
      Serial.println("팬 on");
    digitalWrite(relay, HIGH); //릴레이 켜짐 
      if (one_min > 60) {
        flag = 0;
    one_min_t = true;
    digitalWrite(relay, LOW);
      }
    }
  } else {
    Serial.println("팬 off");
  digitalWrite(relay, LOW);
  }

}
