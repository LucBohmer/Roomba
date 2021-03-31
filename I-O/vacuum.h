#ifndef VACUUM_H
#define VACUUM_H

#include "/home/iot/Roomba/BestRoombaNA/SerialCommand.h"

//Class to controll the vacuum. Sends the right signals to the seriallink SA. Checks if the appclication is started.
class Vacuum
{
  private:
    bool enable_;
    SerialCommand &SL_;

  public:
    Vacuum(SerialCommand &SL) : enable_(false), SL_(SL)
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
