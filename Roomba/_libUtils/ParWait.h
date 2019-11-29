#ifndef PARWAIT_H
#define PARWAIT_H

#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;
using callbackFunction_t = std::function<void()>;

/// Always instantiate ParWait objects dynamiccaly.
/// A ParWait object will deallocate it-self!
class ParWait
{
public:
   ParWait(callbackFunction_t cbf, int waitTimeSeconds = 0):
      waitTimeSeconds_{waitTimeSeconds},
      cbf_{cbf},
      par_{&ParWait::parWaitf, this}
   {
      par_.detach();
   }
   ParWait(const ParWait &other) = delete;
   ParWait& operator=(const ParWait &other) = delete;
   ~ParWait() = default;
private:
   std::chrono::seconds waitTimeSeconds_;
   callbackFunction_t cbf_;
   std::thread par_;

   void parWaitf()
   {
      if (waitTimeSeconds_.count() > 0) {
         std::this_thread::sleep_for(waitTimeSeconds_);
      }
      cbf_();
      delete this;
   }
};

#endif
