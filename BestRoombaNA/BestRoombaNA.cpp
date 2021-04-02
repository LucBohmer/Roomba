#include "BestRoombaNA.h"
/*! 
 * \brief BestRoombaNA Class Constructor.
 */
BestRoombaNA::BestRoombaNA()
{

}
/*! 
 * \brief BestRoombaNA Class Destructor.
 */
BestRoombaNA::~BestRoombaNA()
{

}
/*!
 * \brief Starts BestRoombaNA Application. Print application info to console, startup AI and mqttClient instances.
 */
void BestRoombaNA::startApplication()
{
    showAppInfo();
    ai.startup();
    mqttClient.startClient();
}

/*!
 * \brief BestRoombaNA Application info is printed to console. 
 */
void BestRoombaNA::showAppInfo()
{
  std::cout << std::setfill('-') << std::setw(30) << "" << std::endl;
  std::cout << "--" << std::left << std::setw(26) << APPNAME_VERSION << "--" << std::endl;
  std::cout << std::setfill('-') << std::setw(30) << "" << std::endl;
}
