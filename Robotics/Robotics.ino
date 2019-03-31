#include "stdafx.h"

void setup() {
  Serial.flush(); 
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
  
  while (digitalRead(LeftBumper) == HIGH && digitalRead(RightBumper) == HIGH) { delay(1); }
  catchBall(); 
  while (digitalRead(LeftBumper) == HIGH && digitalRead(RightBumper) == HIGH) { delay(1); }
  depositBall(); 
  
  //followLine();
  //pivot(0);
  delay(1000);
  Serial.println("Press Bumper to restart");
  waitBumper();
}
