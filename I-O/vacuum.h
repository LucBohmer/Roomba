#ifndef VACUUM_H
#define VACUUM_H

#include "../_libUtils/SerialLink/SerialLinkAS.h"

/*!
* \brief Class to controll the vacuum. Sends the right signals to the seriallink SA. Checks if the appclication is started.
*/

class Vacuum
{
  private:
    bool enable_;
    SerialLinkAS &SL_;

  public:
    Vacuum(SerialLinkAS &SL) : enable_(false), SL_(SL)
    {
    }
    ~Vacuum() {}

    void start()
    {
        enable_ = true;
    }

    void stop()
    {
        enable_ = false;
        SL_.Vacuum(false);
        
    }

    void setOnOff(bool state)
    {
        if (enable_ == true)
        {
            SL_.Vacuum(state);
        }
    }
};

#endif