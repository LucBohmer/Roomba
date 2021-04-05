
#ifndef IOHANDLER_H
#define IOHANDLER_H

#include "motor.h"
#include "vacuum.h"
#include "sensors.h"
#include "SerialCommand.h"

/*! @brief Handles the IO of the Roomba. 
 *  Functions in #IOhandler can be called to let the Roomba execute movements. 
 */
 
class IOhandler
{
  private:
    SerialCommand SL;
    Motor motors;
    Vacuum vacuum;
    int motorSpeed = 150;  /// Default motorspeed = 150

  public:
    IOhandler():SL(), motors(SL), vacuum(SL)
    {
    }
    void start();
    void stop();
    void moveForward();
    void moveBackward();
    void rotateLeft();
    void rotateRight();
    void standStill();
    void startVacuum();
    void stopVacuum();
    bool isCollision();
    bool isButtonSpot();
	void Clean();
	void Spot();
	void Dock();
};
#endif 
