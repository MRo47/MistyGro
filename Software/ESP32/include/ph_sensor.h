#ifndef _PH_SENSOR_H_
#define _PH_SENSOR_H_

#include <Arduino.h>
#include <EEPROM.h>

#include "adc.h"
#include "custom_eeprom.h"
#include "utility.h"

class PHSensor
{
private:
  ADC * adc_;
  const int power_pin_;   // ph sensor supply
  const size_t samples_;  // num of avg samples per reading

  PhCalib ph_calib_;
  CustomEEPROM & eeprom_;

public:
  PHSensor(int power_pin, int samples, ADC * adc);

  void begin();

  float read_voltage();

  float read_ph();

  void calibration();
};

#endif