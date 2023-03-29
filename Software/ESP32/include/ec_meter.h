#include <Arduino.h>

#include "adc.h"
#include "custom_eeprom.h"
#include "utility.h"

class ECMeter
{
private:
  ADC * adc_;
  const int power_pin_;
  const size_t samples_;
  float ec_calib_;
  CustomEEPROM & eeprom_;

public:
  ECMeter(int power_pin, int samples, ADC * adc);

  void begin();

  float read_voltage();

  float read_tds(float temperature_c = 25.f);

  void calibration(float temperature_c);
};