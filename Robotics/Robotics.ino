#include "stdafx.h"

void setup() {
  // Lisiten  Port
  Serial.begin(9600);
  // PinModes
  pinMode(LeftBumper, INPUT);
  pinMode(RightBumper, INPUT);
  pinMode(LeftWheelEncoder, INPUT);
  pinMode(RightWheelEncoder, INPUT);
  pinMode(rightSpeed, OUTPUT);
  pinMode(leftSpeed, OUTPUT);
  pinMode(rightDirection, OUTPUT);
  pinMode(leftDirection, OUTPUT);
  // Servo Configuration
  Pan.attach(ServoPan);
  Tilt.attach(ServoTilt);
  Grab.attach(ServoGrab);
  // IR Detector
  IRReceiver.attach(IRPin, -1);
}

void loop() {
  teamInfo.displayInfo();
  initRobot();
  delay(1000);
  /*
  while (digitalRead(LeftBumper) == HIGH && digitalRead(RightBumper) == HIGH) { delay(1); }
  catchBall(); 
  while (digitalRead(LeftBumper) == HIGH && digitalRead(RightBumper) == HIGH) { delay(1); }
  depositBall(); 
  */
  pivot();
  delay(1000);
}
