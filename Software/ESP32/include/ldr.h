#ifndef _LDR_H_
#define _LDR_H_

#include <Arduino.h>

#include "adc.h"

class LDR
{
private:
  ADC * adc_;
  const size_t samples_;

public:
  LDR(int samples, ADC * adc);

  float read_voltage();
};

#endif