#ifndef DRIVING_INFO_H
#define DRIVING_INFO_H

#include <stdint.h>
#include <string>
#include "nlohmann/json.hpp"

/** @brief 仪表行车信息 */
struct DrivingInfo
{
    float value;     /*! 数值 */
    uint8_t decimal; /*! 小数点后的位数 */
    bool valid;      /*! 是否有效 */

    DrivingInfo(float _value = 0, uint8_t _decimal=0, bool _valid = false)
    {
        value = _value;
        decimal = _decimal;
        valid = _valid;
    }
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(DrivingInfo, value, decimal, valid);
};

#endif // !DRIVING_INFO_H
