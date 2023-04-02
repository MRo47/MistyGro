#ifndef _LDR_H_
#define _LDR_H_

#include <Arduino.h>

#include "adc.h"
#include "utility.h"

class LDR
{
private:
  ADC * adc_;
  const size_t samples_;

public:
  LDR(int samples, ADC * adc) : samples_(samples), adc_(adc) {}

  // void begin();

  float read_voltage()
  {
    // return voltage in v
    float v = 0.f;
    for (int i = 0; i < samples_; ++i) {
      v += adc_->read_voltage(ADCChannel::ldr);
      delay(10);
    }
    return v / (float)samples_;
  }

  // float read_tds(float temperature_c = 25.f);

  // void calibration(float temperature_c);
};

#endif