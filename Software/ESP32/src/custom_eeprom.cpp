#include "custom_eeprom.h"

void CustomEEPROM::begin()
{
    EEPROM.begin(eeprom_size);
}

void CustomEEPROM::savePhCalib(const PhCalib &ph_data)
{
    EEPROM.put(ph_addr, ph_data);
    EEPROM.commit();
}

PhCalib CustomEEPROM::getPhCalib()
{
    PhCalib temp;
    EEPROM.get(ph_addr, temp);
    return temp;
}

void CustomEEPROM::saveECCalib(const float ec_calib)
{
    //offset by ph calib size
    EEPROM.put(ec_addr, ec_calib);
    EEPROM.commit();
}

float CustomEEPROM::getECCalib()
{
    float temp;
    EEPROM.get(ec_addr, temp);
    return temp;
}