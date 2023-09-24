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
