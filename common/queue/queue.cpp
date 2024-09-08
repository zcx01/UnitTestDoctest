#include "queue.h"
#include <chrono>
#include <condition_variable>
#include <queue>
#include <unordered_map>
#include <mutex>
#include <utility>

namespace PolyIC {

class Queue::Impl
{
public:
    Impl() :queue_(), queueMutex_(),queueMaxSize_(0),msgIDQueue_(), msgMap_(), msgMapMutex_(), msgMapCond_()
    {
    }

    void put(Msg&& msg)
    {
        {
            std::lock_guard<std::mutex> lock(queueMutex_);
            if(queueMaxSize_ == 0 || queueMaxSize_ > queue_.size())
            {
                queue_.push(msg.move());
            }
            else
            {
                return;
            }
        }

        queueCond_.notify_one();
    }

    std::unique_ptr<Msg> get(int timeoutMillis)
    {
        std::unique_lock<std::mutex> lock(queueMutex_);

        if (timeoutMillis <= 0)
            queueCond_.wait(lock, [this]{return !queue_.empty();});
        else
        {
            // wait_for returns false if the return is due to timeout
            auto timeoutOccured = !queueCond_.wait_for(
                lock,
                std::chrono::milliseconds(timeoutMillis),
                [this]{return !queue_.empty();});

            if (timeoutOccured)
                queue_.emplace(new Msg(MESSAGE_TIMEOUT));
        }

        auto msg = queue_.front()->move();
        queue_.pop();
        return msg;
    }


    void putUnique(Msg&& msg)
    {
        {
            std::lock_guard<std::mutex> lock(msgMapMutex_);
            auto id = msg.getMsgId();
            if (msgMap_.count(id) == 0)
            {
                msgIDQueue_.push(id);
            }
            else
            {
                msgMap_.erase(id);
            }
            msgMap_[id] = msg.move();
        }

        msgMapCond_.notify_one();
    }



    std::unique_ptr<Msg> getUnique(int timeoutMillis)
    {
        std::unique_lock<std::mutex> lock(msgMapMutex_);

        if (timeoutMillis <= 0)
            msgMapCond_.wait(lock, [this]{return !msgMap_.empty();});
        else
        {
            // wait_for returns false if the return is due to timeout
            auto timeoutOccured = !msgMapCond_.wait_for(
                lock,
                std::chrono::milliseconds(timeoutMillis),
                [this]{return !msgMap_.empty();});

            if (timeoutOccured)
                return nullptr;
        }

        auto id = msgIDQueue_.front();
        msgIDQueue_.pop();
        auto msg = msgMap_[id]->move();
        msgMap_.erase(id);
        return msg;
    }

    // size_t size()
    // {
    //     std::unique_lock<std::mutex> lock(queueMutex_);
    //     auto size = queue_.size();
    //     return size;
    // }

    uint32_t size()
    {
        return queue_.size();
    }

    void setQueueMaxSize(const uint32_t &maxSize)
    {
        queueMaxSize_ = maxSize;
    }

private:
    // Queue for the Msgs
    std::queue<std::unique_ptr<Msg>> queue_;

    // Mutex to protect access to the queue
    std::mutex queueMutex_;

    // Condition variable to wait for when getting Msgs from the queue
    std::condition_variable queueCond_;

    // Queue max size
    uint32_t queueMaxSize_;

    // Queue for the Msg Id
    std::queue<int> msgIDQueue_;

    // Map to keep Msg
    std::unordered_map<int, std::unique_ptr<Msg>> msgMap_;

    // Mutex to protect access to the msgMap
    std::mutex msgMapMutex_;

     // Condition variable to wait for when getting Msgs from the map
    std::condition_variable msgMapCond_;
};

Queue::Queue()
  : impl_(new Impl)
{
}

Queue::~Queue()
{
}

void Queue::put(Msg&& msg)
{
    impl_->put(std::move(msg));
}

std::unique_ptr<Msg> Queue::get(int timeoutMillis)
{
    return impl_->get(timeoutMillis);
}

void Queue::putUnique(Msg&& msg)
{
    impl_->putUnique(std::move(msg));
}

std::unique_ptr<Msg> Queue::getUnique(int timeoutMillis)
{
    return impl_->getUnique(timeoutMillis);
}

int Queue::getSize()
{
    return impl_->size();
}

void Queue::setQueueMaxSize(const uint32_t &maxSize)
{
    impl_->setQueueMaxSize(maxSize);
}
}
