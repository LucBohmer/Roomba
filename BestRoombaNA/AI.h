#ifndef AI_H
#define AI_H

#include "/home/iot/Roomba/I-O/ioHandler.h"
#include <chrono>
#include <thread>

/**
 *  @brief Holds the cleaning strategies and different programs.
 *  AI inherits IOh class.
 */ 
class AI{

    private:
    IOhandler IOh;

    public:
    AI(): IOh()
    {}
    void startup();
};

#endif
