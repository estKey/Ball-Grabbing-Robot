
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


int  BaseSpeed = 115;

/*
void adjust(int dir){

  analogWrite(M1, );
  analogWrite(M2, );

  
}*/



/*
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
*/
void followLine(){


    
  
    int ir[3];
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

    digitalWrite(leftDirection, HIGH);
    digitalWrite(rightDirection, HIGH);

    
    if (ir[0] > LTHRESH) {//turn left
         analogWrite(leftSpeed, 0);
         analogWrite(rightSpeed, 90);
         //delay(10);
         

    }
    
    
    else if (ir[2] > RTHRESH) {//turn right
        analogWrite(leftSpeed, 90);
        analogWrite(rightSpeed, 0);
        //delay(10);
        
    }

    
    
    else{
      analogWrite(leftSpeed, 90);
      analogWrite(rightSpeed, 90);
    
    }
}

#endif
