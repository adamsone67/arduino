#include <Arduino.h>
#include <U8x8lib.h>
#include <IRremote.h>

/*
 *  Mini IR Remote
 *  
 *   Author: Eric Adamson
 *  Updated: 2/20/2020
 *  
 *  A super-simple infrared remote implementation.
 *  
 *  Requires the following hardware:
 *  
 *    * Arduino Uno (or equivalent)
 *    * SSD1306 OLED module (or similar)
 *    * an IR transmitter module (VS1838 or similar)
 *    * an analog potentiometer
 *    
 *  This project was developed using the Seeed Studio "Grove Beginner Kit"
 *  as a quick & dirty experiment, in hopes of coming up with a practical
 *  application of the kit.
 *  
 *  While the Grove Beginner Kit comes with a nice collection of sensors,
 *  it lacks a rotary encoder for menu navigation. Instead, we use an analog
 *  potentiometer, proportionally dividing its 1024-step range among menu
 *  items. Additionally, the menu is monitored by polling, rather than
 *  interrupts, mainly to keep things simple.
 */

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);
IRsend IrSender;

char* menu[] = { "ON/OFF", "MUTE", "VOL+", "VOL-", "SOURCE", "LEFT", "RIGHT", "ENTER" };
uint8_t codes[] = { 0x0C, 0x0D, 0x10, 0x11, 0x38, 0x5A, 0x5B, 0x5C };

int KNOB = A0;
int BTN = 6;
int menuPos = 0;
int arrayLen = 0;
boolean buttonPressed = false;

void setup() {
  arrayLen = sizeof(menu)/sizeof(char*);
  pinMode(KNOB, INPUT);
  pinMode(BTN, INPUT);
  initOLED();
}

void loop() {
  checkButton();
  if (buttonPressed) {
    sendCode();
    buttonPressed=false;
  } else {
    updateMenu();    
  }
}

void initOLED() {
  u8x8.begin();
  u8x8.setFlipMode(1);
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_u);
}

void checkButton() {
  buttonPressed=(digitalRead(BTN)==HIGH);
}

void updateMenu() {
  menuPos=arrayLen * analogRead(KNOB)/1024;
  for (int i=0; i<arrayLen ; i++) {
    u8x8.noInverse();
    if (menuPos==i) u8x8.inverse();
    u8x8.drawString(0,i,menu[i]);
  }
}

void sendCode() {
  IrSender.sendRC6(0, codes[menuPos], 3, true);
}

void flashCurrentMenuItem() {
  for (int i=0; i<3; i++) {
    u8x8.inverse();
    u8x8.drawString(0,menuPos,menu[menuPos]);
    delay(750);
    u8x8.noInverse();
    u8x8.drawString(0,menuPos,menu[menuPos]);
    delay(200);
  }
}
