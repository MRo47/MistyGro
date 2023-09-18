#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <Arduino.h>

struct PhCalib
{
  float slope;
  float intercept;
};

namespace constants
{
static const long ph_calib_timeout = 30000;  // 30 sec
static const long ec_calib_timeout = 20000;  // 20 sec
static const int ec_samples = 10;            // samples taken for computing mean
static const int ec_calib_magic = 99;        // if ec calib found
static const int ph_calib_magic = 88;        // if calib found
static const int ph_samples = 10;            // samples of ph to compute mean
static const PhCalib default_ph_data{2030, 1500};
static const float default_ec_calib = 1;
static const float tds_factor = 0.5;  // tds = ec/2
static const int sample_size = 10;
static const uint8_t adc_bus_num = 0;
static const uint8_t adc_bus_addr = 0x48;
static const float ldr_thresh_v = 3.5;
static const unsigned long mister_toggle_time = 10 * 60;       // 10 mins
static const unsigned long temperature_check_time = 10 * 60;   // 10 mins
static const unsigned long light_check_n_set_time = 5 * 60;    // 5 mins
static const unsigned long check_token_refresh_time = 1 * 60;  // 1 min
static const int light_start_hour = 6;                         // GMT
static const int light_start_min = 0;                          // GMT
static const unsigned long light_duration = 12 * 60 * 60;      // 12 hours
static const unsigned long wifi_check_time = 1 * 60;           // sec
}  // namespace constants

namespace pin
{
static const int temp_sensor_bus = 32;  // pin
static const int adc_scl = 22;
static const int adc_sda = 21;
static const int ec_enable = 17;
static const int misters = 12;
static const int light = 14;
static const int extra_relay = 27;
static const int ph_enable = 5;
}  // namespace pin

inline float median(float * arr, int size)
{
  if (size % 2 == 0) {
    return (arr[int(size * 0.5)] + arr[int((size - 1) * 0.5)]) * 0.5;
  }
  return arr[int(size * 0.5)];
}

#endif