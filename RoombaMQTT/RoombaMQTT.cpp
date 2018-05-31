#include "../_libUtils/parLoop.h"
#include "../_libMQTT/CommandProcessor"

ParLoop(heartBeat(), 5);

heartBeat(){
  CommandProcessor::on_connect(0);
  CommandProcessor::publishInfo("heartbeat", "still connected");
}

