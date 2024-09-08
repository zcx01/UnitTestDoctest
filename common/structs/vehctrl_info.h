#ifndef VEHCTRL_INFO_H
#define VEHCTRL_INFO_H

#include <stdint.h>
#include <string>
#include "nlohmann/json.hpp"

/** @brief 车控信息 */
struct VehCtrlInfo
{
    float value; /*! 数值 */

    VehCtrlInfo(float _value = 0)
    {
        value = _value;
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(VehCtrlInfo, value);
};

#endif // !VEHCTRL_INFO_H