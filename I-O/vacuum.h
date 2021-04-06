#ifndef VACUUM_H
#define VACUUM_H

#include "SerialCommand.h"
/*!
*\brief Class to control the vacuum. 
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
	 *  @param enable_ is set to true;
	 */  
    void start()
    {
        enable_ = true;
    }
	
	/*! \fn Stop vacuuming. 
	 *  @param enable_ is set to true;
	 */
    void stop()
    {
        enable_ = false;
        SL_.Vacuum(false);
        
    }
	/*! \fn Turn vacuum ON or OFF. 
	 *  @param state Boolean to turn vacuum ON or OFF. Valid values: true or false.
	 */
    void setOnOff(bool state)
    {
        if (enable_ == true)
        {
            SL_.Vacuum(state);
        }
    }
};
#endif
