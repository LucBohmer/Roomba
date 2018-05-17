#ifndef APPINFO_H
#define APPINFO_H

#include <string.h>
#include <iostream>


std::string AppVersion = "0.0.1";
std::string AppName = "Roomba";

void DisplayAppInfo(void){

 std::cout <<"Version: "<<AppVersion<<std::endl;
 std::cout <<"Name: "<<AppName<<std::endl;
}

#endif // APPINFO_H
