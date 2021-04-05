#ifndef SERIALCOMMAND_H
#define SERIALCOMMAND_H
#include "/home/iot/Roomba/_libUtils/SerialLink/SerialLink.h"
#include "/home/iot/Roomba/_libUtils/SerialLink/OpenInterfaceConfig.h"

/*!
*\brief Converts Command to Serial Communication for the BestRoomba HEADER file.
*\brief Contains default baudrate and different functions.
*\brief Functions: start_safe, Drive, Spot, Clean, Dock, Vacuum.
*\brief Sensors: isCollision, ButtonSpot.
*/
class SerialCommand
{
  private:
  SerialLink sl{"/dev/ttyUSB0", static_cast<unsigned int>(Baud::ROOMBA_DEFAULT)};

  public:
    /*!  @brief Constructor 
	 */
	SerialCommand() {}

    /*!  @brief Writes serial command to turn Roomba on in Safe mode.
	 */
    void start_safe()
    {
        sl.write(startSafe());
    }

    /*!  @brief Writes serial command to let Roomba drive.
	 *   @par speedL Integer to set left Roomba drive speed.
	 *   @par speedR Integer to set right Roomba drive speed.
	 */
	void Drive(int speedL, int speedR)
    {
        sl.write(driveDirect(speedR, speedL));
    }
	
	/*!  @brief Writes serial Spot command
	 *   Roomba is started in Spot mode. When called again the Roomba exit Spot mode.
	 */
    void Spot()
    {
        sl.write({134});            /// Serial Spot Command
    }
	
	/*!  @brief Writes serial Clean command
	 *   Roomba is started in Clean mode. When called again the Roomba exit Clean mode.
	 */
    void Clean()
    {
        sl.write({135});            /// Serial Clean Command
    }
	
	/*!  @brief Writes serial Dock command
	 *   Roomba is started in Force Dock Seeking mode. When called again the Roomba exit Dock mode.
	 */
	void Dock()
    {
        sl.write({143});            /// Serial Force Dock Seeking Command
    }

	/*! @brief Turns Roomba vacuum ON or OFF;
	 *  @par state Boolean value (true | false) to turn vacuum on or off.
	 */
    void Vacuum(bool state)
    {
        if (state)
        {
            sl.write({138, 7});     /// Serial command Vacuum ON
        }
        else
        {
            sl.write({138, 0});     /// Serial command Vacuum OFF
        }        
    }

	/*! @brief Sends serial command to read Collision sensor data.
	 */
    bool isCollision()
    {
        return (sl.writeRead({142, 1}, 10).at(1) & 0x1);
        //return (sl.writeRead({142, 7}, 2).at(1) >> 0) & 0x1;

    }
	/*! @brief Sends serial command to read state of Spot button.
	 */
    bool ButtonSpot()
    {
        return (sl.writeRead({142, 2}, 2).at(1) >> 0) & 0X2;
    }

	/*! @brief Sends serial command to set Spot Led green.
	 */
    void LedSpotGreen()
    {
        sl.write({139, 2, 0, 255});
    }
};
#endif 
