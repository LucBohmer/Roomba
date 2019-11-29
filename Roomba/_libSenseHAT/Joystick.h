#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <atomic>
#include <functional>
#include <thread>

enum {JS_UP = 103, JS_DOWN = 108, JS_LEFT = 105, JS_RIGHT = 106,
      JS_PRESSED = 28};

using jshandler = std::function<void()>;

/// Joystick reacts to senseHAT joystick events received in a loop
/// executed in a thread.
/// Objects are not copyable by copy ctor and assignment.
class Joystick
{
public:
   Joystick();
   Joystick(const Joystick& other) = delete;
   Joystick& operator=(const Joystick& other) = delete;
   virtual ~Joystick();
   jshandler directionUP = nullptr;
   jshandler directionDOWN = nullptr;
   jshandler directionLEFT = nullptr;
   jshandler directionRIGHT = nullptr;
   jshandler directionPRESSED = nullptr;
   jshandler directionANY = nullptr;
protected:
   //std::condition_variable _cv;
   //std::mutex _mtx;
   std::atomic<bool> running_;
   std::thread thread_;
   void stop();
   void handleEvents();
};

#endif // JOYSTICK_H
