#include "MQTTClient.h"
#include <mosquittopp.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

MQTTClient::MQTTClient(const char * _id,const char * _topic, const char * _host, int _port) : mosquittopp(_id)
{
    mosqpp::lib_init();        // Mandatory initialization for mosquitto library
    this->keepalive = 60;    // Basic configuration setup for myMosq class
    this->id = _id;
    this->port = _port;
    this->host = _host;
    this->topic = _topic;
    connect_async(host,     // non blocking connection to broker request
        port,
        keepalive);
    loop_start();            // Start thread managing connection / publish / subscribe
}

MQTTClient::~MQTTClient() {
    loop_stop();            // Kill the thread
    mosqpp::lib_cleanup();    // Mosquitto library cleanup
}

bool MQTTClient::send_message(const  char * _message)
{
// Send message - depending on QoS, mosquitto lib managed re-submission this the thread
//
// * NULL : Message Id (int *) this allow to latter get status of each message
// * topic : topic to be used
// * lenght of the message
// * message
// * qos (0,1,2)
// * retain (boolean) - indicates if message is retained on broker or not
// Should return MOSQ_ERR_SUCCESS
    int ret = publish(NULL,this->topic,strlen(_message),_message,2,false);
    return ( ret == MOSQ_ERR_SUCCESS );
}

void MQTTClient::on_disconnect(int rc) {
    std::cout << ">> MQTTClient - disconnection(" << rc << ")" << std::endl;
}

void MQTTClient::on_connect(int rc)
{
    if ( rc == 0 ) {
        std::cout << ">> MQTTClient - connected with server" << std::endl;
    } else {
        std::cout << ">> MQTTClient - Impossible to connect with server(" << rc << ")" << std::endl;
    }
}

void MQTTClient::on_publish(int mid)
{
    std::cout << ">> MQTTClient - Message (" << mid << ") succeed to be published " << std::endl;
}

void MQTTClient::on_message(const struct mosquitto_message *message)
{
    std::cout << "[+] Topic: " << message->topic << " Payload: " << message->payload << std::endl;
}