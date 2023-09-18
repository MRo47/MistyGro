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

  void begin(int addr, int sda_pin, int scl_pin);

  int16_t read(ADCChannel ch);

  float read_voltage(ADCChannel ch);
};

#endif