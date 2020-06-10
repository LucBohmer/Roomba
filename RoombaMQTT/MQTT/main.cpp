#include <iostream>
#include <unistd.h>
#include "MQTTClient.h"
#include "../_libUtils/ParLoop.h"
#include "../_libMQTT/CommandProcessor.h"

int main(int argc, char* argv[])
{
    if(argc < 3) {
        std::cout << "Usage: ./RoombaMQTT <host> <port>" << std::endl;
        return 0;
    }

    ParLoop(heartBeat(), 5);

    heartBeat(){
    CommandProcessor::on_connect(0);
    CommandProcessor::publishInfo("heartbeat", "still connected");
}
    return 0;
}
