#include "../parLoop.h"
#include "../CommandProcessor.h"

ParLoop(heartBeat(), 5);

heartBeat(){
  CommandProcessor::on_connect(0);
  CommandProcessor::publishInfo("heartbeat", "still connected");
}

