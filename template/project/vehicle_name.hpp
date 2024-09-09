#pragma once
#include <string>
#define ECU_TABLE_USER_POWER_MODE 0
#define ECU_TABLE_USER_C385_VEHICLE_TYPE 1
#define ECU_TABLE_USER_DA_SOLUTION  2

class VehicleName 
{
public:

    static int getEcuConfig(uint32_t id);
};