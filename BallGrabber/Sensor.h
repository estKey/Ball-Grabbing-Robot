#pragma once
#include "QSerial.h"
// IR Range Sensor
#define IRRange				A0
// line tracker for recieving IR light
#define LSENSOR				A1
#define CSENSOR				A2
#define RSENSOR				A3
// Grip Force Sensor
#define GripFSR				A4
class Sensor
{
private:

	int ir[3];
	int RightWheelEncoder;
	int LeftWheelEncoder;
	int IRPin;
	int LeftBumper;
	int RightBumper;
	//
	QSerial IRReceiver;
	void setupPins();
public:
	// Initialize the Controller by input pins
	Sensor();
	void attach(int pins[]);
	void detach();
	char receiveIR();
	int *readLine();
	bool isTriggered();
	String getLineLevel();
};

