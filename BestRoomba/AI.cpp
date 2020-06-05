#include "AI.h"

SerialLinkRoomba SLR;
/*!
* \brief Drives till a collision, changes direction and goes on
*/

void AI::roombaRunning() 
	{
		SLR.start_safe();
		SLR.Spot();
		SLR.Drive(20,20);

		/*
		 * Add collission detection
		 *
		 *
		 *
		 * 
		 *
		 *
		 */
		while (1)
		{
			if (IOh.isCollision())
			{
				IOh.moveBackward();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				IOh.rotateRight();
				std::this_thread::sleep_for(std::chrono::seconds(2));
				IOh.moveForward();
			}
		}
	}
