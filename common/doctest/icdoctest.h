#pragma once
#include "doctest.h"
#include "Internal_message_center.h"
#include "test.hpp"

#define IC_SINGLE_SET_UINT32_T(sig,value) {union veh_signal_value raw_value; \
        raw_value.val_uint32_t = value; \
        sig.is_timeout = false; \
        sig.SetValue.fpSetter(nullptr, &raw_value); \
}

#define IC_CHECK_FUN(topic,value,func,...) {func(topic,__VA_ARGS__); \
std::string topicValue; \
fds::getTopicValue(topic,topicValue); \
CHECK(topicValue == value); \
}


#define IC_CHECK_VALUE(topic,value) {std::string topicValue; \
fds::getTopicValue(topic,topicValue); \
CHECK(topicValue == value); \
}
