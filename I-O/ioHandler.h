
#ifndef IOHANDLER_H
#define IOHANDLER_H

#include "motor.h"
#include "vacuum.h"
#include "sensors.h"
#include "../BestRoombaNA/SerialCommand.h"

// Handels all te IO. Gets a commando from AI and controls the right acuators
class IOhandler
{
  private:
    SerialCommand SL;
    Motor motors;
    Vacuum vacuum;
    int motorSpeed = 150;

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
};
#endif 
