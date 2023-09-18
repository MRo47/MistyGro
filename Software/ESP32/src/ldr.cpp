#include "ldr.h"

#include "utility.h"

LDR::LDR(int samples, ADC * adc) : samples_(samples), adc_(adc) {}

float LDR::read_voltage()
{
  // return voltage in v
  float v[samples_] = {0.f};
  for (int i = 0; i < samples_; ++i) {
    v[i] = adc_->read_voltage(ADCChannel::ldr);
    delay(10);
  }
  return median(v, samples_);
}
