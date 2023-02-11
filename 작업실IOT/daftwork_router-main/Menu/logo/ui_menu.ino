

/*

 수동 이동 메뉴.
 1틱당 이동 거리를 조절하고 싶다면 
 step_up( )  안의 값을 수정하면 된다. 

*/

void updateact(void) {
  if ( uiKeyCode != KEY_NONE && last_key_code == uiKeyCode ) {
    return;
  }
  last_key_code = uiKeyCode;
  switch (units) {
    case KEY_NEXT:
       if(ver2 == 4.5) {
        step_up(2);  
      } else if (ver == 0) {
        step_up(0);
      }
      router += (0.5 + ver2);
      menu_redraw_required = 1;
   
      break;
    case KEY_PREV:
        if (ver2 == 4.5) {
        step_down(2);
      } else if (ver == 0) {
        step_down(0);
      }
      menu_redraw_required = 1;
      router -= (0.5 + ver2);
  
      break;
    case KEY_SELECT:
      if (toogle == 1) {
        ver2 = 4.5;  // <------------1틱당 이동 거리이다. 4.5라고 적으면 5mm를 이동한다. 9.5라 적으면 10mm를 이동한다. 
        toogle = 0;
      } else {
        ver2 = 0;   //<-------------0이라고 되어 있는 것이 기본 값이다. 0.5mm 이동한다. 적혀 있는 값에 0.5를 더한 값이 이동된다. 
        toogle = 1;
      }
      break;
    case KEY_BACK:
      menu_state = 1;
      menu_redraw_required = 1;
      break;
  } 

}

void actMenu(){

 // u8g2.setFont(u8g_font_fub14);
  u8g2.firstPage();
  do {
    u8g2.setCursor(34, 2);
    u8g2.print("position");
    u8g2.drawFrame(0, 0, 128, 64);
    u8g2.drawLine(28, 20, 128, 20);
    u8g2.drawBitmap( 2, 3, 3, 59, atr);
    u8g2.setCursor(28, 40);
    u8g2.print(router);
    u8g2.print("mm");
    if (ver2 == 4.5) {
      u8g2.drawBitmap( 6, 20, 2, 15, zero3);
    } else if (ver2 == 0) {
      u8g2.drawBitmap( 6, 30, 2, 15, zero4);
    }
  } while ( u8g2.nextPage() );
}
