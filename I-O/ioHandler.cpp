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
    motors.setDrive(motorSpeed, motorSpeed);
}

/*!
* \brief Roomba starts driving backward
*/
void IOhandler::moveBackward()
{
    motors.setDrive(-motorSpeed, -motorSpeed);
}

/*!
* \brief Roomba rotate left
*/
void IOhandler::rotateLeft()
{
    motors.setDrive(motorSpeed, -motorSpeed);
}

/*!
* \brief Roomba rotates right
*/
void IOhandler::rotateRight()
{
    motors.setDrive(-motorSpeed, motorSpeed);
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
   // SL.LedSpotGreen();
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

void IOhandler::Clean()
{
	SL.Clean;
}

void IOhandler::Spot()
{
	SL.Spot;
}

void IOhandler::Dock()
{
	SL.Dock;
}

