#include "maintest.hpp"
#include "can_api.h"
#include "base_fds_module.hpp"
#include <set>
#include <map>
#include "icdoctest.h"

std::map<struct veh_signal *, std::set<std::shared_ptr<BaseFdsModule>>> signal_modules_map;
bool isPrintLog = true;
void test_main()
{
    init_signal_process();
    // IC_SINGLE_SET_UINT32_T(CANSIG_GW_1F3__MdcNicaReminderAcoustic_g,1);

    for(auto iter : signal_modules_map)
    {
        IC_LOG_INFO("signal: %s",iter.first->sig_name);
        veh_signal *signal_addr = iter.first;
        if(signal_addr)
        {
            uint32_t minValue = 0;
            uint32_t maxValue = std::pow(2,signal_addr->sig_length)-1;
            for(uint32_t i=minValue;i<=maxValue;i++)
            {
                IC_LOG_INFO("signal: %s, value: %d, max:%d",signal_addr->sig_name,i,maxValue);
                // IC_SINGLE_SET_UINT32_T(signal_addr,i);
            }
        }
    }
}