/*
 * Copyright 2023 Myron Rodrigues
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <Arduino.h>

namespace constants
{
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
static const int misters = 12;
static const int light = 14;
static const int extra_relay = 27;
}  // namespace pin

/**
 * @brief Calculate median of a float array
 * 
 * @param arr float array
 * @param size size of array
 * @return float median
 */
inline float median(float * arr, int size)
{
  if (size % 2 == 0) {
    return (arr[int(size * 0.5)] + arr[int((size - 1) * 0.5)]) * 0.5;
  }
  return arr[int(size * 0.5)];
}

#endif