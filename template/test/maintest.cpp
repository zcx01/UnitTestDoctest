#include "maintest.hpp"
#include "can_api.h"
#include "base_fds_module.hpp"
#include <set>
#include <map>
#include "icdoctest.h"

std::map<struct veh_signal *, std::set<std::shared_ptr<BaseFdsModule>>> signal_modules_map;
void test_main()
{
    init_signal_process();
    // IC_SINGLE_SET_UINT32_T(CANSIG_GW_1F3__MdcNicaReminderAcoustic_g,1);
}