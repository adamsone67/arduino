#include <Arduino.h>
#include <U8x8lib.h>

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);  // OLED display

String type = "???";
String size = "???";
String data = "AABBCCDD";

// runs once, upon startup
void setup(void) {
  initSensors();
  initDisplay();
}

// runs repeatedly, forever after
void loop(void) {
  readSensors();
  updateDisplay();
  delay(2000);
}

void initSensors() {
}

void readSensors() {
}

void initDisplay() {
  u8x8.begin();
  u8x8.setFlipMode(1);
  u8x8.setFont(u8x8_font_pxplustandynewtv_u);
}

void updateDisplay() {
  u8x8.drawString(0, 0, "-= IR DECODER =-");
  u8x8.drawString(0, 2, " TYPE:");
  u8x8.drawString(7, 2, type.c_str());
  u8x8.drawString(0, 3, " SIZE:");
  u8x8.drawString(7, 3, size.c_str());
  u8x8.drawString(0, 4, " DATA:");
  u8x8.drawString(7, 4, data.c_str());
  u8x8.refreshDisplay();
}
