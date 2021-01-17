#include <Arduino.h>
#include <U8x8lib.h>
#include <dht.h>

#define DHT11_PIN 3

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);
dht DHT;

byte temp = 0;
byte hum = 0;

void setup(void) {
  initDisplay();
}

void loop(void) {
  readSensor();
  updateDisplay();
  delay(2000);
}

void readSensor() {
  DHT.read11(DHT11_PIN);
}

void initDisplay() {
  u8x8.begin();
  u8x8.setFlipMode(1);
  u8x8.setFont(u8x8_font_pxplustandynewtv_u);
}

void updateDisplay() {
  u8x8.drawString(0, 0, "TEMP: ");
  u8x8.drawString(6, 0, String(DHT.temperature).c_str());
  u8x8.drawString(0, 1, " HUM: ");
  u8x8.drawString(6, 1, String(DHT.humidity).c_str());
  u8x8.refreshDisplay();
}
