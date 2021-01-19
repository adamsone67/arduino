#include <Arduino.h>
#include <U8g2lib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SimpleDHT.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // if you use Hardware I2C port, full framebuffer, size = 1024 bytes

SimpleDHT11 dht11(3);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// various program variables
byte temperature = 0;   // 
byte humidity = 0;

String lblTemp = "TEMP: ";
String lblHum = " HUM: ";
 
void setup() {
  initDHT();
  initDisplay();
}

void loop(void) {

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.print("HELLO");
  display.

  display.display();
  delay(2000);

}


void initDHT() {
  // nothing to do!
}

void initDisplay() {
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // I2C address for Grove Beginner kit SSD1306 is 0x3c
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.setRotation(2);
  display.clearDisplay();
  
}

void readTemp() {
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }
}

void displayTemp() {
}
