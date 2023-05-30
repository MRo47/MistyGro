#ifndef SCHEDULER_H_
#define SCHEDULER_H_

class Scheduler
{
public:
  Scheduler();

  void create_task(void (*task_func)(), unsigned long interval);
  void run();

private:
  struct TaskInfo
  {
    void (*task_func)();
    unsigned long interval;
    unsigned long last_execution_time;
  };

  static const int MAX_TASKS = 10;  // Maximum number of tasks
  TaskInfo tasks_[MAX_TASKS];
  int num_tasks_;
};

#endif  // SCHEDULER_H_
