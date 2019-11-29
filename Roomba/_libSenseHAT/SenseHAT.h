#ifndef SENSEHAT_H
#define SENSEHAT_H

#include "Joystick.h"
#include "LedMatrix.h"

#include <cstdint>

class RTHumidity;
class RTPressure;

class SenseHAT
{
public:
	SenseHAT();
	SenseHAT(const SenseHAT& other) = delete;
	SenseHAT& operator=(SenseHAT& other) = delete;
	virtual ~SenseHAT() = default;

	// Sensor methods
	double get_temperature();
	double get_humidity();
	double get_temperature_from_humidity();
	double get_pressure();
	double get_temperature_from_pressure();

	Joystick stick;
	LedMatrix leds;
private:
	RTHumidity* humidity;
	RTPressure* pressure;
};

#endif
