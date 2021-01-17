#include <Seeed_BMP280.h>

#include <Arduino.h>
#include <U8x8lib.h>
#include <dht.h>

#define DHT11_PIN 3

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);  // OLED display
BMP280 bmp280;                                                      // air pressure sensor
dht DHT;                                                            // temp/humidity sensor

byte temp = 0;
byte hum = 0;
float pressure = 0.0;

void setup(void) {
  initSensors();
  initDisplay();
}

void loop(void) {
  readSensors();
  updateDisplay();
  delay(2000);
}

void initSensors() {
  bmp280.init();
}

void readSensors() {
  DHT.read11(DHT11_PIN);
}

void initDisplay() {
  u8x8.begin();
  u8x8.setFlipMode(1);
  u8x8.setFont(u8x8_font_pxplustandynewtv_u);
}

void updateDisplay() {
  u8x8.drawString(0, 0, "TEMP: ");
  float fahrenheitTemp = (DHT.temperature * 1.8) + 32;
  u8x8.drawString(6, 0, String((int) fahrenheitTemp).c_str());
  u8x8.drawString(0, 1, " HUM: ");
  u8x8.drawString(6, 1, String((int) DHT.humidity).c_str());
  u8x8.drawString(0, 2, " PSI: ");
  pressure = bmp280.getPressure();
  u8x8.drawString(6, 2, String((pressure / 6895)).c_str());
  u8x8.drawString(0, 3, " ALT: ");
  u8x8.drawString(6, 3, String(bmp280.calcAltitude(pressure)).c_str());
  u8x8.refreshDisplay();
}
