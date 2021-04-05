#include "AI.h"

/*!
 *  \brief Start instance of AI. 
 *  Calls function start() of IOh instance to start Motor and Vacuum object and 
 *  opens interface to start Roomba in Safe Mode.
 */

void AI::startup()
{
    IOh.start();
}

