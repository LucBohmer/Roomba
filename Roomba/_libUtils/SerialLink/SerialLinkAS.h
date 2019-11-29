#ifndef SERIALLINKCOMMANDS_H
#define SERIALLINKCOMMANDS_H
#include "SerialLink.h"
#include "InterfaceConfig.h"

/*!
*\brief SerialLink for the BestRoomba HEADER file.
*\brief Contains default baudrate and different functions.
*\brief Functions: start_safe, Drive, Spot, Clean, Vacuum.
*\brief Sensors: isCollision, ButtonSpot.
*\param value
*/
class SerialLinkRoomba
{
  private:
  SerialLink sl{"/dev/ttyUSB0", static_cast<unsigned int>(Baud::ROOMBA_DEFAULT)};
	std::vector<uint8_t> iets;
  public:
    SerialLinkRoomba() {}

///----------------------- FUNCTIONS -----------------------------
    void start_safe()
    {
        sl.write(startSafe());
    }

    void Drive(int speedL, int speedR)
    {
        sl.write(driveDirect(speedR, speedL));
    }

    void Spot()
    {
        sl.write({134});            /// Spot ON
    }

    void Clean()
    {
        sl.write({135});            /// Clean ON
    }

    void Vacuum(bool state)
    {
        if (state)
        {
            sl.write({138, 7});     /// Vacuum ON
        }
        else
        {
            sl.write({138, 0});     /// Vacuum OFF
        }        
    }

///----------------------- SENSORS ------------------------------
    bool isCollision()
    {
//        return (sl.write({142, 1}, 2).at(1) >> 0) & 0x1;
	sl.write({142, 1});
	sl.read(iets,2);	
	return ((iets.at(1) >> 0) & 0x1); 
    }

    bool ButtonSpot()
    {
        sl.write({142, 2});
	sl.read(iets,2);
	return ((iets.at(1) >> 0) & 0X4);
    }

///------------------------- LEDS --------------------------------
    void LedSpotGreen()
    {
        sl.write({139, 2, 0, 255});
    }
};
#endif
