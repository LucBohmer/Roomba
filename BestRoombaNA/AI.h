#ifndef AI_H
#define AI_H

#include "/home/iot/Roomba/I-O/ioHandler.h"
#include <chrono>
#include <thread>

/**
 *  \class AI inherits IOh class.
 *  Holds the cleaning strategies and different programs.
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
