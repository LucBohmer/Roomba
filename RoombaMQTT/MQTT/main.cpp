#include <iostream>
#include <unistd.h>
#include "MQTTClient.h"

int main(int argc, char* argv[])
{
    if(argc < 3) {
        std::cout << "Usage: ./RoombaMQTT <host> <port>" << std::endl;
        return 0;
    }

    MQTTClient cli("Roomba", "roomba/beat", argv[1], atoi(argv[2]));

    while(1){
        usleep(2*1000000);
        cli.send_message("heartbeat");
    }
    return 0;
}