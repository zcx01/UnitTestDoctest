/**
 * @file megaipc_api.h
 * @brief MegaIpcApi definition
 * @date 2021-05-07
 * @copyright Copyright (c) 2021 Megatronix
 */

/*! \mainpage 主页
# 简介
MegaIPC 是Megatronix 进程间通信库, 内部封装了Iceroyx MQTT、UDP组播、和基于UDP的PubSub等多种实现

提供如下多种开发模式： Pub+Sub、 Client+Service、GetProperty+SetProperty 等

# Quick Start
对外提供的API包含在 megaipc::MegaIpcApi, 请从查看 megaipc_api.h 开始
 */
#ifndef MEGA_IPC_API
#define MEGA_IPC_API

#include "ipc_message.h"
#include <string>
#include "singleton/singleton.h"

#ifdef __cplusplus
namespace megaipc
{

    using std::string;

    /**
     * @brief PubSub模式的管理类(单例)
     * 对外提供了统一的API，内部封装了MQTT、UDP等多种SubSub实现
     */
    class MegaIpcApi : public Singleton<MegaIpcApi>
    {
    public:
        MegaIpcApi(Token token);
        virtual ~MegaIpcApi();

        /**
         * 创建 MegaIpcApi 实例对象，用于同一进程内建立多个连接
         * 如果进程内只使用单例模式 可使用 MegaIpcApi::instance() 获取单例对象的引用
         */
        static MegaIpcApi* createInstance();

        // PubSubInterface implement

        /**
         * @brief 初始化连接
         * 
         * @return true 初始化成功
         * @return false 初始化失败
         */
        bool init();

        /**
         * @brief 发布一条消息
         * 
         * @param topic 发布消息的topic
         * @param message 发布的消息结构体 内部可配置消息传输的参数
         * @return true 发布成功
         * @return false 发布失败
         */
        bool publish(const string &topic, const IpcMessage &message);
        
        /**
         * @brief 订阅topic
         * 可多次调用该方法订阅不同的topic
         * @param topic 要订阅的topic字符串
         * @return true 订阅成功
         * @return false 订阅失败
         */
        bool subscribe(const string &topic);

        /**
         * @brief 取消订阅topic
         * 
         * @param topic 要取消订阅的topic
         * @return true 取消订阅成功
         * @return false 取消订阅失败
         */
        bool unSubscribe(const string &topic);
        
        
        /**
         * @brief  销毁释放 init建立连接时占用的资源
         * 
         * @return true 释放成功
         * @return false 释放失败
         */
        bool destroy();

        /** MegaIpcApi 内部对底层 PubSubListenerInterface的虚函数实现*/
        void onMessageArrival(const string &topic, const IpcMessage &msg);
        void onMessageDelivered(const string &msgId);


    private:
    };
}
#endif

#endif // !MEGA_IPC_API
