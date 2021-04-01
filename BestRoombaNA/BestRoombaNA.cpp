#include "BestRoombaNA.h"

BestRoombaNA::BestRoombaNA()
{

}

BestRoombaNA::~BestRoombaNA()
{

}

void BestRoombaNA::startApplication()
{
showAppInfo();
    std::cout << mqttBroker << std::endl;
    std::cout << mqttBrokerPort << std::endl;
    ai.startup();
    mqttClient.startClient();
}

void BestRoombaNA::showAppInfo()
{
  std::cout << std::setfill('-') << std::setw(30) << "" << std::endl;
  std::cout << "--" << std::left << std::setw(26) << APPNAME_VERSION << "--" << std::endl;
  std::cout << std::setfill('-') << std::setw(30) << "" << std::endl;
}
