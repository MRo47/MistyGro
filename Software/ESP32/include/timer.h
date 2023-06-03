#ifndef _TIMER_H_
#define _TIMER_H_

#include <WiFi.h>

/**
 * @brief Make sure WiFi is configured before calling begin on this
 * 
 */
class Timer
{
private:
  static const char * ntp_server_;

public:
  Timer();

  tm get_utc_time();

  time_t get_epoch_time();

  void print_utc_time();

  void begin(long int sync_interval_ms = 600000);  // 10 mins
};

#endif