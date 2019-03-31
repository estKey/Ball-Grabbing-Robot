
#include "Arduino.h"
#include "Info.h"
Info::Info()
{
    number = 3;
}

void Info::displayInfo()
{
    Serial.println("ELEC 299 Group 16");
}
