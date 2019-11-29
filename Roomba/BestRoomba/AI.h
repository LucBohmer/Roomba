#ifndef AI_H
#define AI_H

#include "../roombaIO/ioHandler.h"
#include <chrono>
#include <thread>

/*!
* \brief AI holds the cleaning stratagy. holds diffecent programms 
*/

class AI{

private:
    IOhandler IOh;

    public:
    AI(): IOh()
    {}
	void roombaRunning();
	
};



#endif