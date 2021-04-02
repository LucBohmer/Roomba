#ifndef SENSOR_H
#define SENSOR_H

#include "SerialCommand.h"

/*!
* \brief Sensor class for reading the sensors. It sends the right signals to the seriallink with the serialCommand class.
*/

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
