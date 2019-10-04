#include "BestRoomba.h"

void startApplication()
{
	AI ai{};

	ai.roombaRunning();

}

void showAppInfo() {
	std::cout << std::setfill('-') << std::setw(30) << "" << std::endl;
	std::cout << "--" << std::left << std::setw(26) << APPNAME_VERSION << "--" << std::endl;
	std::cout << std::setfill('-') << std::setw(30) << "" << std::endl;
}
