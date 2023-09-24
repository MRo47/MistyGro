#ifndef _ADC_H_
#define _ADC_H_

#include <Adafruit_ADS1X15.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

enum class ADCChannel { ph = 0, ec = 1, ldr = 3 };

class ADC
{
private:
  Adafruit_ADS1115 ads_;
  TwoWire i2c_bus_;

public:
  explicit ADC();

  /** initialise i2c, ADS1115 and set gain to 2/3
   * @brief 
   * 
   * @param addr ADS i2c address
   * @param sda_pin 
   * @param scl_pin 
   */
  void begin(int addr, int sda_pin, int scl_pin);

  /**
   * @brief Read ADC value from channel
   * 
   * @param ch ADC channel of ADS1115
   * @return int16_t : adc value
   */
  int16_t read(ADCChannel ch);

  /**
   * @brief Read voltage from ADC channel (computes voltage using the set fixed gain)
   * 
   * @param ch ADC channel
   * @return float : voltage
   */
  float read_voltage(ADCChannel ch);
};

#endif