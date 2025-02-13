#include "SoftwareSerial.h"

#define robotID 252
#define rx 7;
#define tx 6;

int data[]; 

SoftwareSerial ArdSerial(rx, tx);

void setup() {
  pinMode(rx, INPUT);
  pinMode(tx, OUTPUT);
  ArdSerial.begin(9600);
}

void loop() {
  if (ArdSerial.available() > 0) {
    byte startByte = ArdSerial.read();
    while (startByte != robotID) {
      startByte = ArdSerial.read();
    } else {
      data = Serial.readbytes(9)
    }
  }
  Serial.println(data[0]);
}
