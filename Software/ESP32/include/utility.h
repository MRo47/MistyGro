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
    const float adc_res = 1024.0;
    const int ph_data_add = 0;
}

#endif