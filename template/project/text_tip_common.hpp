#pragma once

#include "fds_common_codes.hpp"
#include <string>

namespace fds
{
    void addTextInfo(std::string topic, int value);

    void addTextInfo(std::string topic, int value,bool valid);

    void setVariableText(const std::string &topic,const int &value,const int &textPos,const std::string &text);
}
