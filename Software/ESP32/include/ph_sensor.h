#ifndef _PH_SENSOR_H_
#define _PH_SENSOR_H_

#include <Arduino.h>
#include "utility.h"
#include <EEPROM.h>
#include "custom_eeprom.h"

class PHSensor
{
private:
    int temp_pin_; //temperature input
    int ph_pin_; //ph input
    int power_pin_; //ph sensor supply

    float ph_;
    float voltage_;
    float temp_;
    // PhData ph_calib_data_;
    float m_; //slope
    float c_; //intercept
    CustomEEPROM& eeprom;

public:
    PHSensor(int temp_pin, int ph_pin, int power_pin);

    void begin();

    float read();

    void calibration();

    // void calibration(float voltage, float temperature)
    // {
    //     // EEPROM.put
    // }

    // float read() //read pH
    // {
    //     // power on
    //     digitalWrite(power_, HIGH);
    //     float sum = 0.0;
    //     for(int i=0; i<samples_; ++i)
    //     {
    //         sum += analogRead(p0_);
    //         delay(10);
    //     }
    //     // power on
    //     digitalWrite(power_, LOW);
    //     return 7 + 
    //         ((1.65 - (3.3 * samples_ / (constants::adc_res * sum))) / 0.18);
    // }

    //add calib

};

#endif