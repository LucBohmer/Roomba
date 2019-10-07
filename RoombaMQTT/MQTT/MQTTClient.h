// code from https://www.disk91.com/2013/technology/programming/mosquitto-c-sample-code-to-publish-message/

#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <mosquittopp.h>
#include <mosquitto.h>

class MQTTClient : public mosqpp::mosquittopp
{
private:
    const char* host;
    const char* id;
    const char* topic;
    int port;
    int keepalive;
    
    void on_connect(int rc);
    void on_disconnect(int rc);
    void on_publish(int mid);
    void on_message(const struct mosquitto_message *message);

public:
    MQTTClient(const char *id, const char * _topic, const char *host, int port);
    ~MQTTClient();
    bool send_message(const char * _message);
};

#endif