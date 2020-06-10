#include "ioHandler.h"
/*!
* \brief Starts all the actuators and sends safeMode signal.
*/
void IOhandler::start()
{
    motors.start();
    vacuum.start();
    SL.start_safe();
}

/*!
* \brief Stops all te actuators. Needs start to run again.
*/
void IOhandler::stop()
{
    motors.stop();
    vacuum.stop();
}

/*!
* \brief Roomba starts driving forward
*/
void IOhandler::moveForward()
{
    motors.setDrive(300, 300);
}

/*!
* \brief Roomba starts driving backward
*/
void IOhandler::moveBackward()
{
    motors.setDrive(-300, -300);
}

/*!
* \brief Roomba rotate left
*/
void IOhandler::rotateLeft()
{
    motors.setDrive(300, -300);
}

/*!
* \brief Roomba rotates right
*/
void IOhandler::rotateRight()
{
    motors.setDrive(-300, 300);
}

/*!
* \brief Roomba stops driving. Need no start
*/
void IOhandler::standStill()
{
    motors.setDrive(0, 0);
}

/*!
* \brief Starts vacuum and brushes
*/
void IOhandler::startVacuum()
{
    vacuum.setOnOff(true);
}

/*!
* \brief Stops vacuum and brushes
*/
void IOhandler::stopVacuum()
{
    vacuum.setOnOff(false);
}

/*!
* \brief Checks if there is a collition
* \param bool isCollision 
*/
bool IOhandler::isCollision()
{
    return SL.isCollision();
}

/*!
* \brief checks if the button Spot is pressed. if this is true sets the LED on
* \param bool isButtonSpot
*/
bool IOhandler::isButtonSpot()
{
    if (SL.ButtonSpot())
    {
        SL.LedSpotGreen();
        return true;
    }
    else
    {
        return false;
    }
}