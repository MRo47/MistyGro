#include "light_scheduler.h"

LightScheduler::LightScheduler(Relay * light, uint64_t light_duration_sec)
: light_(light),
  light_duration_(light_duration_sec),
  end_time_(0),
  prev_wday_(0)  // sunday
{
}

void LightScheduler::run(
  tm * time, bool is_bright)  // needs a daylight cycle between runs
{
  if (time->tm_wday != prev_wday_)  // day changed
  {
    end_time_ = 0;  // reset endtime
    prev_wday_ = time->tm_wday;
  }

  time_t epoch_time = mktime(time);

  if (end_time_ == 0 && is_bright)  // first entry and first bright time
  {
    end_time_ = epoch_time + light_duration_;
  }

  if (
    end_time_ != 0 && epoch_time < end_time_ &&
    !is_bright) {  // when end set and not end
    light_->set(Switch::ON);
    Serial.println("Light on");
  } else {
    light_->set(Switch::OFF);
    Serial.println("Light off");
  }
}
