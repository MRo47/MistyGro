#include "temperature_sensor.h"

TemperatureSensor::TemperatureSensor(int pin)
: pin_(pin), wire_(pin::temp_sensor_bus), sensors_(&wire_){};

void TemperatureSensor::begin() { sensors_.begin(); }

uint8_t TemperatureSensor::device_count() { return sensors_.getDeviceCount(); }

float TemperatureSensor::read()
{
  // request temperature form 1st/only sensor
  sensors_.requestTemperaturesByIndex(0);
  // read first/only sensor
  return sensors_.getTempCByIndex(0);
}