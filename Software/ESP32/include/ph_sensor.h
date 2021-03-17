#ifndef _PH_SENSOR_H_
#define _PH_SENSOR_H_

#include <Arduino.h>
#include "utility.h"
#include <EEPROM.h>
#include "custom_eeprom.h"

class PHSensor
{
private:
    const int temp_pin_; //temperature input
    const int ph_pin_; //ph input
    const int power_pin_; //ph sensor supply
    const size_t samples_; //num of avg samples per reading

    PhCalib ph_calib_;
    CustomEEPROM& eeprom;

public:
    PHSensor(int temp_pin, int ph_pin, int power_pin, size_t samples);

    void begin();

    float read_voltage();

    float read_ph();

    void calibration();

};

#endif