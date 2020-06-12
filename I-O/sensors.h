#ifndef SENSOR_H
#define SENSOR_H

#include "../BestRoombaNA/SerialLinkAS.h"

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
