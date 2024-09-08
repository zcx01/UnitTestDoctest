#ifndef TELLTALE_INFO_H
#define TELLTALE_INFO_H

#include <stdint.h>
#include <string>
#include "nlohmann/json.hpp"
#include "enums/common_enums.h"

/** @brief 仪表指示灯信息 */
struct TelltaleInfo
{
    enum LampColor color;  /*! 颜色 */
    int32_t period;        /*! 闪烁周期(ms) >0 有效， <=0 无效*/
    float dutyCycle;       /*! 占空比 0-1 */
    int32_t blinkDuration; /*! 闪烁时长(ms) >0 有效， <=0 无效; */
    int finalStatus;       /*！ 闪烁最后的状态，如果值为-1 超过该时长 指示灯状态变为常亮或常灭 取决于 value */

    TelltaleInfo(enum LampColor _color = LampColor::DEFAULT, int32_t _period = 0, float _dutyCycle = 0, int32_t _blinkDuration = 0,int _finalStatus=-1)
    {
        color = _color;
        period = _period;
        dutyCycle = _dutyCycle;
        blinkDuration = _blinkDuration;
        finalStatus = _finalStatus;
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(TelltaleInfo, color, period, dutyCycle, blinkDuration,finalStatus);
};

#endif // !TELLTALE_INFO_H