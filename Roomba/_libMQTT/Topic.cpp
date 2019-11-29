#include "Topic.h"
#include "Tokenizer.h"

Topic::Topic():
   topic_{""},
   cachedSplit_{}
{}

Topic::Topic(const std::string& root):
   topic_{root},
   cachedSplit_{split(topic_, isForwardSlash)}
{}

Topic& Topic::add(const std::string& item)
{
   topic_ += "/" + item;
   cachedSplit_ = split(topic_, isForwardSlash);
   return *this;
}

Topic& Topic::add(const char* pItem)
{
   topic_ += ("/" + std::string(pItem));
   cachedSplit_ = split(topic_, isForwardSlash);
   return *this;
}

std::string Topic::operator[](const int nIndex) const
{
   if (nIndex < cachedSplit_.size()) {
      return cachedSplit_[nIndex];
   }
   return "";
}
