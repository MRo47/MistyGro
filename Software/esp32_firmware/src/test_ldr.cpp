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

#include "ldr.h"
#include "utility.h"

ADC adc;
LDR ldr(10, &adc);

void setup()
{
  Serial.begin(115200);
  adc.begin(constants::adc_bus_addr, pin::adc_sda, pin::adc_scl);
  Serial.println("LDR test/calib");
}

void loop()
{
  if (Serial.available() > 0) {
    Serial.print("Reading LDR voltage: ");
    Serial.println(ldr.read_voltage());
    delay(1000);
  }
}