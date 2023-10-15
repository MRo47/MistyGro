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

#include "temperature_sensor.h"

TemperatureSensor temp_sensor(pin::temp_sensor_bus);

void setup()
{
  Serial.begin(115200);
  temp_sensor.begin();
  Serial.println("Temperature sensor test");
}

void loop()
{
  Serial.print("Device count: ");
  Serial.println(temp_sensor.device_count());
  Serial.print("Temperature: ");
  Serial.println(temp_sensor.read());
  delay(1000);
}