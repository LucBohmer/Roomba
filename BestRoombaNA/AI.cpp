#include "AI.h"
//#include "BestRoombaNA.h"

// drives till a collision , turns around and repeats
void AI::startup()
{
    IOh.start();
}
/*
    IOh.startVacuum();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    IOh.stopVacuum();

    IOh.moveForward();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    IOh.moveBackward();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    IOh.standStill();


    bool bool_new = false;
    bool bool_old = false;
    std::cout << "enter loop" << std::endl;
    IOh.moveForward();
    while (1)
    {
//        std::cout << "enter loop" << std::endl; 
       if (IOh.isCollision())
        {
           std::cout << "collision" << std::endl;
           IOh.moveBackward();
           std::this_thread::sleep_for(std::chrono::seconds(1));
           IOh.rotateRight();
           std::this_thread::sleep_for(std::chrono::seconds(2));
           IOh.moveForward();
	}
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

    }
*/

