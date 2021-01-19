/*
 * IRreceiveDemo.cpp
 *
 * Demonstrates receiving IR codes with IRrecv
 *
 *  This file is part of Arduino-IRremote https://github.com/z3t0/Arduino-IRremote.
 *
 */

#include <IRremote.h>
#include <Arduino.h>
#include <U8x8lib.h>

int IR_RECEIVE_PIN = 7;
IRrecv IrReceiver(IR_RECEIVE_PIN);
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);  // OLED display

#define DISPLAY_WIDTH 16

// On the Zero and others we switch explicitly to SerialUSB
#if defined(ARDUINO_ARCH_SAMD)
#define Serial SerialUSB
#endif

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)
    delay(2000); // To be able to connect Serial monitor after reset and before first printout
#endif
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    // In case the interrupt driver crashes on setup, give a clue
    // to the user what's going on.
    Serial.println("Enabling IRin");
    IrReceiver.enableIRIn();  // Start the receiver
    IrReceiver.blink13(true); // Enable feedback LED

    Serial.print(F("Ready to receive IR signals at pin "));
    Serial.println(IR_RECEIVE_PIN);

    initDisplay();

}

void loop() {
    /*
     * Check if received data is available and if yes, try to decode it.
     * Decoded result is in the IrReceiver.decodedIRData structure.
     */
    if (IrReceiver.decode()) {
        // Print a short summary of received data
        IrReceiver.printIRResultShort(&Serial);
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            // We have an unknown protocol, print more info
            IrReceiver.printIRResultRawFormatted(&Serial, true);
        }
        Serial.println();
        updateDisplay();

#if !defined(ESP32)
        /*
         * Play tone, wait and restore IR timer
         */
        tone(5, 2200, 10);
        delay(11);
        IrReceiver.enableIRIn();
#endif

        IrReceiver.resume(); // Enable receiving of the next value
        /*
         * Check the received data
         */
        if (IrReceiver.decodedIRData.command == 0x11) {
            // do something
        }
    } else if (IrReceiver.results.overflow) {
        IrReceiver.results.overflow = false;
        // no need to call resume, this is already done by decode()
        Serial.println(F("Overflow detected"));
    }
}

  void initDisplay() {
    u8x8.begin();
    u8x8.setFlipMode(1);
    u8x8.setFont(u8x8_font_8x13B_1x2_f);
    writeHeader();
  }

  void writeHeader() {
    u8x8.setInverseFont(1);
    u8x8.drawString(0, 0, "-= IR DECODER =-");
    u8x8.setInverseFont(0);
    
  }
  
  void updateDisplay() {

    writeHeader();
    
    // write protocol
    
    u8x8.drawString(0, 2, " TYPE:");
    String protocol = IrReceiver.getProtocolString();
    int plen = protocol.length();
    u8x8.drawString(7, 2, String("         ").c_str());
    u8x8.drawString(7, 2, protocol.c_str());

    // write IR code length
 
    u8x8.drawString(0, 4, " SIZE:");
    String size = String(sprintf(IrReceiver.results.bits, DEC));
    size+="-BIT";
    u8x8.drawString(7, 4, size.c_str());

    // write IR code
    
    u8x8.drawString(0, 6, " CODE:");
    String code = String(IrReceiver.results.value, HEX);
    code.toUpperCase();
    u8x8.drawString(7, 6, code.c_str());
    u8x8.refreshDisplay();
    
  }

  
  void updateDisplayB() {

    // write protocol
    
    String protocol = IrReceiver.getProtocolString();
    int plen = protocol.length();
    u8x8.drawString(0, 0, String("         ").c_str());
    u8x8.drawString(0, 0, protocol.c_str());

    // write IR code length
    
    String size = String(sprintf(IrReceiver.results.bits, DEC));
    size+="-BIT";
    u8x8.drawString(0, 2, size.c_str());

    // write IR code
    
    String code = String(IrReceiver.results.value, HEX);
    code.toUpperCase();
    u8x8.drawString(0, 4, code.c_str());

    u8x8.refreshDisplay();
    
  }
