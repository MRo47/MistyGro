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