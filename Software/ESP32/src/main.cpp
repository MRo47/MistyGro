#include <Arduino.h>

#include "custom_eeprom.h"
#include "ec_meter.h"
#include "ph_sensor.h"
#include "relay.h"
#include "utility.h"

ADC adc;
RelayAL misters(pin::misters);
RelayAL light(pin::light);
RelayAH extra_relay(pin::extra_relay);
ECMeter ec_meter(pin::ph_enable, constants::ec_samples, &adc);
PHSensor ph_sensor(pin::ph_enable, constants::ph_samples, &adc);
CustomEEPROM & eeprom(CustomEEPROM::get_instance());

void setup()
{
  Serial.begin(115200);
  eeprom.begin();
  adc.begin(constants::adc_bus_addr, pin::adc_sda, pin::adc_scl);
  misters.begin(Switch::ON);
  light.begin(Switch::ON);
  extra_relay.begin(Switch::OFF);
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