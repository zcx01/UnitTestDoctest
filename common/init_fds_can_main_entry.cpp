#include "init_fds_can_main_entry.hpp"
#include <map>
#include <memory>
#include <iostream>
#include <chrono>
#include <thread>
#include <set>
#include <mutex>
#include "ic_log.h"
#include "megaipc_api.h"
#include "queue.h"
#include "signal_msg.hpp"
#include "base_fds_module.hpp"

using namespace megaipc;
class BaseFdsModule;
/* mutex to protect simutanous access
  to can message variable between UDP receive thread and timer thread. */
std::mutex can_data_mutex;
extern std::map<struct veh_signal *, std::set<std::shared_ptr<BaseFdsModule>>> signal_modules_map;
static std::set<std::string> filter_sig_name;

// #define SIGDEBUG

void signal_changed_callback(struct veh_signal *signal, int type)
{
#ifdef SIGDEBUG
    if (filter_sig_name.count(std::string(signal->sig_name, strlen(signal->sig_name))) != 0)
    {
        return;
    }
#endif
    IC_LOG_DEBUG("sig_name %s",signal->sig_name);
    SignalMsg m{signal, false};
    auto module_set = signal_modules_map[signal];
    bool is_call_back = true;
    for (auto &module : module_set)
    {
        is_call_back = false;
        module->putUnique(PolyIC::DataMsg<SignalMsg>(signal->unique_id, m));
    }
}

void meassage_changed_callback(struct veh_message *message, int type)
{
}

void SendTopic(std::string topic, std::string msg, int log)
{
    if(log == 1){
        IC_LOG_INFO("topic: %s msg: %s",topic.c_str(), msg.data());
    }else
    {
        IC_LOG_DEBUG("topic: %s msg: %s",topic.c_str(), msg.data());
    }
    
    IpcMessage message = {(uint32_t)msg.length(), (uint8_t *)msg.data(), true};
    MegaIpcApi::instance().publish(topic, message);
}

void SendCan(const uint8_t *data, uint32_t data_len,bool spi_flag)
{
    //fds::MessageProxy::instance().publish(spi_flag ? SPIRPC_SVC_TOPIC_VEH_CTRL_REQ : UARTRPC_SVC_TOPIC_VEH_CTRL_REQ, data, data_len, true);
}

void message_timeout_callback(struct veh_message *message, int type)
{
    IC_LOG_WARNING("message id timeout: %08x", message->msg_id);
    struct veh_signal **pp_signal = (struct veh_signal **)message->signal_array_addr;
    struct veh_signal *signal;

    for (; *pp_signal != NULL; pp_signal++)
    {
        signal = *pp_signal;
        // printf("--signal uid: %X\n", signal->unique_id);
        SignalMsg m{signal, true};
        bool is_call_back = true;
        auto module_set = signal_modules_map[signal];
        for (auto &module : module_set)
        {
            is_call_back = false;
            module->putUnique(PolyIC::DataMsg<SignalMsg>(signal->unique_id, m));
        }
    }
}

void set_can_parser_callbacks()
{
    CAN_SetSigChangeHandler(signal_changed_callback);
    CAN_SetMsgChangeHandler(meassage_changed_callback);
    CAN_SetMsgTimeoutHandler(message_timeout_callback);
}

void set_lin_parser_callbacks()
{
    LIN_SetSigChangeHandler(signal_changed_callback);
    LIN_SetMsgTimeoutHandler(message_timeout_callback);
}

void qnx_timer_handler()
{
    // std::lock_guard<std::mutex> lk(can_data_mutex);

    CAN_MessageElapseTime(0, 100, 0);
    CAN_MessageElapseTime(1, 100, 0);
}

void init_signal_process_up()
{
#ifdef SIGDEBUG
    filter_sig_name.insert("BcuBattI");
#endif
    IC_LOG_INFO("init_signal_process");
    set_can_parser_callbacks();
    set_lin_parser_callbacks();
}

void init_signal_process_down()
{
}
