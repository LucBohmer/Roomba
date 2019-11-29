#ifndef SENSOR_H
#define SENSOR_H

#include "../_libUtils/SerialLink/SerialLinkAS.h"

/*!
* \brief Needs to be implemented !!!
*/

class Sensors
{
private:
SerialLinkRoomba& SL_;


public:
Sensors(SerialLinkRoomba& SL): SL_(SL)
{}


};

#endif
