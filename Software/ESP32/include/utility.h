#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <Arduino.h>

struct PhData
{
    float ph4_v;
    float ph7_v;
};

namespace constants
{
    static const float adc_res = 1024.0;
    static const float ph7_volt_at_25C = 1134;
}

#endif