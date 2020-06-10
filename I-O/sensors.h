#ifndef SENSOR_H
#define SENSOR_H

#include "../_libUtils/SerialLink/SerialLinkAS.h"

/*!
* \brief Needs to be implemented !!!
*/

class Sensors
{
private:
SerialLinkAS& SL_;


public:
Sensors(SerialLinkAS& SL): SL_(SL)
{}


};

#endif