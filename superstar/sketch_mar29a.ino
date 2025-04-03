#include <AFMotor.h>
#include <Servo.h>
Servo S;
AF_DCMotor motorL(1);
AF_DCMotor motorR(2);
byte st;
byte move_flag = 0;
unsigned long match;
unsigned long srv_t;
void setup() {
  delay(85000);
  S.attach(10);
  forward(255);
  delay(400);
  forward(0);
  match = millis();
}
void loop() {
  // put your main code here, to run repeatedly:
  if (millis() - srv_t > 500) {
    st = !st;
    if (st == 0) {
      S.write(90);
    } else {
      S.write(0);
    }
    srv_t = millis();
  }
  if (move_flag == 0) {
    if (millis() - match < 11000) {
      byte ld = digitalRead(15);
      byte rd = digitalRead(14);
      if (ld == 0 and rd == 0) {
        forward(255);
      } else if (ld == 0 and rd == 1) {
        left(255);
      } else if (ld == 1 and rd == 0) {
        right(255);
      }
    } else {
      stop();
      move_flag = 1;
    }
  } else if (move_flag == 1) {
    forward(255);
    delay(100);
    stop();
    move_flag = 2;
  } else {
    stop();
  }
}
void stop() {
  motorL.run(RELEASE);
  motorR.run(RELEASE);
}
void forward(byte sp) {
  motorL.setSpeed(sp);
  motorL.run(FORWARD);
  motorR.setSpeed(sp);
  motorR.run(FORWARD);
}
void left(byte sp) {
  motorL.setSpeed(sp*0.25);
  motorL.run(FORWARD);
  motorR.setSpeed(sp);
  motorR.run(FORWARD);
}
void right(byte sp) {
  motorL.setSpeed(sp);
  motorL.run(FORWARD);
  motorR.setSpeed(sp*0.25);
  motorR.run(FORWARD);
}
void debug_digit_bls() {
  byte ld = digitalRead(15);
  byte rd = digitalRead(14);
  Serial.print("ld = ");
  Serial.print(ld);
  Serial.print(" rd = ");
  Serial.println(rd);
}