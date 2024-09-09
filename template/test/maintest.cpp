#include "maintest.hpp"
#include "can_api.h"
void test_main()
{
    init_signal_process();
    IC_SINGLE_SET_UINT32_T(CANSIG_GW_1F3__MdcNicaReminderAcoustic_g,1);
}