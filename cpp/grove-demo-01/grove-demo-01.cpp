#include <Arduino.h>

const int LED=4;

// forward declarations (stinky old one-pass compilers require these!)
void blink(int device, int delayTime);

void setup() {
	pinMode(LED, OUTPUT);
}

void loop() {
	blink(LED, 500);
}

void blink(int device, int delayTime) {
	digitalWrite(LED, HIGH);
	delay(delayTime);
	digitalWrite(LED, LOW);
	delay(delayTime);
}

