#include "RoombaMQTTClient.h"
#include "../_libMQTT/MQTTconfig.h"
#include "../_libUtils/ParWait.h"
#include "../_libUtils/ParLoop.h"
#include "../_libSenseHAT/Pixel.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>

using namespace std;

MQTTClient::MQTTClient(const std::string &appname,
                       const std::string &clientname,
                       const std::string &host,
                       int port) : CommandProcessor(appname, clientname, host, port),
                                   senseHAT_{},
                                   mqttID_{HOSTNAME + appname + clientname},
                                   x_{0},
                                   y_{0},
                                   publishSensorData_(std::bind(&MQTTClient::handleSensorData, this), 60),
                                   heartbeatPar_(std::bind(&MQTTClient::sendHeartbeat, this), 10),
                                   jsonData_{}
{
    std::cerr << "---- CTOR MQTTsenseHAT host = '" << host
              << "'  port = " << port
              << "  id = " << mqttID_
              << "  topic root = " << MQTT_TOPIC_ROOT << std::endl;

    senseHAT_.leds.clear(Pixel{0, 50, 0});

    // LEDs display commands
    registerCommand("clear", bind(&MQTTClient::clear, this,
                                  placeholders::_1));
    registerCommand("blank", bind(&MQTTClient::blank, this,
                                  placeholders::_1));
    registerCommand("invert", bind(&MQTTClient::invert, this,
                                   placeholders::_1));
    registerCommand("setPixel", bind(&MQTTClient::setPixel, this,
                                     placeholders::_1));
    registerCommand("getPixel", bind(&MQTTClient::getPixel, this,
                                     placeholders::_1));
    registerCommand("invertPixel", bind(&MQTTClient::invertPixel, this,
                                        placeholders::_1));
    registerCommand("cylon", bind(&MQTTClient::cylon, this,
                                  placeholders::_1));

    senseHAT_.leds.setPixel(x_, y_, Pixel{200, 100, 100});

    data2json();
    std::cerr << "Data in json format = " << jsonData_ << std::endl;
}

MQTTClient::~MQTTClient()
{
    senseHAT_.leds.clear(Pixel{50, 0, 0});
}

void MQTTClient::blank(const parameters_t &commandParameters)
{
    if (commandParameters.size() != 0)
    {
        publishError("setPixel", "number of parameters != 0");
    }
    else
    {
        senseHAT_.leds.clear();
    }
}

void MQTTClient::clear(const parameters_t &commandParameters)
{
    if (commandParameters.size() != 3)
    {
        publishError("clear", "number of parameters != 3");
    }
    else
    {
        auto r = stoi(commandParameters[0]);
        auto g = stoi(commandParameters[1]);
        auto b = stoi(commandParameters[2]);
        senseHAT_.leds.clear(Pixel(r, g, b));
    }
}

void MQTTClient::invert(const parameters_t &commandParameters)
{
    if (commandParameters.size() != 0)
    {
        publishError("clear", "number of parameters != 0");
    }
    else
    {
        senseHAT_.leds.invert();
    }
}

void MQTTClient::setPixel(const parameters_t &commandParameters)
{
    if (commandParameters.size() != 5)
    {
        publishError("setPixel", "number of parameters != 5");
    }
    else
    {
        auto y = stoi(commandParameters[0]);
        auto x = stoi(commandParameters[1]);
        auto r = stoi(commandParameters[2]);
        auto g = stoi(commandParameters[3]);
        auto b = stoi(commandParameters[4]);
        senseHAT_.leds.setPixel(x, y, Pixel(r, g, b));
    }
}

void MQTTClient::getPixel(const parameters_t &commandParameters)
{
    if (commandParameters.size() != 2)
    {
        publishError("getPixel", "number of parameters != 2");
    }
    else
    {
        auto y = stoi(commandParameters[0]);
        auto x = stoi(commandParameters[1]);
        Pixel pixel = senseHAT_.leds.getPixel(x, y);
        publishReturn("getPixel", std::to_string(pixel[Pixel::RGB::R]) + " " + std::to_string(pixel[Pixel::RGB::G]) + " " + std::to_string(pixel[Pixel::RGB::B]));
    }
}

void MQTTClient::invertPixel(const parameters_t &commandParameters)
{
    if (commandParameters.size() != 2)
    {
        publishError("invertPixel", "number of parameters != 2");
    }
    else
    {
        auto y = stoi(commandParameters[0]);
        auto x = stoi(commandParameters[1]);

        Pixel pixel{senseHAT_.leds.getPixel(x, y)};
        pixel.invert();
        senseHAT_.leds.setPixel(x, y, pixel);
    }
}

void MQTTClient::cylonPar(const parameters_t &commandParameters)
{
    auto putDot = [this](int x, const Pixel &pixel) {
        senseHAT_.leds.setPixel(x, 3, pixel);
        senseHAT_.leds.setPixel(x, 4, pixel);
        senseHAT_.leds.setPixel(x + 1, 3, pixel);
        senseHAT_.leds.setPixel(x + 1, 4, pixel);
    };

    auto show = [putDot] {
        int x{0};
        int i{1};
        int count{13};

        while (count > 0)
        {
            putDot(x, Pixel::RED);
            std::this_thread::sleep_for(std::chrono::milliseconds{200});
            putDot(x, Pixel::BLANK);
            x += i;
            if (x < 0)
            {
                i = 1;
                x = 1;
            }
            if (x > 6)
            {
                i = -1;
                x = 5;
            }
            --count;
        }
    };

    show();
}

void MQTTClient::cylon(const parameters_t &commandParameters)
{
    new ParWait{std::bind(&MQTTClient::cylonPar, this, commandParameters)};
}

void MQTTClient::handleSensorData()
{
    //    std::string message{
    //       std::to_string(static_cast<int>(senseHAT_.get_humidity()))};
        //publishAddition("json", jsonData_.dump());
}

void MQTTClient::data2json()
{
   jsonData_["pi"] = pi_;
   jsonData_["happy"] = happy_;
   jsonData_["name"] = name_;
   jsonData_["list"] = list_;
}

void MQTTClient::sendHeartbeat()
{
    publishAddition("heartbeat" , "json data heartbeat: " + jsonData_.dump());
}