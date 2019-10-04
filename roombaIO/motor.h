#ifndef MOTOR_H
#define MOTOR_H

#include "../_libUtils/SerialLink/SerialLinkAS.h"

/*!
* \brief Class to controll the motors. Sends the right signals to the seriallink SA. Checks if the appclication is started.
*/

class Motor
{
  private:
    int speedL_;
    int speedR_;
    bool enable_;
    SerialLinkAS& SL_;

  public:
    Motor(SerialLinkAS& SL) : speedL_(0),speedR_(0), enable_(false), SL_(SL)
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