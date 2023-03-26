#include <Arduino.h>

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

void loop()
{
  misters.toggle();
  delay(2000);
  light.toggle();
  delay(2000);
  extra_out.toggle();
  delay(2000);
}