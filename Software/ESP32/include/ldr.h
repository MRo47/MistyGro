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

  float read_voltage()
  {
    // return voltage in v
    float v[samples_] = {0.f};
    for (int i = 0; i < samples_; ++i) {
      v[i] = adc_->read_voltage(ADCChannel::ldr);
      delay(10);
    }
    return median(v, samples_);
  }
};

#endif