
#ifndef stdafx_h
#define stdafx_h

#include <Servo.h>
#include "QSerial.h"
//#include "Controller.h"


int RightWheelEncoder = 13;
int LeftWheelEncoder = 12;
int IRPin = 11;
//right motor
int ServoGrab = 10;
int ServoTilt = 9;
int ServoPan = 8;
int E1 = 6;
int M1 = 7;
//left motor
int E2 = 5;
int M2 = 4;
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
int LTHRESH = 900;					// LEFT sensor level xxx
int CTHRESH = 900;					// CENTRE sensor level yyy
int RTHRESH = 900;					// RIGHT sensor level zzz


int  BaseSpeed = 115;

void directionController(int direction) {
	digitalWrite(M1, direction);
	digitalWrite(M2, direction);
}

void motorController(float speedFactor) {
	Serial.print("right spped: ");
	Serial.println(BaseSpeed * speedFactor);
	analogWrite(E1, BaseSpeed * speedFactor);
	Serial.print("left spped: ");
	Serial.println(BaseSpeed * speedFactor);
	analogWrite(E2, BaseSpeed * speedFactor);
}

void drive(int direction, float speedFactor){
	if (direction == -1) 
		motorController(0);
	else {
		directionController(direction);
		motorController(speedFactor);
	}
}

void followLine(){
    int ir[3] = {0};
    while (ir[0] < LTHRESH && ir[1] < CTHRESH && ir[2] < RTHRESH) {
    ir[0] = analogRead(LSENSOR);
	Serial.print("LSENSOR: ");
	Serial.println(ir[0]);
    if (ir[0] < LTHRESH) {
        digitalWrite(E1, HIGH);
        digitalWrite(M1, HIGH);
        digitalWrite(E2, HIGH);
        digitalWrite(M2, HIGH);
    }
    ir[1] = analogRead(CSENSOR);
	Serial.print("CSENSOR: ");
	Serial.println(ir[1]);
    if (ir[0] < CTHRESH) {
        digitalWrite(E1, HIGH);
        digitalWrite(M1, HIGH);
        digitalWrite(E2, HIGH);
        digitalWrite(M2, HIGH);
    }
    ir[2] = analogRead(RSENSOR);
	Serial.print("RSENSOR: ");
	Serial.println(ir[2]);
    if (ir[0] < RTHRESH) {
        digitalWrite(E1, HIGH);
        digitalWrite(M1, HIGH);
        digitalWrite(E2, HIGH);
        digitalWrite(M2, HIGH);
    }
  }
}

#endif