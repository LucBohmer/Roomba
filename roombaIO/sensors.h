#ifndef SENSOR_H
#define SENSOR_H

#include "../_libUtils/SerialLink/SerialLink.h"

/*!
* \brief Needs to be implemented !!!
*/

class Sensors
{
private:
SerialLink& SL_;


public:
Sensors(SerialLink& SL): SL_(SL)
{}


};

#endif
