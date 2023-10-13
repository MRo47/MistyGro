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

#ifndef _TIMER_H_
#define _TIMER_H_

#include <WiFi.h>

/**
 * @brief Timer that syncs with NTP server
 * 
 */
class Timer
{
private:
  static const char * ntp_server_;

public:
  Timer();

  /**
   * @brief Get the utc time now
   * 
   * @return tm 
   */
  tm get_utc_time();

  /**
   * @brief Get the seconds since epoch now
   * 
   * @return time_t 
   */
  time_t get_epoch_time();

  /**
   * @brief Print the seconds since epoch
   * 
   */
  void print_utc_time();

  /**
   * @brief initialise the timer, set a sync interval to sync with NTP server
   * 
   * @param sync_interval_ms sync interval in milliseconds
   */
  void begin(long int sync_interval_ms = 600000);  // 10 mins
};

#endif