#pragma once
#include "doctest.h"
#include "Internal_message_center.h"
#include "struct/telltale_info.h"
#include "struct/payload_info.h"
#include "ic_log.h"
static bool equationTelltaleInfo(const TelltaleInfo &mapvalue,const TelltaleInfo &value)
{
        return mapvalue.blinkDuration == value.blinkDuration && mapvalue.color == value.color && mapvalue.dutyCycle == value.dutyCycle && mapvalue.finalStatus == value.finalStatus && mapvalue.period == value.period;
}

#define IC_SINGLE_SET_UINT32_T(sig,value) {union veh_signal_value raw_value; \
raw_value.val_uint32_t = value; \
if(sig){ \
sig->is_timeout = false; \
if(sig->SetValue.fpSetter != nullptr){ \
sig->SetValue.fpSetter(nullptr, &raw_value); \
}\
else\
{\
   IC_LOG_ERROR("sig set is nullptr") \
}\
/*需要睡眠，让module里面的线程处理改变的信号*/ \
std::this_thread::sleep_for(std::chrono::milliseconds(1)); \
}\
}

#define IC_SINGLE_TIMEOUT(sig) {if(sig){union veh_signal_value raw_value; \
sig->GetValue.fpGetter(nullptr, &raw_value); \
sig->is_timeout = true; \
if(sig->SetValue.fpSetter != nullptr){ \
sig->SetValue.fpSetter(nullptr, &raw_value); \
}\
else\
{\
   IC_LOG_ERROR("sig set is nullptr") \
}\
}\
}


#define IC_CHECK_FUN(topic,value,func,...) {func(topic,__VA_ARGS__); \
std::string topicValue; \
fds::getTopicValue(topic,topicValue); \
CHECK(topicValue == value); \
}


#define IC_CHECK_STRING(topic,value) {std::string topicValue; \
fds::getTopicValue(topic,topicValue); \
CHECK(topicValue == value); \
}

#define IC_CHECK_FLOAT(topic,value) {float topicValue; \
fds::getTopicValue(topic,topicValue); \
CHECK(topicValue == value); \
}

#define IC_CHECK_VALUE(topic,topicValue) {std::string content; \
fds::getTopicValue(topic,content); \
if(content.empty()) \
{\
IC_LOG_ERROR("get topic  failed");\
CHECK(false);\
}\
else \
{\
nlohmann::json j = nlohmann::json::parse(content);\
PayloadInfo info = j.get<PayloadInfo>();\
CHECK(info.value == topicValue); \
} \
}

#define IC_CHECK_TEXT(topic,value) IC_CHECK_FLOAT(topic,value)

#define IC_CHECK_CHIME(topic,value) IC_CHECK_VALUE(topic,value)

#define IC_CHECK_TELLTALE(topic,topicValue,telltaleInfo) {std::string content; \
fds::getTopicValue(topic,content); \
if(content.empty()) \
{\
IC_LOG_ERROR("get topic failed");\
CHECK(false);\
}\
else\
{\
        nlohmann::json j = nlohmann::json::parse(content);\
        PayloadInfo info = j.get<PayloadInfo>();\
        TelltaleInfo tInfo = info.extension.get<TelltaleInfo>();\
        CHECK(info.value == topicValue && equationTelltaleInfo(telltaleInfo,tInfo)); \
}\
}
