#include <U8x8lib.h>
#include <U8g2lib.h>

#include <Arduino.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {
  randomSeed(analogRead(A4));
  u8g2.begin();
}

void loop(void) {
  u8g2.clearBuffer();
  drawDie(0, roll());
  drawDie(1, roll());
  u8g2.sendBuffer();
  delay(250);
}

int roll() {
  return ((random(666))%6)+1;
}

void drawDie(int pos, int val) {
  
  int offset = (pos==0) ? 0 : 42;
  
  boolean show1 = (val > 3);
  boolean show2 = (val == 6);
  boolean show3 = (val > 1);;
  boolean show4 = show3;
  boolean show5 = show2;
  boolean show6 = show1;
  boolean show7 = (val%2==1);
  
  u8g2.drawRFrame(offset + 3, 18, 36, 36, 6);
  if (show1) u8g2.drawDisc(offset + 12, 26, 3);
  if (show2) u8g2.drawDisc(offset + 12, 35, 3);
  if (show3) u8g2.drawDisc(offset + 12, 44, 3);
  if (show4) u8g2.drawDisc(offset + 28, 26, 3);
  if (show5) u8g2.drawDisc(offset + 28, 35, 3);
  if (show6) u8g2.drawDisc(offset + 28, 44, 3);
  if (show7) u8g2.drawDisc(offset + 20, 35, 3);
}
