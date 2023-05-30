#include <Arduino.h>

#include "scheduler.h"

Scheduler scheduler;

void task1() { Serial.println("Task 1"); }

void task2() { Serial.println("Task 2"); }

void setup()
{
  Serial.begin(115200);
  scheduler.create_task(task1, 2000);
  scheduler.create_task(task2, 5000);
}

void loop() { scheduler.run(); }