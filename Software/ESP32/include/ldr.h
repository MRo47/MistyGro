#ifndef _LDR_H_
#define _LDR_H_

#include <Arduino.h>

#include "adc.h"

/**
 * @brief Light dependent resistor wrapper
 * 
 */
class LDR
{
private:
  ADC * adc_;
  const size_t samples_;

public:
  /**
   * @brief Construct a new LDR object
   * 
   * @param samples total samples to use for voltage calculation (uses median to compute final value)
   * @param adc The adc to use to read samples
   */
  LDR(int samples, ADC * adc);

  /**
   * @brief Read voltage from ADC for LDR. Make sure ADC is initialised before calling this method
   * 
   * @return float LDR voltage at junction
   */
  float read_voltage();
};

#endif