
#include "Arduino.h"
#include "Sensor.h"



Sensor::Sensor()
{
	ir[3] = { 0 };
	RightWheelEncoder = -1;
	LeftWheelEncoder = -1;
	IRPin = -1;
	LeftBumper = -1;
	RightBumper = -1;
}

void Sensor::setupPins()
{
	pinMode(LeftBumper, INPUT);
	pinMode(RightBumper, INPUT);
	pinMode(LeftWheelEncoder, INPUT);
	pinMode(RightWheelEncoder, INPUT);
}

void Sensor::attach(int pins[])
{
	RightWheelEncoder = pins[0];
	LeftWheelEncoder = pins[1];
	IRPin = pins[2];
	LeftBumper = pins[3];
	RightBumper = pins[4];
	setupPins();
}

void Sensor::detach()
{
	RightWheelEncoder = -1;
	LeftWheelEncoder = -1;
	IRPin = -1;
	LeftBumper = -1;
	RightBumper = -1;
	setupPins();
}

char Sensor::receiveIR()
{
	char rec = IRReceiver.receive(200);
	while (rec == 0 || rec == -1 || rec == -2) {
		rec = IRReceiver.receive(200);
	}
	Serial.println(rec);
	return rec;
}

int *Sensor::readLine()
{
	ir[0] = analogRead(LSENSOR);
	ir[1] = analogRead(CSENSOR);
	ir[2] = analogRead(RSENSOR);
	return ir;
}

bool Sensor::isTriggered() { return digitalRead(LeftBumper) == HIGH && digitalRead(RightBumper) == HIGH; }

String Sensor::getLineLevel() { return "LSENSOR: " + (String)ir[1] + "CSENSOR: " + (String)ir[1] + "RSENSOR: " + (String)ir[2] + "\n"; }
