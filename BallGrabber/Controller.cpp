
#include "Arduino.h"
#include "Controller.h"


Controller::Controller()
{
	leftSpeed = 0;
	rightSpeed = 0;
	leftDirection = 0;
	rightDirection = 0;
	grabPin = -1;
	tiltPin = -1;
	panPin = -1;
	leftSpeedPin = -1;
	leftDirectionPin = -1;
	rightSpeedPin = -1;
	rightDirectionPin = -1;
	
}

void Controller::setupPins()
{
	Pan.attach(panPin);
	Tilt.attach(tiltPin);
	Grab.attach(grabPin);
	pinMode(rightSpeedPin, OUTPUT);
	pinMode(leftSpeedPin, OUTPUT);
	pinMode(rightDirectionPin, OUTPUT);
	pinMode(leftDirectionPin, OUTPUT);
}

void Controller::attach(int pins[])
{
	grabPin = pins[0];
	tiltPin = pins[1];
	panPin = pins[2];
	leftSpeedPin = pins[3];
	leftDirectionPin = pins[4];
	rightSpeedPin = pins[5];
	rightDirectionPin = pins[6];
	setupPins();
}

void Controller::detach()
{
	grabPin = -1;
	tiltPin = -1;
	panPin = -1;
	leftSpeedPin = -1;
	leftDirectionPin = -1;
	rightSpeedPin = -1;
	rightDirectionPin = -1;
	setupPins();
}

void Controller::setSpeed(float leftSpeed, float rightSpeed)
{
	this->leftSpeed = leftSpeed;
	this->rightSpeed = rightSpeed;
	analogWrite(leftSpeedPin, leftSpeed);
	analogWrite(rightSpeedPin, rightSpeed);
}

void Controller::setDir(int leftDirection, int rightDirection)
{
	this->leftDirection = leftDirection;
	this->rightDirection = rightDirection;
	digitalWrite(leftDirectionPin, leftDirection);
	digitalWrite(rightDirectionPin, rightDirection);
}

void  Controller::setGrab(int force) { Grab.write(force); }

void  Controller::setArm(int degrees) { Tilt.write(degrees); }

void  Controller::setPan(int degrees) { Pan.write(degrees); }

String Controller::getSpeed() { return "Left Speed: " + (String)leftSpeed + "Left Speed: " + (String)rightSpeed + "/n"; }

String Controller::getDir() { return "Left Speed: " + (String)leftDirection + "Left Speed: " + (String)rightDirection + "/n"; }
