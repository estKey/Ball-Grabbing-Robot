
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
			


int  BaseSpeed = 115;





int followLine(){


    
  
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

    
    if (ir[0] > THRESH) {             //turn left
         analogWrite(leftSpeed, 30);
         analogWrite(rightSpeed, 90);
         //delay(10);
         

    }
    
    
    else if (ir[2] > THRESH) {          //turn right
        analogWrite(leftSpeed, 90);
        analogWrite(rightSpeed, 30);
        //delay(10);
        
    }

    else if (ir[0] > THRESH && ir[1] > THRESH && ir[2] > THRESH){
      int out = 1;
    }
    
    else{               //keep straight
      analogWrite(leftSpeed, 90);
      analogWrite(rightSpeed, 90);
    
    }
}

#endif