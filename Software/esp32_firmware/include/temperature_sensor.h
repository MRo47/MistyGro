/*
 * Copyright 2023 Myron Rodrigues
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _TEMPERATURE_SENSOR_H_
#define _TEMPERATURE_SENSOR_H_

#include <Arduino.h>
#include <DallasTemperature.h>
#include <OneWire.h>

#include "utility.h"

/**
 * @brief wrapper for Dallas one-wire temperature sensor (DS18B20)
 * 
 */
class TemperatureSensor
{
private:
  OneWire wire_;
  DallasTemperature sensors_;

public:
  /**
   * @brief Construct a new TemperatureSensor
   * 
   * @param pin one wire bus pin
   */
  TemperatureSensor(int pin);

  /**
   * @brief Initialise all one wire sensors
   * 
   */
  void begin();

  /**
   * @brief Get count of total sensors on the one wire bus
   * 
   * @return uint8_t 
   */
  uint8_t device_count();

  /**
   * @brief Read temperature as float value from sensor
   * 
   * @return float 
   */
  float read();
};

#endif