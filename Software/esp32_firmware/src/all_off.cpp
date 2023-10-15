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
#include <FirebaseESP32.h>  // if exculded complaints about SPIFFS.h header at compile

#include "relay.h"

RelayAL misters(12);
RelayAL light(14);
RelayAH extra_out(27);

void setup()
{
  misters.begin(Switch::ON);
  light.begin(Switch::ON);
  extra_out.begin(Switch::OFF);
  delay(1000);
}

void loop() {}