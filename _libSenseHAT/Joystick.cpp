#include "Joystick.h"
#include "JoystickDevice.h"

#include <iostream>

using namespace std;

Joystick::Joystick():
   running_{true},
   thread_{&Joystick::handleEvents, this}
{
}

Joystick::~Joystick()
{
   stop();
}

void Joystick::stop()
{
   running_ = false;
   if (thread_.joinable())
   {
      thread_.join();
   }
}

void Joystick::handleEvents()
{
   const std::chrono::milliseconds Ts{330};
	running_ = initEventDevice() >= 0;

   while (running_)
   {
		input_event_t event = pollingEventDevice();
		switch (event.code)
		{
			case JS_UP:
            if (event.value != 0 and directionUP) directionUP();
				break;
			case JS_DOWN:
				if (event.value != 0 and directionDOWN) directionDOWN();
			   break;
			case JS_LEFT:
				if (event.value != 0 and directionLEFT) directionLEFT();
			   break;
			case JS_RIGHT:
			   if (event.value != 0 and directionRIGHT) directionRIGHT();
	         break;
			case JS_PRESSED:
				if (event.value != 0 and directionPRESSED) directionPRESSED();
		      break;
			default:
			  break;
		}
      switch (event.code)
		{
			case JS_UP:
			case JS_DOWN:
			case JS_LEFT:
			case JS_RIGHT:
			case JS_PRESSED:
				if (event.value != 0 and directionANY) directionANY();
		      break;
			default:
			  break;
		}
      std::this_thread::sleep_for(Ts);
   }
}
