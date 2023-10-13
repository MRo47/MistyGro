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

#include "scheduler.h"

#include <Arduino.h>

Scheduler::Scheduler() : num_tasks_(0) {}

void Scheduler::create_task(void (*task_func)(), unsigned long interval_sec)
{
  if (num_tasks_ < MAX_TASKS) {
    tasks_[num_tasks_].task_func = task_func;
    tasks_[num_tasks_].interval = interval_sec;
    tasks_[num_tasks_].last_execution_time = 0;
    num_tasks_++;
  }
}

void Scheduler::run()
{
  for (;;) {
    time_t current_time = timer_.get_epoch_time();
    for (int i = 0; i < num_tasks_; i++) {
      if (current_time - tasks_[i].last_execution_time >= tasks_[i].interval) {
        tasks_[i].last_execution_time = current_time;
        tasks_[i].task_func();
      }
    }
    // Additional code to be executed in the main loop can go here
  }
}

void Scheduler::begin(long int timer_sync_interval_ms)
{
  timer_.begin(timer_sync_interval_ms);
}