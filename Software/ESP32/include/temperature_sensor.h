#ifndef _TEMPERATURE_SENSOR_H_
#define _TEMPERATURE_SENSOR_H_

#include <Arduino.h>
#include <DallasTemperature.h>
#include <OneWire.h>

#include "utility.h"

/**
 * @brief wrapper for Dallas one-wire temperature sensor (DS18B20)
 * 
 */
class TemperatureSensor
{
private:
  OneWire wire_;
  DallasTemperature sensors_;

public:
  /**
   * @brief Construct a new TemperatureSensor
   * 
   * @param pin one wire bus pin
   */
  TemperatureSensor(int pin);

  /**
   * @brief Initialise all one wire sensors
   * 
   */
  void begin();

  /**
   * @brief Get count of total sensors on the one wire bus
   * 
   * @return uint8_t 
   */
  uint8_t device_count();

  /**
   * @brief Read temperature as float value from sensor
   * 
   * @return float 
   */
  float read();
};

#endif