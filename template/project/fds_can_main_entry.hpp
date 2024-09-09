#pragma once

#include "parser_typedef.h"

#ifdef __cplusplus
extern "C"
{
#endif
    extern void init_signal_process();

    extern void CAN_SetMsgChangeHandler(fpMsgChangeHandler_t func);
    extern void CAN_SetSigChangeHandler(fpSigChangeHandler_t func);
    extern void CAN_SetMsgTimeoutHandler(fpMsgTimeoutHandler_t func);
    extern void CAN_MessageElapseTime(int bus_id, int time_ms, int restart);


    extern void LIN_SetSigChangeHandler(fpSigChangeHandler_t func);
    extern void LIN_SetMsgTimeoutHandler(fpMsgTimeoutHandler_t func);

    extern void init_signal_process_up();
    extern void init_signal_process_down();
    extern void qnx_timer_handler();
    extern void CAN_PARSER_Init();
#ifdef __cplusplus
}
#endif