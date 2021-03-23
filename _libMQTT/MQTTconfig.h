#ifndef MQTTCONFIG_H
#define MQTTCONFIG_H

#include <string>

const char *getHostname();
const std::string HOSTNAME{getHostname()};

const std::string GROUP{"1718sem4"};

const int MQTT_KEEP_ALIVE{60};
const int MQTT_QoS_0{0};
const int MQTT_QoS_1{1};
const int MQTT_QoS_2{2};
const bool MQTT_RETAIN_OFF{false};
const bool MQTT_RETAIN_ON{true};

const std::string MQTT_LOCAL_BROKER{"broker.hivemq.com"};
const int MQTT_LOCAL_BROKER_PORT{8000};

const std::string MQTT_TOPIC_ROOT{"mqtt"};

#endif
