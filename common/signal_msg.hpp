#pragma once

#include "parser_typedef.h"

class SignalMsg
{
public:
    struct veh_signal *signal_addr;
    bool is_timeout;
};