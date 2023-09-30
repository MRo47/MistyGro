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

#ifndef _LDR_H_
#define _LDR_H_

#include <Arduino.h>

#include "adc.h"

/**
 * @brief Light dependent resistor wrapper
 * 
 */
class LDR
{
private:
  ADC * adc_;
  const size_t samples_;

public:
  /**
   * @brief Construct a new LDR object
   * 
   * @param samples total samples to use for voltage calculation (uses median to compute final value)
   * @param adc The adc to use to read samples
   */
  LDR(int samples, ADC * adc);

  /**
   * @brief Read voltage from ADC for LDR. Make sure ADC is initialised before calling this method
   * 
   * @return float LDR voltage at junction
   */
  float read_voltage();
};

#endif