
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
//Controller Condtrol;

///*** Constant Configuration ***///
int LTHRESH = 850;					// LEFT sensor level xxx
int CTHRESH = 850;					// CENTRE sensor level yyy
int RTHRESH = 850;					// RIGHT sensor level zzz


int  BaseSpeed = 115;

void directionController(int ldirection, int rdirection) {
	digitalWrite(M1, ldirection);
	digitalWrite(M2, rdirection);
  delay(100);
}

void motorController(float speedFactor) {
	Serial.print("right spped: ");
	Serial.println(BaseSpeed * speedFactor);
	analogWrite(E1, BaseSpeed * speedFactor);
	Serial.print("left spped: ");
	Serial.println(BaseSpeed * speedFactor);
	analogWrite(E2, BaseSpeed * speedFactor);
}

// Forward Backward Stop
void drive(int direction, float speedFactor){
	if (direction == -1) 
		motorController(0);
	else {
		directionController(direction, direction);
		motorController(speedFactor);
	}
}

void followLine(){
    int ir[3] = {0};
    drive(1, 1.0);
    while (1) {
    ir[0] = analogRead(LSENSOR);
	  Serial.print("LSENSOR: ");
	  Serial.println(ir[0]);
    ir[1] = analogRead(CSENSOR);
	  Serial.print("CSENSOR: ");
	  Serial.println(ir[1]);
    ir[2] = analogRead(RSENSOR);
	  Serial.print("RSENSOR: ");
	  Serial.println(ir[2]);
    if(ir[1] > CSENSOR && ir[2] < RTHRESH && ir[0] < LTHRESH){
        // stay forward
        Serial.println("forward");
        directionController(1,1);
    }
    else if (ir[2] > RTHRESH && ir[0] < LTHRESH) {
        // turn right
        Serial.println("turn right");
        directionController(1,0);
    }
    else if (ir[0] > LTHRESH && ir[2] < RTHRESH) {
        // turn left
        Serial.println("turn left");
        directionController(0,1);
    }
    else{
    while(ir[0] < LTHRESH && ir[1] < CTHRESH && ir[2] < RTHRESH){
      ir[0] = analogRead(LSENSOR);
      //Serial.print("LSENSOR: ");
      //Serial.println(ir[0]);
      ir[1] = analogRead(CSENSOR);
      Serial.print("CSENSOR: ");
      Serial.println(ir[1]);
      ir[2] = analogRead(RSENSOR);
      //Serial.print("RSENSOR: ");
      //Serial.println(ir[2]);
      Serial.println("Our of the Line!");
    }
    while(ir[0] > LTHRESH && ir[1] > CTHRESH && ir[2] > RTHRESH){
      ir[0] = analogRead(LSENSOR);
      //Serial.print("LSENSOR: ");
      //Serial.println(ir[0]);
      ir[1] = analogRead(CSENSOR);
      Serial.print("CSENSOR: ");
      Serial.println(ir[1]);
      ir[2] = analogRead(RSENSOR);
      //Serial.print("RSENSOR: ");
      //Serial.println(ir[2]);
      Serial.println("Too Bright!");
    }
    }
  }
    
}

#endif
