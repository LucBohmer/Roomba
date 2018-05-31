#include "../_libUtils/parLoop.h"
#include "../_libMQTT/CommandProcessor"

ParLoop(heartBeat(), 5);

heartBeat(){
  std::cout << "alive" << std::endl;
}

