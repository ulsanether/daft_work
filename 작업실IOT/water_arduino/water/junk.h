// bool Algo_play_set(int all_now_minute) {

//   bool delay_time_toogle = false;
//   bool pump_value;

//   Serial.println((all_now_minute % all_work_time));

//   switch ((all_now_minute % all_work_time)) {
//     case 0:
//       delay_time_toogle = true;
//       //Serial.print("작동 루프 들어감 all_now_minute: ");
//       Serial.println(all_now_minute);
//       break;
//   }

// #if how_int_pump == 1
//   if (delay_time_toogle == true || all_work_time == minute_60 && minute_60 != 0) {  //휴식 부터 하는 걸로 수정 하는게 나을것 같음.
//     real_now_work_time = all_now_minute + minute_60;

//     //Serial.print("펌프 작동 :");
//     Serial.println(real_now_work_time);
//     delay_time_toogle = false;
//     pump_value = true;
//     motor_play(1);
//   }
//   if (real_now_work_time == all_now_minute) {
//     //Serial.println("펌프 멈춤");
//     pump_value = false;
//     if (motor_pwm_power != 11) {
//       motor_play(0);
//     } else {
//       motor_play(1);
//     }
//   }
// #endif
// #if how_int_pump == 2
//   if (delay_time_toogle == true) {
//     //Serial.print("펌프 휴식 부터 :");
//     real_now_work_time = all_now_minute + rest_time;
//     delay_time_toogle = false;
//     pump_value = false;
//     if (motor_pwm_power != 11) {
//       motor_play(0);
//     } else {
//       motor_play(1);
//     }
//   }
//   if (real_now_work_time == all_now_minute || all_work_time == minute_60 && minute_60 != 0) {
//     //Serial.println("펌프 멈춤");
//     pump_value = true;
//     motor_play(1);
//   }
// #endif

//   return pump_value;
// }
