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

#include "adc.h"

#include "utility.h"

ADC::ADC() : i2c_bus_(constants::adc_bus_num) {}

void ADC::begin(int addr, int sda_pin, int scl_pin)
{
  i2c_bus_.begin(sda_pin, scl_pin);
  ads_.begin(addr, &i2c_bus_);
  ads_.setGain(
    GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads_.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads_.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads_.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads_.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads_.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
}

int16_t ADC::read(ADCChannel ch)
{
  return ads_.readADC_SingleEnded((int16_t)ch);
}

float ADC::read_voltage(ADCChannel ch) { return ads_.computeVolts(read(ch)); }
