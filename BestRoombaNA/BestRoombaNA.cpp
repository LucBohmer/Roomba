#include "BestRoombaNA.h"

void startApplication()
{
    AI ai{};
    ai.startup();
}

void showAppInfo() {
  std::cout << std::setfill('-') << std::setw(30) << "" << std::endl;
  std::cout << "--" << std::left << std::setw(26) << APPNAME_VERSION << "--" << std::endl;
  std::cout << std::setfill('-') << std::setw(30) << "" << std::endl;
}