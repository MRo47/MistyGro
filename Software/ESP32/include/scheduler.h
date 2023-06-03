#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <time.h>

#include "timer.h"

class Scheduler
{
public:
  Scheduler();

  void create_task(void (*task_func)(), unsigned long interval_sec);
  void run();
  void begin(long int timer_sync_interval_ms = 600000);  // 10 mins

private:
  struct TaskInfo
  {
    void (*task_func)();
    unsigned long interval;
    time_t last_execution_time;
  };

  static const int MAX_TASKS = 10;  // Maximum number of tasks
  TaskInfo tasks_[MAX_TASKS];
  int num_tasks_;
  Timer timer_;
};

#endif  // SCHEDULER_H_
