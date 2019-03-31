#include "stdafx.h"

Coord path[3][5][3] = {{{2,0},{1,2},{0,2}},
                    {0},
                    {0}};

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
  int index = 0;
  //int index = choosePath();
  process(path[index]);
  delay(1000);
  Serial.println("Press Bumper to restart");
  waitBumper();
}
