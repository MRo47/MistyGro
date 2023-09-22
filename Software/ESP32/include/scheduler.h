// Partly created with chat GPT 3.5

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <time.h>

#include "timer.h"

/**
 * @brief A scheduler for running tasks on the controller, minimum time between events is 1 second
 * based off the ntc timer. Also depends how slow is the loop function. 
 * 
 * Maximum 10 tasks can be added, increase in the header file (MAX_TASKS) if required 
 * but beware of exhausting the heap
 */
class Scheduler
{
public:
  Scheduler();

  /**
   * @brief Create a task
   * 
   * @param task_func a task function that takes no input and has void output
   * @param interval_sec 
   */
  void create_task(void (*task_func)(), unsigned long interval_sec);

  /**
   * @brief This needs to be run in the loop function continuously. Best practice is
   * to have a loop function that only runs the run() method of this scheduler.
   */
  void run();

  /**
   * @brief initialise timer
   * 
   * @param timer_sync_interval_ms time interval in milliseconds to sync the internal ntc clock
   */
  void begin(long int timer_sync_interval_ms = 600000);  // 10 mins

private:

  /**
   * @brief Task info which stores info on a task to be run
   * 
   */
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
