#ifndef BESTROOMBANA_H
#define BESTROOMBANA_H

#include "AppInfo.h"
#include "AI.h"
#include "/home/iot/Roomba/RoombaMQTT/RoombaMQTTClient.h"
#include <iostream>
#include <iomanip>

class BestRoombaNA
{
	public:
	BestRoombaNA();
	void startApplication();
	
	private:
	void showAppInfo();
	AI ai{};
	MQTTClient mqttClient;
};
#endif