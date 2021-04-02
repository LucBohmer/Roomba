#ifndef AI_H
#define AI_H

#include "/home/iot/Roomba/I-O/ioHandler.h"
#include <chrono>
#include <thread>

// AI holds the cleaning stratagy. holds diffecent programms 
class AI
{
    private:
    IOhandler IOh;

    public:
    AI(): IOh()
    {}
    void startup();
};

#endif
