#ifndef _TEMPERATURE_SENSOR_H_
#define _TEMPERATURE_SENSOR_H_

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "utility.h"


class TemperatureSensor
{
private:
    const int pin_;
    OneWire wire_;
    DallasTemperature sensors_;

public:
    TemperatureSensor(int pin);

    void setup();

    float read();
};

#endif