#ifndef MQTTCONFIG_H
#define MQTTCONFIG_H

#include <string>

const char *getHostname();
const std::string HOSTNAME{getHostname()};

const std::string GROUP{"1718"};

const int MQTT_KEEP_ALIVE{60};
const int MQTT_QoS_0{0};
const int MQTT_QoS_1{1};
const int MQTT_QoS_2{2};
const bool MQTT_RETAIN_OFF{false};
const bool MQTT_RETAIN_ON{true};

const std::string MQTT_LOCAL_BROKER{"127.0.0.1"};
const int MQTT_LOCAL_BROKER_PORT{1883};

const std::string MQTT_TOPIC_ROOT{"ESEiot/" + GROUP + "/" + HOSTNAME};

#endif
