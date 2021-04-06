#ifndef MOTOR_H
#define MOTOR_H

#include "SerialCommand.h"

/*! @brief Control of Roomba motors.
 *  Functions in #Motor can be called to let the Roomba execute movements. 
 *  @param speedL_ Private variable which holds left motorspeed.
 *  @param speedR_ Private variable which holds left motorspeed.
 *  @param enable_ Boolean variable which enables motorspeed to be changed.
 *  @fn start() Enable motorspeed to be changed.
 *  @fn stop() Disable motorspeed to be changed.
 *  @fn setDrive(int speedL, int speedR) Set motorspeed.
 */
class Motor
{
  private:
    int speedL_;
    int speedR_;
    bool enable_;
    SerialCommand& SL_;

  public:
    /*! @brief Constructor
	*/
	Motor(SerialCommand& SL) : speedL_(0),speedR_(0), enable_(false), SL_(SL)
    {}
	/*! @brief Motor start. Enables motorspeed to be changed.
	*/
    void start()
    {
        enable_ = true;
    }

	/*! @brief Motor stop. Diables motorspeed to be changed.
	*/
    void stop()
    {
        speedL_ = 0;
        speedR_ = 0;
        SL_.Drive(speedL_, speedR_);
		enable_ = false;
    }

	/*! @brief Set motorspeed, range -255 to 255. 
	*   @param speedL Integer that holds left motorspeed. Valid value: -255 to 255.
	*   @param speedR Integer that holds right motorspeed. Valid value: -255 to 255.
	*/
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
