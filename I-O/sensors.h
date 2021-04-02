#ifndef SENSOR_H
#define SENSOR_H

#include "SerialCommand.h"

// Class to read the sensors. Sends the right signals to the seriallink with the serialCommand class. Checks if the appclication is started.
class Sensors
{
private:
SerialCommand& SL_;

public:
Sensors(SerialCommand& SL): SL_(SL)
{}

};
#endif
