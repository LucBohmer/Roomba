#ifndef SENSOR_H
#define SENSOR_H

#include "SerialCommand.h"

class Sensors
{
private:
SerialCommand& SL_;

public:
Sensors(SerialCommand& SL): SL_(SL)
{}

};
#endif
