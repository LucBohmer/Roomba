#ifndef VACUUM_H
#define VACUUM_H

#include "SerialCommand.h"
/*!
*\brief Class to controll the vacuum. 
*\brief Sends the correct signals to the Seriallink instance. 
*\brief Checks if the application is started.
*/

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
	
	/*! \fn Start vacuuming. 
	 *  @par enable_ is set to true;
	 */  
    void start()
    {
        enable_ = true;
    }
	
	/*! \fn Stop vacuuming. 
	 *  @par enable_ is set to true;
	 */
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
