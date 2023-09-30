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

#include "temperature_sensor.h"

TemperatureSensor::TemperatureSensor(int pin) : wire_(pin), sensors_(&wire_){};

void TemperatureSensor::begin() { sensors_.begin(); }

uint8_t TemperatureSensor::device_count() { return sensors_.getDeviceCount(); }

float TemperatureSensor::read()
{
  // request temperature form 1st/only sensor
  sensors_.requestTemperaturesByIndex(0);
  // read first/only sensor
  return sensors_.getTempCByIndex(0);
}