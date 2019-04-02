#pragma once
#include <Servo.h>
class Controller
{
private:
	// Variables
	float leftSpeed;
	float rightSpeed;
	int leftDirection;
	int rightDirection;
	// Pins
	int grabPin;
	int tiltPin;
	int panPin;
	int leftSpeedPin;
	int leftDirectionPin;
	int rightSpeedPin;
	int rightDirectionPin;
	// Servos
	Servo Pan, Tilt, Grab;
	void setupPins();
public:
	// Initialize the Controller by input pins
	Controller();
	void attach(int pins[]);
	void detach();
	void setSpeed(float leftSpeed, float rightSpeed);
	void setDir(int leftDirection, int rightDirection);
	void setGrab(int force);
	void setArm(int degrees);
	void setPan(int degrees);
	String getSpeed();
	String getDir();
};
