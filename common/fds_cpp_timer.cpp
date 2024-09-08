#include "fds_cpp_timer.hpp"
#include "singleton/singleton.h"
#include <memory>
#include "ic_log.h"

#define MINSPACETIME 100
namespace fds
{

    fds_cpp_timer::fds_cpp_timer(/* args */)
    {
        START_TIMING(&fds_cpp_timer::time_out);
        time_out_process->setTimeSpace(MINSPACETIME);
        time_out_process->setLoop(true);
        time_out_process->start();
    }

    int fds_cpp_timer::add(int fristTime, FdsTimeOutProCallFun fun, int spaceTime)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        CallBackFunInfo info;
        info.is_loop = (spaceTime > 0);
        info.spaceTime = info.is_loop ? spaceTime : fristTime;
        info.fun = fun;
        all_id++;
        call_back_funs[all_id]=info;
        if(fristTime == 0)
        {
            fun(all_id);
        }
        return all_id;
    }

    void fds_cpp_timer::remove(int id)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if(call_back_funs.count(id) !=0){
            call_back_funs[id].is_loop = false;
            call_back_funs[id].is_remove = true;
        }
    }

    void fds_cpp_timer::reset(int id)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if(call_back_funs.count(id) !=0)
            call_back_funs[id].is_reset = true;
    }

    bool fds_cpp_timer::is_exist(int id)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if(call_back_funs.count(id) != 0){
            return !call_back_funs[id].is_remove;
        }
        return false;
    }


    void fds_cpp_timer::time_out(float value)
    {
        m_mutex.lock();
        auto call_back_funT = call_back_funs;
        m_mutex.unlock();
        for(auto iter = call_back_funT.begin(); iter != call_back_funT.end(); iter++)
        {
            auto info = (*iter).second;
            auto id = (*iter).first;
            info.count++;
            try
            {
                if (info.count * MINSPACETIME >= info.spaceTime)
                {
                    if (!info.is_remove && info.fun != nullptr)
                    {
                        info.fun(id);
                    }
                    if (!info.is_loop)
                    {
                        call_back_funs.erase(id);
                        continue;
                    }
                    else
                    {
                        info.count = 0;
                    }
                }
            }
            catch(...)
            {
                IC_LOG_INFO(" %d throw",id);
            }
            
            m_mutex.lock();
            if(call_back_funs[id].is_reset)
            {
                call_back_funs[id].count = 0;
                call_back_funs[id].is_reset = false;
            }
            else
            {
                call_back_funs[id].count = info.count;
            }
            m_mutex.unlock();
        }
    }

    class CppTimerSingleton : public Singleton<CppTimerSingleton>
    {
    public:
        CppTimerSingleton(Token t) : m_timer(new fds::fds_cpp_timer())
        {
        }
        static fds::fds_cpp_timer *getTimer()
        {
            return instance().m_timer.get();
        }

    private:
        std::unique_ptr<fds::fds_cpp_timer> m_timer = nullptr;
    };

    fds_cpp_timer * getTimer()
    {
        return CppTimerSingleton::getTimer();
    }
} // namespace fds

