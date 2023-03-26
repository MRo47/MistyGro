#include <Arduino.h>

#include "custom_eeprom.h"
#include "ph_sensor.h"
#include "relay.h"

RelayAL misters(12);
RelayAL light(14);
RelayAH extra_out(27);
PHSensor ph_sensor(1, 2, 3);
CustomEEPROM & eeprom(CustomEEPROM::get_instance());

void setup()
{
  Serial.begin(115200);
  eeprom.begin();
  misters.begin(Switch::ON);
  light.begin(Switch::ON);
  extra_out.begin(Switch::OFF);
  ph_sensor.begin();
  delay(1000);
}

void loop()
{
  // misters.toggle();
  // delay(2000);
  // light.toggle();
  // delay(2000);
  // extra_out.toggle();
  // delay(2000);
}