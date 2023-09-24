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