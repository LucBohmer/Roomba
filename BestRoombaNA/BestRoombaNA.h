#ifndef BESTROOMBANA_H
#define BESTROOMBANA_H

#include "AppInfo.h"
#include "AI.h"
#include "/home/iot/Roomba/RoombaMQTT/RoombaMQTTClient.h"
#include "/home/iot/Roomba/_libMQTT/MQTTconfig.h"
#include <iostream>
#include <iomanip>
#include <string>

/**
 *  @brief Main application to control Roomba.
 */ 
class BestRoombaNA
{
	public:
	BestRoombaNA();
	~BestRoombaNA();
	void startApplication();
	
	private:
	std::string mqttBroker{MQTT_LOCAL_BROKER};
        int mqttBrokerPort{MQTT_LOCAL_BROKER_PORT};
	void showAppInfo();
	AI ai{};
	RoombaMQTTClient mqttClient{"MSH", "msh", mqttBroker, mqttBrokerPort};
};
#endif
