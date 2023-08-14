#ifndef _LIGHT_SCHEDULER_H_
#define _LIGHT_SCHEDULER_H_

#include <Arduino.h>

#include "relay.h"

class LightScheduler
{
private:
  Relay * light_;
  uint64_t light_duration_;
  time_t start_time_;
  int prev_wday_;
  int start_hour_;
  int start_min_;

public:
  LightScheduler(
    Relay * light, int start_hour, int start_min, uint64_t duration_sec);

  void reset(tm * time);

  void run(tm * time, bool is_bright);
};

#endif