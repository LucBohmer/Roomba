#include "AI.h"
#include "BestRoombaNA.h"

// drives till a collision , turns around and repeats
void AI::startup()
{
    IOh.start();
    IOh.startVacuum();
    IOh.moveForward();

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