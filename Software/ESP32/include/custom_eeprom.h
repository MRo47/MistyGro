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
    static const int ec_addr = ph_addr + sizeof(PhCalib);
    static const int eeprom_size = 255;
    CustomEEPROM(){};

public:
    static CustomEEPROM &getInstance()
    {
        static CustomEEPROM eeprom_obj;
        return eeprom_obj;
    }
    
    void begin();

    void savePhCalib(const PhCalib& ph_data);

    PhCalib getPhCalib();

    void saveECCalib(const float ec_calib);

    float getECCalib();
};

#endif