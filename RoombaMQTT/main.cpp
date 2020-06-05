
#include "AppInfo.h"
#include "../_libMQTT/CommandProcessor.h"
#include "../_libMQTT/MQTTconfig.h"
#include "../_libSenseHAT/SenseHAT.h"
#include "RandomWalk.h"
#include "RoombaMQTTClient.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <csignal>

using namespace std;

volatile sig_atomic_t receivedSIGINT{false};

void handleSIGINT(int /* s */)
{
   receivedSIGINT = true;
}

int main(int argc,char *argv[])
{
   int majorMosquitto{0};
   int minorMosquitto{0};
   int revisionMosquitto{0};

   string mqttBroker{MQTT_LOCAL_BROKER};
   int mqttBrokerPort{MQTT_LOCAL_BROKER_PORT};

   switch (argc)
   {
   case 1:
      // Using MQTT_LOCAL_BROKER and MQTT_LOCAL_BROKER_PORT
      break;
   case 2:
      // Using MQTT_LOCAL_BROKER_PORT
      mqttBroker = string(argv[1]);
      break;
   case 3:
      mqttBroker = string(argv[1]);
      mqttBrokerPort = stoi(argv[2]);
      break;
   default:
      cerr << endl
           << "ERROR command line arguments:\n"
              "\tsenseHAT\n"
              "\tsenseHAT <URL broker>\n"
              "\tsenseHAT <URL broker> <broker port>\n"
           << endl;
      exit(EXIT_FAILURE);
   }

	try
   {
	   signal(SIGINT, handleSIGINT);

      //cout << "-- MQTT application: " << APPNAME_VERSION << "  ";
      mosqpp::lib_init();
      mosqpp::lib_version(&majorMosquitto, &minorMosquitto, &revisionMosquitto);
      cout << "uses Mosquitto lib version "
           << majorMosquitto
           << '.' << minorMosquitto
           << '.' << revisionMosquitto << endl;

	   MQTTClient mqttSenseHAT("MSH", "msh", mqttBroker, mqttBrokerPort);
		mqttSenseHAT.publishInfo("main()",
                               "--------- Hello " "APPNAME_VERSION" " ---------");
      //RandomWalk rw{mqttSenseHAT.senseHAT_.leds};

		// Checking rc for reconnection, 'clients' is an initializer_list
	   auto clients = {static_cast<mosqpp::mosquittopp*>(&mqttSenseHAT)};
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
   return 0;
}
