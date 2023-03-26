#include <Arduino.h>

#include "custom_eeprom.h"
#include "temperature_sensor.h"

class ECMeter
{
private:
  const int ec_pin_;
  const int power_pin_;
  const size_t samples_;
  float ec_calib_;
  CustomEEPROM & eeprom_;

public:
  ECMeter(int ec_pin, int power_pin, size_t samples);

  void begin();

  float read_voltage();

  float read_tds(TemperatureSensor & temperature_sensor);

  void calibration(TemperatureSensor & temperature_sensor);
};