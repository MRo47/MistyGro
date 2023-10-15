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

#include "relay.h"

RelayAH::RelayAH(int pin) : pin_(pin){};

void RelayAH::begin(Switch sw)
{
  pinMode(pin_, OUTPUT);
  digitalWrite(pin_, bool(sw));
}

void RelayAH::set(Switch state) { digitalWrite(pin_, bool(state)); }

int RelayAH::get_state() { return digitalRead(pin_); }

void RelayAH::toggle()
{
  bool state = digitalRead(pin_);
  delay(10);
  digitalWrite(pin_, !state);  // TODO check this
}

RelayAL::RelayAL(int pin) : pin_(pin){};

void RelayAL::begin(Switch sw)
{
  pinMode(pin_, OUTPUT);
  digitalWrite(pin_, !bool(sw));
}

void RelayAL::set(Switch state) { digitalWrite(pin_, !bool(state)); }

int RelayAL::get_state()
{
  return !(bool)digitalRead(pin_);  // negate the state as this is an active low
}

void RelayAL::toggle()
{
  bool state = digitalRead(pin_);
  delay(10);
  digitalWrite(pin_, !state);
}
