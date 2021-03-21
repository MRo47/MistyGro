#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <Arduino.h>

struct PhCalib
{
    float acid;
    float neutral;
    float base;
};

namespace constants
{
    static const float adc_res = 1024.0;
    static const float adc_ref_v = 3.3;
    static const long ph_calib_timeout = 30000; //30 sec
    static const long ec_calib_timeout = 20000; //20 sec
    static const PhCalib ph_low_limit{1830, 1300, 775}; //ph low limits
    static const PhCalib ph_high_limit{2230, 1700, 1175}; //ph high limits
    static const PhCalib default_ph_data{2030, 1500, 975};
    static const float default_ec_calib = 1;
    static const float tds_factor = 0.5; // tds = ec/2
    static const int sample_size = 10;
}

#endif