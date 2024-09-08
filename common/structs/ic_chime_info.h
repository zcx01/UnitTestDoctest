#ifndef IC_CHIME_INFO_H__
#define IC_CHIME_INFO_H__

#include <stdint.h>
#include <string>
#include "nlohmann/json.hpp"
#include "enums/common_enums.h"

/** @brief 蜂鸣/语音信息 */
struct ChimeInfo
{
    uint32_t value; /*! 数值 */

    ChimeInfo(uint32_t _value = 0)
    {
        value = _value;
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ChimeInfo, value);
};

#endif