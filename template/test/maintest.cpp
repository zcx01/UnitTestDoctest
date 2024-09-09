#include "maintest.hpp"
#include "icdoctest.h"
#include "can_api.h"
#include "fds_can_main_entry.hpp"

void test_main()
{
    init_signal_process();
    IC_SINGLE_SET_UINT32_T(CANSIG_GW_1F3__MdcNicaReminderAcoustic_g,1);
}