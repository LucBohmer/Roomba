#include "CommandProcessor.h"
#include "MQTTconfig.h"
#include "Tokenizer.h"
#include "Topic.h"
#include <iostream>

CommandProcessor::CommandProcessor(const std::string& appname,
                                   const std::string& clientname,
                                   const std::string& host,
                                   int port)
   : mosqpp::mosquittopp{(HOSTNAME + appname + clientname).c_str()}
   , appname_{appname}
   , clientname_{clientname}
   , topicRoot_{MQTT_TOPIC_ROOT}
   , topicCommandRoot_{MQTT_TOPIC_ROOT}
   , commands_{}
{
   topicRoot_.add(appname_).add(clientname_);
   topicCommandRoot_.add(appname_).add(clientname_).add("command");
   std::cerr << __func__ << " command topic: " << topicCommandRoot_.c_str()
             << std::endl;
   connect(host.c_str(), port, MQTT_KEEP_ALIVE);
}

CommandProcessor::~CommandProcessor()
{
   disconnect();
}

void CommandProcessor::on_message(const mosquitto_message* message)
{
   executeCommand((char*)message->payload);
}

void CommandProcessor::on_connect(int rc)
{
   if (rc == 0)
   {
      subscribe(nullptr, topicCommandRoot_.c_str());
   }
}

void CommandProcessor::on_log(int level, const char *str)
{
   //std::cerr << "---- # log CommandProcessor " << level << ": " << str
   //          << std::endl;
}

void CommandProcessor::registerCommand(const std::string& command,
                                       commandfunction cfunction)
{
   std::cerr << "CommandProcessor::registerCommand  " << command << std::endl;
   if (!commandIsRegistered(command))
   {
      commands_[command] = cfunction;
      publishInfo(command, " registered");
   }
   else
   {
      publishWarning(command, " already registered");
   }
}

void CommandProcessor::executeCommand(const std::string& command)
{
   std::vector<std::string> commandpars {split(command)};
   std::cerr << "CommandProcessor::executeCommand  " << command << std::endl;
   if (commandIsRegistered(commandpars[0]))
   {
      commands_[commandpars[0]](
               std::vector<std::string>(std::begin(commandpars) + 1,
                                        std::end(commandpars)));
   }
   else
   {
      publishError(commandpars[0], " unknown command");
   }
}

void CommandProcessor::executeCommands(const std::vector<std::string>& commands)
{
   for (const auto& command : commands)
   {
      executeCommand(command);
   }
}

bool CommandProcessor::commandIsRegistered(const std::string& command) const
{
   return commands_.find(command) != std::end(commands_);
}

void CommandProcessor::publishAddition(const std::string& topicAddition,
                                       const std::string& message)
{
   Topic topic{topicRoot_};
   topic.add(topicAddition);
   publish(nullptr, topic.c_str(), message.size(), message.c_str());
}

void CommandProcessor::publishReturn(const std::string& command,
                                     const std::string& message)
{
   publishAddition("command/" + command + "/return", message);
}

void CommandProcessor::publishInfo(const std::string& command,
                                   const std::string& message)
{
   publishAddition("command/" + command + "/info", message);
}

void CommandProcessor::publishWarning(const std::string& command,
                                      const std::string& message)
{
   publishAddition("command/" + command + "/warning", message);
}

void CommandProcessor::publishError(const std::string& command,
                                    const std::string& message)
{
   publishAddition("command/" + command + "/error", message);
}
