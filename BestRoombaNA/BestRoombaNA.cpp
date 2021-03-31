#include "BestRoombaNA.h"

BestRoombaNA::BestRoombaNA()
{
	
}

void BestRoombaNA::startApplication()
{
	showAppInfo();
	mqttClient.startClient();
    ai.startup();
}

void BestRoombaNA::showAppInfo() 
{
  std::cout << std::setfill('-') << std::setw(30) << "" << std::endl;
  std::cout << "--" << std::left << std::setw(26) << APPNAME_VERSION << "--" << std::endl;
  std::cout << std::setfill('-') << std::setw(30) << "" << std::endl;
}