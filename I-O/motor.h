#ifndef MOTOR_H
#define MOTOR_H

#include "SerialCommand.h"

// Class to controll the motors. Sends the right signals to the seriallink with the serialCommand class. Checks if the appclication is started.
class Motor
{
  private:
    int speedL_;
    int speedR_;
    bool enable_;
    SerialCommand& SL_;

  public:
    Motor(SerialCommand& SL) : speedL_(0),speedR_(0), enable_(false), SL_(SL)
    {}

    void start()
    {
        enable_ = true;
    }

    void stop()
    {
        enable_ = false;
        speedL_ = 0;
        speedR_ = 0;
        SL_.Drive(speedL_, speedR_);
    }

    void setDrive(int speedL, int speedR)
    {
        if (enable_ == true)
        {
            speedL_ = speedL;
            speedR_ = speedR;            
            SL_.Drive(speedL_, speedR_);
        }
    }
};
#endif
