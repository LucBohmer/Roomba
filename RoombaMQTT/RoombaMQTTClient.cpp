#include "RoombaMQTTClient.h"
#include "/home/iot/Roomba/_libMQTT/MQTTconfig.h"
#include "/home/iot/Roomba/_libUtils/ParWait.h"
#include "/home/iot/Roomba/_libUtils/ParLoop.h"
#include "/home/iot/Roomba/_libSenseHAT/Pixel.h"

#include <csignal>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#define UNUSED(x) (void)(x)

using namespace std;
/**
 *  @brief Constructor.
 */ 
RoombaMQTTClient::RoombaMQTTClient(const std::string &appname,
                       const std::string &clientname,
                       const std::string &host,
                       int port) : CommandProcessor(appname, clientname, host, port),
                                   senseHAT_{},
				   ioHandler_{},
								   pi_{0},
								   happy_{0},
								   name_{0},
								   list_{0},
								   jsonData_{},
                                   mqttID_{HOSTNAME + appname + clientname},
                                   x_{0},
                                   y_{0},
                                   publishSensorData_(std::bind(&RoombaMQTTClient::handleSensorData, this), 60),
                                   heartbeatPar_(std::bind(&RoombaMQTTClient::sendHeartbeat, this), 10)
{
    std::cerr << "---- CTOR MQTTsenseHAT host = '" << host
              << "'  port = " << port
              << "  id = " << mqttID_
              << "  topic root = " << MQTT_TOPIC_ROOT << std::endl;

    senseHAT_.leds.clear(Pixel{0, 50, 0});

    // LEDs display commands
    registerCommand("clear", bind(&RoombaMQTTClient::clear, this,
                                  placeholders::_1));
    registerCommand("blank", bind(&RoombaMQTTClient::blank, this,
                                  placeholders::_1));
    registerCommand("invert", bind(&RoombaMQTTClient::invert, this,
                                   placeholders::_1));
    registerCommand("setPixel", bind(&RoombaMQTTClient::setPixel, this,
                                     placeholders::_1));
    registerCommand("getPixel", bind(&RoombaMQTTClient::getPixel, this,
                                     placeholders::_1));
    registerCommand("invertPixel", bind(&RoombaMQTTClient::invertPixel, this,
                                        placeholders::_1));
    registerCommand("cylon", bind(&RoombaMQTTClient::cylon, this,
                                  placeholders::_1));
	// Roomba buttons							  
	registerCommand("clean", bind(&RoombaMQTTClient::clean, this,
                                  placeholders::_1));
	registerCommand("spot", bind(&RoombaMQTTClient::spot, this,
                                  placeholders::_1));
	registerCommand("dock", bind(&RoombaMQTTClient::dock, this,
                                  placeholders::_1));

    senseHAT_.leds.setPixel(x_, y_, Pixel{200, 100, 100});

    data2json();
    std::cerr << "Data in json format = " << jsonData_ << std::endl;
}

volatile sig_atomic_t receivedSIGINT{false};

void handleSIGINT(int /* s */)
{
   receivedSIGINT = true;
}

void RoombaMQTTClient::startClient()
{
	using namespace std;
	
   int majorMosquitto{0};
   int minorMosquitto{0};
   int revisionMosquitto{0};

	try
  {
     
            signal(SIGINT, handleSIGINT);

      cout << "-- MQTT application: " << APPNAME_VERSION << "  ";
      mosqpp::lib_init();
      mosqpp::lib_version(&majorMosquitto, &minorMosquitto, &revisionMosquitto);
      cout << "uses Mosquitto lib version "
           << majorMosquitto
           << '.' << minorMosquitto
           << '.' << revisionMosquitto << endl;

      publishInfo("main()",
                               "--------- Hello " "APPNAME_VERSION" " ---------");
      //RandomWalk rw{mqttSenseHAT.senseHAT_.leds};

		// Checking rc for reconnection, 'clients' is an initializer_list
	   auto clients = {static_cast<mosqpp::mosquittopp*>(this)};
	   cout << "-- MQTT and SenseHAT are ready" << endl;
	   while (!receivedSIGINT)
	   {
		   for (auto client: clients)
		   {
			   int rc = client->loop();
			   if (rc)
			   {
				   cerr << "-- MQTT reconnect" << endl;
				   client->reconnect();
			   }
		   }
	   }
   }
   catch(exception& e)
   {
	   cerr << "-- Exception " << e.what() << endl;
   }
   catch(...)
   {
	   cerr << "-- UNKNOWN EXCEPTION\n";
   }

   cout << "\n-- MQTT application: " << "APPNAME_VERSION" << " stopped"
	     << endl << endl;
   mosqpp::lib_cleanup();
}
/**
 *  @brief Destructor.
 */ 
RoombaMQTTClient::~RoombaMQTTClient()
{
    senseHAT_.leds.clear(Pixel{50, 0, 0});
}

void RoombaMQTTClient::blank(const parameters_t &commandParameters)
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

void RoombaMQTTClient::clear(const parameters_t &commandParameters)
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

void RoombaMQTTClient::invert(const parameters_t &commandParameters)
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

void RoombaMQTTClient::setPixel(const parameters_t &commandParameters)
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

void RoombaMQTTClient::getPixel(const parameters_t &commandParameters)
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

void RoombaMQTTClient::invertPixel(const parameters_t &commandParameters)
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

void RoombaMQTTClient::cylonPar(const parameters_t &commandParameters)
{
    UNUSED(commandParameters);
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

void RoombaMQTTClient::cylon(const parameters_t &commandParameters)
{
    new ParWait{std::bind(&RoombaMQTTClient::cylonPar, this, commandParameters)};
}

void RoombaMQTTClient::handleSensorData()
{
    //    std::string message{
    //       std::to_string(static_cast<int>(senseHAT_.get_humidity()))};
        //publishAddition("json", jsonData_.dump());
}

void RoombaMQTTClient::data2json()
{
   jsonData_["pi"] = pi_;
   jsonData_["happy"] = happy_;
   jsonData_["name"] = name_;
   jsonData_["list"] = list_;
}

void RoombaMQTTClient::sendHeartbeat()
{
    publishAddition("heartbeat" , "json data heartbeat: " + jsonData_.dump());
}

void RoombaMQTTClient::clean(const parameters_t &commandParameters)
{
    if (commandParameters.size() != 0)
    {
        publishError("clean", "number of parameters != 0");
    }
    else
    {
        ioHandler_.Clean();
    }
}

void RoombaMQTTClient::spot(const parameters_t &commandParameters)
{
    if (commandParameters.size() != 0)
    {
        publishError("spot", "number of parameters != 0");
    }
    else
    {
        ioHandler_.Spot();
    }
}

void RoombaMQTTClient::dock(const parameters_t &commandParameters)
{
    if (commandParameters.size() != 0)
    {
        publishError("dock", "number of parameters != 0");
    }
    else
    {
        ioHandler_.Dock();
    }
}





