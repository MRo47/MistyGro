#ifndef _RELAY_H_
#define _RELAY_H_

#include <Arduino.h>

enum class Switch : bool { ON = HIGH, OFF = LOW };

class Relay
{
public:
  virtual void begin(Switch sw) = 0;

  virtual void set(Switch state) = 0;

  virtual int get_state() = 0;

  virtual void toggle() = 0;
};

// active high
class RelayAH : public Relay
{
private:
  int pin_;

public:
  RelayAH(int pin);

  void begin(Switch sw);

  void set(Switch state);

  int get_state();

  void toggle();
};

// active low
class RelayAL : public Relay
{
private:
  int pin_;

public:
  RelayAL(int pin);

  void begin(Switch sw);

  void set(Switch state);

  int get_state();

  void toggle();
};

#endif