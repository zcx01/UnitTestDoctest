#include "megaipc_api.h"
#include "Internal_message_center.h"

megaipc::MegaIpcApi::MegaIpcApi(Token token)
{
}

megaipc::MegaIpcApi::~MegaIpcApi()
{
}

bool megaipc::MegaIpcApi::publish(const string &topic, const IpcMessage &message)
{
    std::string content((char *)message.data, message.length);
    fds::callTopicChanged(topic, content);
    return false;
}