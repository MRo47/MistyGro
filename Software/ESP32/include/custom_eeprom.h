#ifndef _CUSTOM_EEPROM_H_
#define _CUSTOM_EEPROM_H_

#include <Arduino.h>
#include "EEPROM.h"
#include "utility.h"

//singleton eeprom
class CustomEEPROM
{
private:
    static const int ph_addr = 0;
    static const int eeprom_size = 255;
    CustomEEPROM(){};

public:
    static CustomEEPROM &getInstance()
    {
        static CustomEEPROM eeprom_obj;
        return eeprom_obj;
    }
    
    void begin();

    void savePhCalib(const PhData& ph_data);

    PhData getPhCalib();
};

#endif