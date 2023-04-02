#include "custom_eeprom.h"

void CustomEEPROM::begin() { EEPROM.begin(eeprom_size_); }

void CustomEEPROM::save_ph_calib(const PhCalib & ph_data)
{
  EEPROM.put(ph_addr_, ph_data);
  EEPROM.put(ph_set_addr_, constants::ph_calib_magic);
  EEPROM.commit();
}

PhCalib CustomEEPROM::get_ph_calib()
{
  PhCalib temp;
  EEPROM.get(ph_addr_, temp);
  return temp;
}

void CustomEEPROM::save_ec_calib(const float ec_calib)
{
  EEPROM.put(ec_addr_, ec_calib);
  EEPROM.put(ec_set_addr_, constants::ec_calib_magic);
  EEPROM.commit();
}

float CustomEEPROM::get_ec_calib()
{
  float temp;
  EEPROM.get(ec_addr_, temp);
  return temp;
}

bool CustomEEPROM::is_ec_calibrated()
{
  int calib;
  EEPROM.get(ec_set_addr_, calib);
  return calib == constants::ec_calib_magic;
}

bool CustomEEPROM::is_ph_calibrated()
{
  int calib;
  EEPROM.get(ph_set_addr_, calib);
  return calib == constants::ph_calib_magic;
}