#ifndef _LIGHT_SCHEDULER_H_
#define _LIGHT_SCHEDULER_H_

#include <Arduino.h>

#include "relay.h"

/**
 * @brief Schedules light switching depending on time of day and ambient light
 * 
 */
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
  /**
   * @brief Construct a new Light Scheduler object
   * 
   * @param light Relay used for light
   * @param start_hour start hour in 24h format
   * @param start_min start min 
   * @param duration_sec total light duration required for the plant in seconds
   */
  LightScheduler(
    Relay * light, int start_hour, int start_min, uint64_t duration_sec);

  /**
   * @brief reset start time to given time
   * 
   * @param time time vale to set to
   */
  void reset(tm * time);

  /**
   * @brief Run this in a loop and pass the current time and a boolean indicating if its bright
   * 
   * @param time time struct of time now
   * @param is_bright boolean flag if its bright now
   */
  void run(tm * time, bool is_bright);
};

#endif