// Copyright 2023 Myron Rodrigues
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "light_scheduler.h"

LightScheduler::LightScheduler(
  Relay * light, int start_hour, int start_min, uint64_t duration_sec)
: light_(light),
  start_hour_(start_hour),
  start_min_(start_min),
  light_duration_(duration_sec),
  start_time_(0),
  prev_wday_(0)  // sunday
{
}

void LightScheduler::reset(tm * time)
{
  tm start = *time;
  start.tm_hour = start_hour_;
  start.tm_min = start_min_;
  start.tm_sec = 0;
  start_time_ = mktime(&start);
  Serial.printf("Light start time: %ld\n", start_time_);
}

void LightScheduler::run(
  tm * time, bool is_bright)  // needs a daylight cycle between runs
{
  time_t epoch_time = mktime(time);

  if (
    time->tm_wday != prev_wday_ ||
    start_time_ == 0)  // day changed or first init
  {
    reset(time);
    prev_wday_ = time->tm_wday;
  }

  if (
    epoch_time > start_time_ && epoch_time <= start_time_ + light_duration_ &&
    !is_bright) {  // when end set and not end
    light_->set(Switch::ON);
    Serial.println("Light on");
  } else {
    light_->set(Switch::OFF);
    Serial.println("Light off");
  }
}
