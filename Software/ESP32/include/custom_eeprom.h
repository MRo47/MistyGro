#ifndef _CUSTOM_EEPROM_H_
#define _CUSTOM_EEPROM_H_

#include <Arduino.h>

#include "EEPROM.h"
#include "utility.h"

// singleton eeprom
class CustomEEPROM
{
private:
  static const int ph_addr_ = 0;
  static const int ec_addr_ = ph_addr_ + sizeof(PhCalib);
  static const int eeprom_size_ = 255;
  CustomEEPROM(){};

public:
  static CustomEEPROM & get_instance()
  {
    static CustomEEPROM eeprom_obj;
    return eeprom_obj;
  }

  void begin();

  void save_ph_calib(const PhCalib & ph_data);

  PhCalib get_ph_calib();

  void save_ec_calib(const float ec_calib);

  float get_ec_calib();
};

#endif