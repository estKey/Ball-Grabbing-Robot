#pragma once
#include "Sensor.h"
#include "Controller.h"

#define LINETHRESH 670
// Coordinate
typedef struct _Coord {
	int x;
	int y;
} Coord;

Coord path[3][5][3] = {0};

Sensor sensor;
Controller robot;

void waitBumper() {
	while (sensor.isTriggered()) { delay(1); }
	Serial.print("Triggered");
	delay(1000);
}


void goStraight(int direction, float speed) {
	if (direction == -1)
		robot.setSpeed(0, 0);
	else {
		robot.setDir(direction, direction);
		robot.setSpeed(speed, speed);
	}
}

// -1 left 0 full turn 1 right
void pivot(int direction) {
	Serial.println("Pivot");
	robot.setSpeed(130, 130);
	if (direction == 0) {//turn left
		while (analogRead(CSENSOR) < LINETHRESH)
			robot.setDir(1, 0);
	}
	else if (direction == 2) {//turn right
		while (analogRead(CSENSOR) < LINETHRESH)
			robot.setDir(0, 1);
	}
	else {
		while (analogRead(CSENSOR) < LINETHRESH)
			robot.setDir(1, 0);
		while (analogRead(CSENSOR) < LINETHRESH)
			robot.setDir(1, 0);
	}
	robot.setDir(1, 1);
	robot.setSpeed(0, 0);
	Serial.println("Done Pivot");
}

void followLine() {
	int *ir;
	while (1) {
		ir = sensor.readLine();
		//ir[0] = analogRead(LSENSOR);
		//ir[1] = analogRead(CSENSOR);
		//ir[2] = analogRead(RSENSOR);
		//printLineLevel(ir);

		// Forward direction
		robot.setDir(1, 1);

		if (ir[0] > LINETHRESH) //turn left
			robot.setSpeed(0, 90);
		else if (ir[2] > LINETHRESH)//turn right
			robot.setSpeed(90, 0);
		else if (ir[0] > LINETHRESH && ir[1] > LINETHRESH && ir[2] > LINETHRESH) break;
		else robot.setSpeed(90, 90);
	}
	Serial.println("Meet Intersection");
}

boolean grabBall() {
	int force = 0,
		sensor = 0;
	while (sensor < 200) {
		robot.setGrab(force++);
		sensor = analogRead(GripFSR);
	}
	Serial.println("Ball Grabed.");
	return true;
}

void initArm() {
	robot.setPan(90);
	robot.setArm(180);
	robot.setGrab(0);
}

void catchBall() {
	Serial.println("Catchinging Ball...");
	robot.setPan(90);
	robot.setArm(90);
	//robot.setGrab(0);
	if (grabBall())
		robot.setArm(180);
}

void depositBall() {
	Serial.println("Depositing Ball...");
	robot.setArm(90);
	delay(1000);
	robot.setGrab(0);
	Serial.println("Ball Deposited.");
}

void initRobot() {
	Serial.println("Press Bumper to Start");
	waitBumper();
	Serial.println("Starting");
	initArm();
}

int choosePath() {
	int data = sensor.receiveIR();
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

void tracePath(Coord path[]) {
	Serial.println("Start to trace path");
	for (int i = 0; i < 2; i++)
	{
		Coord route = getRoute(path[i], path[i + 1]);
		int *instruction = getInstruction(route);
		pivot(instruction[0] == -1);
		for (int i = 0; i < instruction[1]; i++) {
			followLine();
		}
	}
}

Coord *reverse(Coord path[]) {
	Coord dist[3];
	for (int i = 0; i < 3; i++)
		dist[i] = path[3 - i];
	return dist;
}

void process(Coord path[][3]) {
	for (int i = 0; i < 5; i++) {
		tracePath(path[i]);
		while (sensor.isTriggered()) { delay(1); }
		goStraight(0, 100); // go backwards a little bit
		delay(1000);
		goStraight(-1, 0);
		catchBall();
		goStraight(0, 100);
		delay(1000);
		goStraight(-1, 0);
		pivot(0);
		tracePath(reverse(path[i]));
		while (sensor.isTriggered()) { delay(1); }
		depositBall();
		delay(100);
		pivot(0);
	}
}

/*
void printLineLevel() { Serial.println(sensor.getLineLevel); }
void printMotorSpeed() { Serial.println(robot.getSpeed); }
void printDirection() { Serial.println(robot.getDir); }
*/
