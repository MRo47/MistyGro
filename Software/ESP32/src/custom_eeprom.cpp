#include "custom_eeprom.h"

void CustomEEPROM::begin() { EEPROM.begin(eeprom_size_); }

void CustomEEPROM::save_ph_calib(const PhCalib & ph_data)
{
  EEPROM.put(ph_addr_, ph_data);
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
  // offset by ph calib size
  EEPROM.put(ec_addr_, ec_calib);
  EEPROM.commit();
}

float CustomEEPROM::get_ec_calib()
{
  float temp;
  EEPROM.get(ec_addr_, temp);
  return temp;
}