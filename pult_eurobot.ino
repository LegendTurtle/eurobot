#define X1 A0
#define Y1 A1
#define X2 A2
#define Y2 A3
#define but1 2
#define but2 3
#define DELTA 25
#define ROBOT_ID 252
#define CLK 5
#define DIO 4

#include "GyverTM1637.h"

GyverTM1637 disp(CLK, DIO);
uint32_t Now, clocktimer;
boolean flag;

int start_x, start_y, cur_x, cur_y = 0;
int start_x2, start_y2, cur_x2, cur_y2 = 0;

int prognoz = 0;

bool orient1 = 0;
bool orient2 = 0;
bool but1_dat = 0;
bool but2_dat = 0;
int dest_y1 = 0;
int dest_y2 = 0;
int dest_x1 = 0;
int dest_x2 = 0;
bool b = 0;
bool b2 = 0;

void setPrognoz() {
  if (0 < dest_x1) {
    prognoz++;
  } else if (0 > dest_x1){
    prognoz--;
  }
  disp.clear();
  disp.displayInt(prognoz);
}

void send_data() {
  readBut();
  readStick();
  if (but2_dat) {
    setPrognoz();
    int data[] = { ROBOT_ID, 0, dest_x1, orient1, but1_dat, 0, dest_x2, orient2, but2_dat, prognoz };
    for (auto x : data) {
      Serial.write(x);
    }
  } else {
    int data[] = { ROBOT_ID, dest_y1, dest_x1, orient1, but1_dat, dest_y2, dest_x2, orient2, but2_dat, prognoz };
    for (auto x : data) {
      Serial.write(x);
    }
  }
}

void readBut() {
  delay(50);
  but1_dat = !digitalRead(but1);
  but2_dat = !digitalRead(but2);
}

void readStick() {
  cur_x = analogRead(X1);
  cur_y = analogRead(Y1);

  if (abs(start_x - cur_x) < DELTA and abs(cur_y - start_y) < DELTA) {
    dest_y1 = 0;
    dest_x1 = 0;
  } else {
    if (start_y - cur_y > 0) {
      dest_y1 = abs(map(cur_y, 512, 1023, 0, 255));
      orient1 = 1;
    } else {
      dest_y1 = abs(map(cur_y, 512, 1023, 0, 255));
      orient1 = 0;
    }
    dest_x1 = map(cur_x, 512, 1023, 0, 255);
  }




  cur_x2 = analogRead(X2);
  cur_y2 = analogRead(Y2);
  if (abs(start_x2 - cur_x2) < DELTA and abs(cur_y2 - start_y2) < DELTA) {
    dest_y2 = 0;
    dest_x2 = 0;
  } else {
    if (start_y2 - cur_y2 > 0) {
      dest_y2 = abs(map(cur_y2, 512, 1023, 0, 255));
      orient2 = 1;
    } else {
      dest_y2 = abs(map(cur_y2, 512, 1023, 0, 255));
      orient2 = 0;
    }
    dest_x2 = map(cur_x2, 512, 1023, 0, 255);
  }
}

void setup() {
  pinMode(but1, INPUT_PULLUP);
  pinMode(but2, INPUT_PULLUP);
  Serial.begin(9600);
  start_x = analogRead(X1);
  start_y = analogRead(Y1);
  start_x2 = analogRead(X2);
  start_y2 = analogRead(Y2);
  disp.clear();
  disp.brightness(7);
}

void debugPult() {
  readStick();
  readBut();
  if (but2_dat) {
    setPrognoz();
    Serial.println("Y1: " + (String)0 + " orient_y1: " + (String)orient1 + " X1: " + (String)dest_x1 + " button1: " + (String)but1_dat + " ----- Y2: " + (String)0 + " orient_y2: " + (String)orient2 + " X2: " + (String)dest_x2 + " button2: " + (String)but2_dat + " prognoz: " + (String)prognoz);
  } else {
    Serial.println("Y1: " + (String)dest_y1 + " orient_y1: " + (String)orient1 + " X1: " + (String)dest_x1 + " button1: " + (String)but1_dat + " ----- Y2:" + (String)dest_y2 + " orient_y2: " + (String)orient2 + " X2: " + (String)dest_x2 + " button2: " + (String)but2_dat + " prognoz: " + (String)prognoz);
  }
}


void loop() {
  send_data();
  //debugPult();
}
