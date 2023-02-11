/*
메모리 저장관련 코드 입니다. 
특별한 경우가 아니라면 놔둡니다.
*/

void memMenu(void) {

  
  uint8_t i, h;
 uint8_t w, d;

 while(1){
  u8g2.setFont(u8g_font_cu12);
  u8g2.firstPage();
  do {
    u8g2.setFontRefHeightText();
    u8g2.setFontPosTop();
    u8g2.drawFrame(0, 0, 128, 64);
    u8g2.drawLine(60, 5, 60, 59);
    u8g2.drawLine(60, 34, 128, 34);
    u8g2.drawBitmap( 10, 0, 5, 64, mem);
    u8g2.drawBitmap(73, 33, 5, 18, mem1);
    u8g2.drawBitmap(73, 1, 5, 18, mem2);
    u8g2.setCursor(80, 48);
    u8g2.print(router);

    h = u8g2.getFontAscent() - u8g2.getFontDescent();
    w = u8g2.getWidth();
    for ( i = 0; i < MEM_ITEMS; i++ ) {
      d = (w - u8g2.getStrWidth(mem_strings[i]) / 5);
    //  u8g2.setDefaultForegroundColor();
      if ( i == Running) {
        u8g2.drawFrame(10, i * h + 1, w / 3 - 1, h + 2);
      }

    }
    if (Running == 0) {
      EEPROM.get(1,ver);
      u8g2.setCursor(77, 15);
      u8g2.print(ver);
    }
    else if (Running == 1) {
      EEPROM.get(1,ver);
      u8g2.setCursor(77, 15);
      u8g2.print(ver);
    }
    else if (Running == 2) {
      EEPROM.get(2,ver1);
      u8g2.setCursor(77, 15);
      u8g2.print(ver1);
    }
    else if (Running== 3) {
      u8g2.setCursor(77, 15);
      u8g2.print(EEPROM.get(2,ver1));
    }
  } while ( u8g2.nextPage() );

 }
}
