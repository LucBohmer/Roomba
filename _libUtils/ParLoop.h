#ifndef PARLOOP_H
#define PARLOOP_H

#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;
using callbackFunction_t = std::function<void()>;

/// Utility class for provinding a loop executing a callback function #cbf
/// in a thread. After executing this function this thread will sleep for
/// #loopTimeSeconds seconds. This class in non-copyable. RAII: the thread
/// is created by the constructor and is stopped in the destructor # Parloop.
class ParLoop
{
public:
   ParLoop(callbackFunction_t cbf, int loopTimeSeconds):
      loopTimeSeconds_{loopTimeSeconds},
      running_{true},
      cbf_{cbf},
      threadLooping_{&ParLoop::loop, this}
   {
   }
   ParLoop(const ParLoop &other) = delete;
   ParLoop& operator=(const ParLoop &other) = delete;
   ~ParLoop()
   {
      stop();
   }
private:
   std::chrono::seconds loopTimeSeconds_;
   std::atomic<bool> running_;
   callbackFunction_t cbf_;
   std::thread threadLooping_;

   void loop()
   {
      while (running_) {
         cbf_();
         std::this_thread::sleep_for(loopTimeSeconds_);
      }
   }

   void stop()
   {
      running_ = false;
      if (threadLooping_.joinable()) {
         threadLooping_.join();
      }
   }
};

#endif
