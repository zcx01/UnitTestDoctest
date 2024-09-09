#include "text_tip_common.hpp"
#include "Internal_message_center.h"

void fds::addTextInfo(std::string topic, int value)
{
    fds::callTopicChanged(topic,value);
}

void fds::addTextInfo(std::string topic, int value, bool valid)
{
    fds::callTopicChanged(topic, value);
}

void fds::setVariableText(const std::string &topic,const int &value,const int &textPos,const std::string &text)
{
}
