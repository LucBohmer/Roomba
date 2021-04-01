#ifndef BESTROOMBANA_H
#define BESTROOMBANA_H

#include "AppInfo.h"
#include "AI.h"
#include "/home/iot/Roomba/RoombaMQTT/RoombaMQTTClient.h"
#include "/home/iot/Roomba/_libMQTT/MQTTconfig.h"
#include <iostream>
#include <iomanip>
#include <string>

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
	MQTTClient mqttClient{"MSH", "msh", mqttBroker, mqttBrokerPort};
};
#endif
