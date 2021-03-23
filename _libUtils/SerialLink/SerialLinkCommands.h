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

  public:
    SerialLinkRoomba() {}

///----------------------- FUNCTIONS -----------------------------
    void start_safe()
    {
        sl.write({128});
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
        return 0;//(sl.readWrite({142, 7}, 2).at(1) >> 0) & 0x1;
    }

    bool ButtonSpot()
    {
        return 0;//(sl.readWrite({142, 2}, 2).at(1) >> 0) & 0X2;
    }

///------------------------- LEDS --------------------------------
    void LedSpotGreen()
    {
        sl.write({139, 2, 0, 255});
    }
};
#endif
