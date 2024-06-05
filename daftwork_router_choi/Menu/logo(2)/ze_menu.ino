/*
영점을 잡는 부분이다. 
*/


void updatezeo(void) {
  if ( uiKeyCode != KEY_NONE && last_key_code == uiKeyCode ) {
    return;
  }
  last_key_code = uiKeyCode;
  switch ( uiKeyCode ) {
    case KEY_NEXT:
      router += 4;
      menu_redraw_required = 1;
      break;
    case KEY_PREV:
      menu_redraw_required = 1;
      router -= 4;    
      break;
    case KEY_SELECT:
      menu_redraw_required = 1;
      router = 0;
      break;
    case KEY_BACK:
      menu_state = 1;
      menu_redraw_required = 1;
      break;
  }
       if(router >= 200){
        router = 200;
      }else if (router <= -200){
        router = -200;
      }
}


void zeroMenu(void) {

  u8g.setFont(u8g_font_cu12);
 
  u8g.firstPage();
  do {
     u8g.drawFrame(0, 0, 128, 64);
    u8g.drawBitmapP( 10, 10, 5, 52, zero);
    u8g.drawBitmapP( 83, 3, 3, 59, zero1);
    u8g.setPrintPos(15, 20);
    u8g.print(router);
  } while ( u8g.nextPage() );


}
