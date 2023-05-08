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