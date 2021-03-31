#ifndef SENSOR_H
#define SENSOR_H

#include "/home/iot/Roomba/BestRoombaNA/SerialCommand.h"

class Sensors
{
private:
SerialCommand& SL_;

public:
Sensors(SerialCommand& SL): SL_(SL)
{}

};
#endif
