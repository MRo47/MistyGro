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

#ifndef _RELAY_H_
#define _RELAY_H_

#include <Arduino.h>

enum class Switch : bool { ON = HIGH, OFF = LOW };

/**
 * @brief Abstract relay class
 * 
 */
class Relay
{
public:
  virtual void begin(Switch sw) = 0;

  virtual void set(Switch state) = 0;

  virtual int get_state() = 0;

  virtual void toggle() = 0;
};

/**
 * @brief Active high relay
 * 
 */
class RelayAH : public Relay
{
private:
  int pin_;

public:
  /**
   * @brief Construct a new active high relay
   * 
   * @param pin pin number where relay is wired
   */
  RelayAH(int pin);

  /**
   * @brief initialise pin and set initial relay state
   * 
   * @param sw 
   */
  void begin(Switch sw);

  /**
   * @brief set relay state
   * 
   * @param state On to switch on, the state is managed internally
   */
  void set(Switch state);

  /**
   * @brief Get the current state
   * 
   * @return int 1 if ON
   */
  int get_state();

  /**
   * @brief Toggle the relay
   * 
   */
  void toggle();
};

// active low
class RelayAL : public Relay
{
private:
  int pin_;

public:
  /**
   * @brief Construct a new active low relay
   * 
   * @param pin pin number where relay is wired
   */
  RelayAL(int pin);

  /**
   * @brief initialise pin and set initial relay state
   * 
   * @param sw 
   */
  void begin(Switch sw);

  /**
   * @brief set relay state
   * 
   * @param state On to switch on, the state is managed internally
   */
  void set(Switch state);

  /**
   * @brief Get the current state
   * 
   * @return int 1 if ON
   */
  int get_state();

  /**
   * @brief Toggle the relay
   * 
   */
  void toggle();
};

#endif