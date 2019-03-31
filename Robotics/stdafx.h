
#ifndef stdafx_h
#define stdafx_h

#include <Servo.h>
#include "QSerial.h"


int RightWheelEncoder = 13;
int LeftWheelEncoder = 12;
int IRPin = 11;
//right motor
int ServoGrab = 10;
int ServoTilt = 9;
int ServoPan = 8;
int leftSpeed = 6;
int leftDirection = 7;
//left motor
int rightSpeed = 5;
int rightDirection = 4;
//10k pull up;
int LeftBumper = 3;
int RightBumper = 2;


#define IRRange				A0

// line tracker for recieving IR light
#define LSENSOR				A1
#define CSENSOR				A2
#define RSENSOR				A3

#define GripFSR				A4

// G:0(OPEN)-180(CLOSED), T:~100(GRAB)-160(CARRY), P:90
Servo Pan, Tilt, Grab;
//
QSerial IRReceiver;
//
//Controller Control;

///*** Constant Configuration ***///
int LTHRESH = 640;					// LEFT sensor level xxx
int CTHRESH = 640;					// CENTRE sensor level yyy
int RTHRESH = 640;					// RIGHT sensor level zzz

void directionController(int direction){
    digitalWrite(leftDirection, direction);
    digitalWrite(rightDirection, direction);
}

void motorController(float lspeed, float rspeed) {
	Serial.print("right spped: ");
	Serial.println(rspeed);
	analogWrite(leftSpeed, rspeed);
	Serial.print("left spped: ");
	Serial.println(lspeed);
	analogWrite(rightSpeed, lspeed);
}

void forward(int direction, float speed){
	if (direction == -1) 
		motorController(0, 0);
	else {
		directionController(direction);
		motorController(speed, speed);
	}
}

void followLine(){
    int ir[3] = {0};
    //while (ir[0] < LTHRESH && ir[1] < CTHRESH && ir[2] < RTHRESH) {
    ir[0] = analogRead(LSENSOR);
	  Serial.print("LSENSOR: ");
	  Serial.println(ir[0]);

    ir[1] = analogRead(CSENSOR);
    Serial.print("CSENSOR: ");
    Serial.println(ir[1]);

    ir[2] = analogRead(RSENSOR);
    Serial.print("RSENSOR: ");
    Serial.println(ir[2]);

    // Forward direction
    directionController(1);

    if (ir[0] > LTHRESH) //turn left
         motorController(0,90);
         //delay(10);
    else if (ir[2] > RTHRESH)//turn right
         motorController(90,0);
        //delay(10);
    else motorController(90,90);
}

// Grabber Servo
boolean grabBall(){
  int force = 0,
      sensor = 0;
  while(sensor < 200){
    Grab.write(force++);
    sensor = analogRead(GripFSR);
  }
  Serial.println("Ball Grabed.");
  return true;
}

void initArm(){
  Pan.write(90);
  Tilt.write(180);
  Grab.write(0);
}

void catchBall(){
  Serial.println("Catchinging Ball...");
  Pan.write(90);
  Tilt.write(90);
  Grab.write(0);
  if(grabBall())
    Tilt.write(180);
}

void depositBall(){
  Serial.println("Depositing Ball...");
  Tilt.write(90);
  delay(1000);
  Grab.write(0);
  Serial.println("Ball Deposited.");
}

void initRobot(){
  Serial.println("Press Bumper to Start");
  while (digitalRead(LeftBumper) == HIGH && digitalRead(RightBumper) == HIGH) { delay(1); }
  Serial.println("Starting");
  initArm()
;}
#endif
