#include "stdafx.h"

void setup() {
	// Lisiten  Port
	Serial.begin(9600);
	// PinModes
	pinMode(LeftBumper, INPUT);
	pinMode(RightBumper, INPUT);
	pinMode(LeftWheelEncoder, INPUT);
	pinMode(RightWheelEncoder, INPUT);
	pinMode(M1, OUTPUT);
	pinMode(E1, OUTPUT);
	pinMode(M2, OUTPUT);
	pinMode(E2, OUTPUT);
	// Servo Configuration
	Pan.attach(ServoPan);
	Tilt.attach(ServoTilt);
	Grab.attach(ServoGrab);
	// IR Detector
	IRReceiver.attach(IRPin, -1);
}

void loop() {
  //drive(1, 1.0);
  followLine();
}
