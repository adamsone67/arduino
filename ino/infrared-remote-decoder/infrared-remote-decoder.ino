#include <IRremote.h>
#include <Arduino.h>
#include <U8x8lib.h>

// I/O pin definitions
  
  int IR_RECEIVE_PIN = 7;


// device declarations

  IRrecv rcvr(IR_RECEIVE_PIN);
  U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);  // OLED display

// other variables

// runs once, upon startup

  void setup(void) {
    Serial.begin(115200);
    pinMode(IR_RECEIVE_PIN, INPUT);
    initDisplay();
    initInfraredReceiver();
  }


// runs repeatedly, forever after

  void loop(void) {
    if (rcvr.decode()) {
      rcvr.printIRResultShort(&Serial);
//      updateDisplay();
      rcvr.resume();
    } else {
      Serial.println("ERROR");
    }
    delay(100);
  }


// initialize infrared receiver module

  void initInfraredReceiver() {
      rcvr.enableIRIn();  // start the receiver
      rcvr.blink13(true); // enable feedback LED
      Serial.print(F("Ready to receive IR signals at pin "));
      Serial.println(IR_RECEIVE_PIN);
  }


// initialize OLED display module
  
  void initDisplay() {
    u8x8.begin();
    u8x8.setFlipMode(1);
    u8x8.setFont(u8x8_font_pxplustandynewtv_u);
    updateDisplay();
  }

// update OLED display to reflect current IR sensor data

  void updateDisplay() {
    u8x8.drawString(0, 0, "-= IR DECODER =-");
    u8x8.drawString(0, 2, " TYPE:");
    u8x8.drawString(7, 2, rcvr.getProtocolString());
    u8x8.drawString(0, 3, " SIZE:");
    u8x8.drawString(7, 3, String(sprintf(rcvr.results.bits, DEC)).c_str());
    u8x8.drawString(0, 4, " CODE:");
    u8x8.drawString(7, 4, sprintf(rcvr.results.value, HEX));
    u8x8.refreshDisplay();
  }
