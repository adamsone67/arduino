#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

int BTN = 6;
int BZR = 5;
int LED = 4;
int KNOB = A0;

boolean buzzerEnabled = false;
int freq = 0;

void setup(void) {
  pinMode(BTN, INPUT);
  pinMode(BZR, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(KNOB, INPUT);
  u8g2.setDisplayRotation(U8G2_R2);
  u8g2.begin();
  randomSeed(analogRead(A1));
}

void loop(void) {
  delay(150);
  boolean on = (digitalRead(BTN)==HIGH);
  if (on) {
    buzzerEnabled = (analogRead(KNOB)>512);
    drawDice();
    blinkLED(); 
  }
}

void blinkLED() {
  for (int i=0; i<3; i++) {
    digitalWrite(LED, HIGH);
    if (buzzerEnabled) tone(BZR, freq);
    delay(150);
    if (buzzerEnabled) noTone(BZR);
    digitalWrite(LED, LOW);
    delay(250);
  }
}

void beep() {
  tone(BZR, freq);
  delay(150);
  noTone(BZR);
}

void drawDice() {
  u8g2.clearBuffer();
  u8g2.sendBuffer();
  int a = randomRoll();
  int b = randomRoll();
  freq = (1000 * a) + (100 * b);
  drawDie(0,a);
  drawDie(1,b);
  u8g2.sendBuffer();
}

int randomRoll() {
  return (random(10000)%6) + 1;
}

void drawDie(int pos, int value) {

  int offset = pos * 40;
  
  int L = offset + 7;
  int R = offset + 28;
  int T = 8;
  int B = 28;
  int Cx = offset + 18;
  int Cy = 18;

  int DIA = 3;

  boolean draw1 = (value > 3);
  boolean draw2 = (value==6);
  boolean draw3 = (value > 1);
  boolean draw4 = draw3;
  boolean draw5 = draw2;
  boolean draw6 = draw1;
  boolean draw7 = ((value%2)==1);
  
  u8g2.drawRFrame(pos * offset,0,36,36,6);
  if (draw1) u8g2.drawDisc(L,T,DIA);
  if (draw2) u8g2.drawDisc(L,Cy,DIA);
  if (draw3) u8g2.drawDisc(L,B,DIA);
  if (draw7) u8g2.drawDisc(Cx,Cy,DIA);
  if (draw4) u8g2.drawDisc(R,T,DIA);
  if (draw5) u8g2.drawDisc(R,Cy,DIA);
  if (draw6) u8g2.drawDisc(R,B,DIA);
  
}
