#include "test.hpp"
#include <iostream>
#include "ipc/megaipc_api.h"
test::test(/* args */) 
{

}

void test::test_function(std::string topic, std::string msg)
{
    IpcMessage message = {(uint32_t)msg.length(), (uint8_t *)msg.data()};
    megaipc::MegaIpcApi::instance().publish(topic,message);
}

void test::test_function2(std::string topic, std::string msg)
{
    int i = 0;
    while(i < 10)
    {
        IpcMessage message = {(uint32_t)msg.length(), (uint8_t *)msg.data()};
        megaipc::MegaIpcApi::instance().publish(topic,message);
        i++;
    }
}
