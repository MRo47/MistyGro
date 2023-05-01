#include <Arduino.h>

#include "custom_eeprom.h"
#include "ec_meter.h"
#include "ph_sensor.h"
#include "relay.h"
#include "temperature_sensor.h"
#include "utility.h"

CustomEEPROM & eeprom(CustomEEPROM::get_instance());
ADC adc;
TemperatureSensor temp_sensor(pin::temp_sensor_bus);
RelayAL misters(pin::misters);
RelayAL light(pin::light);
RelayAH extra_relay(pin::extra_relay);

void setup()
{
  Serial.begin(115200);
  eeprom.begin();
  adc.begin(constants::adc_bus_addr, pin::adc_sda, pin::adc_scl);
  temp_sensor.begin();
  misters.begin(Switch::ON);
  light.begin(Switch::ON);
  extra_relay.begin(Switch::OFF);
  delay(1000);
  Serial.printf("Found temperature sensors: %d", temp_sensor.device_count());
  Serial.printf("Initialisation complete");
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