#include "scheduler.h"

#include <Arduino.h>

Scheduler::Scheduler() : num_tasks_(0) {}

void Scheduler::create_task(void (*task_func)(), unsigned long interval)
{
  if (num_tasks_ < MAX_TASKS) {
    tasks_[num_tasks_].task_func = task_func;
    tasks_[num_tasks_].interval = interval;
    tasks_[num_tasks_].last_execution_time = 0;
    num_tasks_++;
  }
}

void Scheduler::run()
{
  for (;;) {
    unsigned long current_millis = millis();
    for (int i = 0; i < num_tasks_; i++) {
      if (
        current_millis - tasks_[i].last_execution_time >= tasks_[i].interval) {
        tasks_[i].last_execution_time = current_millis;
        tasks_[i].task_func();
      }
    }
    // Additional code to be executed in the main loop can go here
  }
}