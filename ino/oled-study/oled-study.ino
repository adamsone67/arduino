#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 16, /* data=*/ 17);   // ESP32 Thing, HW I2C with pin remapping

int dir = 2;

int X_OFFSET = 56;
int Y_OFFSET = 126;

void setup(void) {
  pinMode(9, OUTPUT);
  digitalWrite(9, 0);	// default output in I2C mode for the SSD1306 test shield: set the i2c adr to 0

  u8g2.begin();
}

void drawLogo(void) {
  u8g2.setFontMode(1);	// Transparent
  u8g2.setFontDirection(dir);
  u8g2.setFont(u8g2_font_luBS18_tn);
  drawText("ABC", 0, 0);
}

void drawText(String text, int x, int y) {
  u8g2.drawStr(X_OFFSET-x,Y_OFFSET-y,text[0]);
}

void loop(void) {
  u8g2.clearBuffer();
  drawLogo();
  u8g2.sendBuffer();
  delay(1000);
}
