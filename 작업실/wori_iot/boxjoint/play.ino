void joint_cal(int i) {

  joint_play_a[i] = joint_gap[i] / (blade - 1.0);
  joint_play_b[i] = joint_gap[i] % (blade - 1.0);

}

void motor() {

  if (digitalRead(z_switch) == LOW) {
    value++;
    stepper.runToNewPosition((blade - 1.0) * (Move_01 * 10))
    count_01 = joint_play_a[i]+1;  //카운트 표시
    M5.Lcd.drawNumber(count_01, 2, 5, 120 ); //화면에 카운트 표시
    count--;
    if (joint_play_a[i] == value) {
      stepper.runToNewPosition(joint_gap[0]*Move_01 * 10);
    }

  }

}
