#include "temperature_sensor.h"

TemperatureSensor::TemperatureSensor(int pin) 
: pin_(pin), wire_(constants::temp_sensor_bus),
  sensors_(&wire_){};

void TemperatureSensor::setup()
{
    sensors_.begin();
}

float TemperatureSensor::read()
{
    //request temperature form 1st/only sensor
    sensors_.requestTemperaturesByIndex(0);
    //read first/only sensor
    return sensors_.getTempCByIndex(0); 
}