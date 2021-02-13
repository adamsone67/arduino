#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_LEDBackpack matrix = Adafruit_LEDBackpack();

uint8_t counter = 0;

uint8_t board[8] = { };
uint8_t neighbors[8][8] = { };

void setup() {
  matrix.begin(0x70);  // pass in the address
  initRandomizer();
  clear();
  randomize();
  updateDisplay();
  delay(1000);
}

void loop() {
  makeNextMove();
}

void clear() {
  matrix.clear();
  matrix.writeDisplay();
}

void initRandomizer() {
  randomSeed(analogRead(A0));
}

void randomize() {
  for (int i=0; i<8; i++) {
    board[i] = random(256);
  }
}

void updateDisplay() {
  for (int i=0; i<8; i++) {
    matrix.displaybuffer[i] = board[i];
  }
  matrix.writeDisplay();
}

void updateNeighborCounts() {
  for (int i=0; i<8; i++) {
    for (int j=0; j<8; j++) {
      updateNeighborCount(i, j);
    }
  }
}

void updateNeighborCount(int x, int y) {
  uint8_t count = 0;
  for (int i=-1; i<2; i++) {
    for (int j=-1; j<2; j++) {
      if (!((i==0)&&(j==0)) && isAlive(i, j)) count++;
    }
  }
  neighbors[x][y] = count;
}

void updatePopulation() {
  for (int i=0; i<8; i++) {
    for (int j=0; j<8; j++) {
      switch ((int) neighbors[i,j]) {
        case 0:
        case 1: setStatus(i, j, 0);
                break;
        case 2: 
        case 3:
      }
    }
  }
}

boolean isAlive(int x, int y) {
  uint8_t row = board[x];
  return (y & (1 << (x - 1)));
}

void makeNextMove() {
  updateNeighborCounts();
  updatePopulation();  
}

void setStatus(int x, int y, uint8_t value) {
  
}
