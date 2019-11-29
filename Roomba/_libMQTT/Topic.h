#ifndef TOPIC_H
#define TOPIC_H

#include <string>
#include <vector>

/// The class #Topic represents a MQTT topic string.
/// A topic string consists of text tokens separated by a foreward slash.
/// Topic objects are copyable. Strings can be added to the contained
/// #topic_ string. A forward slash is automacicalley added as a seperator.
/// Every topic token is readable by the array index operator.
/// If the index value is out of range an empty string will be returned.
class Topic
{
public:
   Topic();
   Topic(const std::string& root);
   Topic(const Topic& other) = default;
   Topic& operator=(const Topic& other) = default;
   virtual ~Topic() = default;

   Topic& add(const std::string& item);
   Topic& add(const char* pItem);
   const char* c_str() const { return topic_.c_str(); }
   std::string operator[](const int nIndex) const;
private:
   std::string topic_;
   std::vector<std::string> cachedSplit_;
};

#endif // TOPIC_H
