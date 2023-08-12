#ifndef _LIGHT_SCHEDULER_H_
#define _LIGHT_SCHEDULER_H_

#include <Arduino.h>

#include "relay.h"

class LightScheduler
{
private:
  Relay * light_;
  uint64_t light_duration_;
  time_t end_time_;
  int prev_wday_;

public:
  LightScheduler(Relay * light, uint64_t light_duration_sec);

  void run(tm * time, bool is_bright);
};

#endif