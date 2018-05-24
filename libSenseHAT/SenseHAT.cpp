#include "SenseHAT.h"
#include "LedMatrixDevice.h"

#include <RTIMULib.h>

SenseHAT::SenseHAT():
	stick{},
	leds{},
	humidity{nullptr},
	pressure{nullptr}
{
	RTIMUSettings* settings = new RTIMUSettings();
	humidity = RTHumidity::createHumidity(settings);
	humidity->humidityInit();
	pressure = RTPressure::createPressure(settings);
	pressure->pressureInit();
}

double SenseHAT::get_temperature()
{
	return get_temperature_from_humidity();
}

double SenseHAT::get_humidity()
{
	RTIMU_DATA data;
	if(!humidity->humidityRead(data)) {
		return nan("");
	}
	if(!data.humidityValid) {
		return nan("");
	}
	return data.humidity;
}

double SenseHAT::get_temperature_from_humidity()
{
	RTIMU_DATA data;
	if(!humidity->humidityRead(data)) {
		return nan("");
	}
	if(!data.temperatureValid) {
		return nan("");
	}
	return data.temperature;
}

double SenseHAT::get_pressure()
{
	RTIMU_DATA data;
	if(!pressure->pressureRead(data)) {
		return nan("");
	}
	if(!data.pressureValid) {
		return nan("");
	}
	return data.pressure;
}

double SenseHAT::get_temperature_from_pressure()
{
	RTIMU_DATA data;
	if(!pressure->pressureRead(data)) {
		return nan("");
	}
	if(!data.temperatureValid) {
		return nan("");
	}
	return data.temperature;
}
