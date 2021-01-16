/******************************************************************
 * 
 *  Demonstrates use of tone() function to drive the buzzer module.
 *  Turn knob to adjust frequency.
 * 
 */

int BUZZER = 5;
int KNOB = A0;

int freq = 0;

void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(KNOB, INPUT);
}

void loop() {
  freq = analogRead(KNOB);
  tone(BUZZER, 1124-freq);  
}
