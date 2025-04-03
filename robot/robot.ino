#define robotID 253
#define DIO 7
#define CLK 8

#include "GyverTM1637.h"

GyverTM1637 disp(CLK, DIO);

byte data[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  disp.clear();
  disp.brightness(7);
}

void loop() {
  if (Serial.available() > 0) {
    byte startByte = Serial.read();
    while (startByte != robotID) {
      startByte = Serial.read();
    }
    Serial.readBytes(data, 10);
  }
  delayMicroseconds(200);
  disp.clear();
  disp.displayInt(data[9]);
}
