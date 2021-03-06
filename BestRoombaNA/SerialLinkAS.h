#ifndef SERIALLINKAS_H
#define SERIALLINKAS_H
#include "../_libUtils/SerialLink/SerialLink.h"
#include "../_libUtils/SerialLink/OpenInterfaceConfig.h"

/*!
*\brief SerialLink for the BestRoomba HEADER file.
*\brief Contains default baudrate and different functions.
*\brief Functions: start_safe, Drive, Spot, Clean, Vacuum.
*\brief Sensors: isCollision, ButtonSpot.
*/
class SerialLinkAS
{
  private:
  SerialLink sl{"/dev/ttyUSB0", static_cast<unsigned int>(Baud::ROOMBA_DEFAULT)};

  public:
    SerialLinkAS() {}

///----------------------- FUNCTIES -----------------------------
    void start_safe()
    {
        std::cout<<"hij komt hier"<<std::endl;
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

///----------------------- SENSOREN ------------------------------
    bool isCollision()
    {
        return (sl.writeRead({142, 7}, 2).at(1) >> 0) & 0x1;
    }

    bool ButtonSpot()
    {
        return (sl.writeRead({142, 2}, 2).at(1) >> 0) & 0X2;
    }

///------------------------- LEDS --------------------------------
    void LedSpotGreen()
    {
        sl.write({139, 2, 0, 255});
    }
};
#endif
