#ifndef COMMON_ENUMS_H
#define COMMON_ENUMS_H

/** @brief 仪表指示灯颜色 */
enum LampColor
{
    DEFAULT = 0,
    YELLOW = 1,
    RED = 2,
    BLUE = 3,
    WHITE = 4
};

/** @brief 仪表指示灯状态 */
enum LampState
{
    TELLTALE_OFF = 0,   //灭
    TELLTALE_ON = 1     //亮
};

/**
* @brief 蜂鸣操作
*/
enum ChimeInfoState
{
    CHIMEINFO_STOP = 0,  // 停止
    CHIMEINFO_START = 1, // 启动
};

/**
 * @brief 功能状态枚举
 */
enum SwitchState
{
    STATE_DISABLE = 0x0,
    STATE_ENABLE  = 0x1,
    STATE_INVALID = 0xFF,
    STATE_CLOSE   = 0x0,
    STATE_OPEN    = 0x1
};
#endif // !COMMON_ENUMS_H
