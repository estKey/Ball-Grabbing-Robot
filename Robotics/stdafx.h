
#ifndef stdafx_h
#define stdafx_h

#include <Servo.h>
#include "QSerial.h"
#include "Info.h"

Info teamInfo;
// Coordinate
typedef struct _Coord {
  int x;
  int y;
}Coord;

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

//
#define IRRange				A0
// line tracker for recieving IR light
#define LSENSOR				A1
#define CSENSOR				A2
#define RSENSOR				A3
//
#define GripFSR				A4

// G:0(OPEN)-180(CLOSED), T:~100(GRAB)-160(CARRY), P:90
Servo Pan, Tilt, Grab;
//
QSerial IRReceiver;
//
//Controller Control;

///*** Constant Configuration ***///
int LTHRESH = 400;					// LEFT sensor level xxx
int CTHRESH = 400;					// CENTRE sensor level yyy
int RTHRESH = 400;					// RIGHT sensor level zzz

void waitBumper(){
  while (digitalRead(LeftBumper) == HIGH && digitalRead(RightBumper) == HIGH) { delay(1); }
  Serial.print("Triggered");
  delay(1000);
}

int ReceiveIR() {
  int rec = IRReceiver.receive(200);
  while (rec == 0 || rec == -1 || rec == -2) {
    rec = IRReceiver.receive(200);
  }
  Serial.println(rec);
  return rec;
}

void printLineLevel(int ir[]){
    Serial.print("LSENSOR: ");
    Serial.println(ir[0]);
    Serial.print("CSENSOR: ");
    Serial.println(ir[1]);
    Serial.print("RSENSOR: ");
    Serial.println(ir[2]);
}

void printMotorSpeed(float lspeed, float rspeed){
  Serial.print("right spped: ");
  Serial.println(rspeed);
  Serial.print("left spped: ");
  Serial.println(lspeed);
}

void directionController(int ldirection, int rdirection){
    digitalWrite(leftDirection, ldirection);
    digitalWrite(rightDirection, rdirection);
}

void motorController(float lspeed, float rspeed) {
	analogWrite(leftSpeed, rspeed);
	analogWrite(rightSpeed, lspeed);
  printMotorSpeed(lspeed, rspeed);
}

void goStraight(int direction, float speed){
	if (direction == -1) 
		motorController(0, 0);
	else {
		directionController(direction, direction);
		motorController(speed, speed);
	}
}

// -1 left 0 full turn 1 right
void pivot(int direction){
  Serial.println("Pivot");
  motorController(130,130);
  if(direction == 0){//turn left
    while(analogRead(CSENSOR) < RTHRESH)
      directionController(1,0);
  }else if(direction == 2){//turn right
    while(analogRead(CSENSOR) < RTHRESH)
      directionController(0,1);
  }else{
      while(analogRead(CSENSOR) < RTHRESH)
      directionController(1,0);
      while(analogRead(CSENSOR) < RTHRESH)
      directionController(1,0);
  }
  directionController(1,1);
  motorController(0,0);
  Serial.println("Done Pivot");
}

void followLine(){
  while(1){
    int ir[3] = {0};
    ir[0] = analogRead(LSENSOR);
    ir[1] = analogRead(CSENSOR);
    ir[2] = analogRead(RSENSOR);
    //printLineLevel(ir);

    // Forward direction
    directionController(1,1);

    if(ir[0] > LTHRESH) //turn left
         motorController(0,90);
    else if(ir[2] > RTHRESH)//turn right
         motorController(90,0);
    else if(ir[0] > LTHRESH && ir[1] > CTHRESH && ir[2] > RTHRESH) break;
    else motorController(90,90);
  }
  Serial.println("Meet Intersection");
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
  waitBumper();
  Serial.println("Starting");
  initArm();
  }

int choosePath(){
  int data = 0;
  while (data != '0' && data != '1' && data != '2') {
    data = ReceiveIR();
  }
  switch (data)
  {
  case '0': return 0;
  case '1': return 1;
  case '2': return 2;
  default:
    Serial.println("Invalid IR Signal");
    return -1;
  }
}

Coord getRoute(Coord start, Coord dist)
{
  return { (start.x - dist.x), (start.y - dist.y) };
}

int *getInstruction(Coord route) {
  int instruction[2] = { 0 };
  if (route.x == 0) {
    instruction[0] = -1;
    instruction[1] = route.y;
  }
  else {
    instruction[0] = 1;
    instruction[1] = route.x;
  }
  return instruction;
}

void tracePath(Coord path[]){
  Serial.println("Start to trace path");
  for (int i = 0; i < 2; i++)
  {
    Coord route = getRoute(path[i], path[i + 1]);
    int *instruction = getInstruction(route);
    pivot(instruction[0] == -1);
    for(int i = 0; i < instruction[1]; i++){
      followLine();
    }
  }
}

Coord *reverse(Coord path[]){
  Coord dist[3];
  for(int i = 0; i < 3; i++)
    dist[i] = path[3-i];
  return dist;
}

void process(Coord path[][3]){
  for(int i = 0; i < 5; i++){
    tracePath(path[i]);
    while (digitalRead(LeftBumper) == HIGH && digitalRead(RightBumper) == HIGH) { delay(1); }
    goStraight(0, 100);
    delay(1000);
    goStraight(-1, 0);
    catchBall();
    goStraight(0, 100);
    delay(1000);
    goStraight(-1, 0);
    pivot(0);
    tracePath(reverse(path[i]));
    while (digitalRead(LeftBumper) == HIGH && digitalRead(RightBumper) == HIGH) { delay(1); }
    depositBall(); 
    delay(100);
    pivot(0);
  }
}

#endif
