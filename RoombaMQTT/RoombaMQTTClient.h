#ifndef ROOMBAMQTTCLIENT_H
#define ROOMBAMQTTCLIENT_H

#include "/home/iot/Roomba/_libMQTT/CommandProcessor.h"
#include "/home/iot/Roomba/_libUtils/ParLoop.h"
#include "/home/iot/Roomba/_libSenseHAT/SenseHAT.h"
#include "json.hpp"

using json = nlohmann::json;

using parameters_t = std::vector<std::string>;

class MQTTClient : public CommandProcessor
{
public:
  MQTTClient(const std::string &appname,
             const std::string &clientname,
             const std::string &host,
             int port);
  MQTTClient() = delete;
  MQTTClient(const MQTTClient &other) = delete;
  MQTTClient &operator=(const MQTTClient &other) = delete;
  virtual ~MQTTClient();

  SenseHAT senseHAT_;

private:
   // Data examples, not in json format.
   double pi_;
   bool happy_;
   std::string name_;
   std::vector<int> list_;
   // json is a first-class data type.
  json jsonData_;

  void data2json();

protected:
  const std::string mqttID_;
  int x_;
  int y_;
  const int min_x_ = 0;
  const int min_y_ = 0;
  const int max_x_ = 7;
  const int max_y_ = 7;

  ParLoop publishSensorData_;
  ParLoop heartbeatPar_;

  // SensorHAT LED matrix display
  void clear(const parameters_t &commandParameters);
  void blank(const parameters_t &commandParameters);
  void invert(const parameters_t &commandParameters);
  void setPixel(const parameters_t &commandParameters);
  void getPixel(const parameters_t &commandParameters);
  void invertPixel(const parameters_t &commandParameters);
  void cylonPar(const parameters_t &commandParameters);
  void cylon(const parameters_t &commandParameters);
  void sendHeartbeat();
  void handleSensorData();
};

#endif
