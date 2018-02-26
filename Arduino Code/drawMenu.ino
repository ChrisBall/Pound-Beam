void drawMenu() {
  u8g2.firstPage();
  do {
    draw();
  } while ( u8g2.nextPage() );

  //  u8g2.clearBuffer();          // clear the internal memory (this method only used with a full buffer)
  //  draw();
  //  u8g2.sendBuffer();          // transfer internal memory to the display - takes time, so only do this when pressing buttons to avoid latency
}

void draw() {
  u8g2.setFont(u8g2_font_timB12_tr);
  
  u8g2.setCursor(1, 12);
  u8g2.print(sm.getFundamentalName() + " " + sm.getScaleName());
  
  u8g2.setCursor(1, 24);
  u8g2.print(scaleRange); u8g2.print(" notes");
  
  u8g2.setCursor(1, 36);
  u8g2.print(minRange/10);u8g2.print("cm");

  u8g2.setCursor(1, 48);
  u8g2.print(maxRange/10);u8g2.print("cm");
  
  u8g2.setCursor(1, 60);
  u8g2.print("Inst: "); u8g2.print(midiInstrument);

  u8g2.drawFrame(0, activeMenuInput * 12, 127, 12);
}

