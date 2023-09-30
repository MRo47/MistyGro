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

#include <Arduino.h>

#include "scheduler.h"

Scheduler scheduler;

void task1() { Serial.println("Task 1"); }

void task2() { Serial.println("Task 2"); }

void setup()
{
  Serial.begin(115200);
  scheduler.begin(10000);
  scheduler.create_task(task1, 2);
  scheduler.create_task(task2, 5);
}

void loop() { scheduler.run(); }