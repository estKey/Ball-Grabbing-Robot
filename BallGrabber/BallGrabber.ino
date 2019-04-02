/*
 Name:		BallGrabber.ino
 Created:	2019/4/1 12:26:24
 Author:	estKey
*/
#include "stdafx.h"

int sensorPins[7] = {};
int controllerPins[5] = {};

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.flush();
	// Lisiten  Port
	Serial.begin(9600);
	sensor.attach(sensorPins);
	robot.attach(controllerPins);
}

// the loop function runs over and over again until power down or reset
void loop() {
	Serial.println("ELEC 299 Robotics Group 16");
	initRobot();
	int index = 0;
	//int index = choosePath();
	process(path[index]);
	delay(1000);
	Serial.println("Press Bumper to restart");
	waitBumper();
}
