#include "ph_sensor.h"

PHSensor::PHSensor(int temp_pin, int ph_pin, int power_pin)
    : temp_pin_(temp_pin), ph_pin_(ph_pin), power_pin_(power_pin),
      ph_(7.0),
      voltage_(1500.0),
      temp_(25.0),
    //   ph_calib_data_{2032.44, //buffer soln 4.0 at 25C
    //                  1500.0}, //buffer soln 7.0 at 25C
      eeprom(CustomEEPROM::getInstance()){}  

void PHSensor::begin()
{
    pinMode(temp_pin_, INPUT);
    pinMode(ph_pin_, INPUT);
    pinMode(power_pin_, OUTPUT);

    PhData temp_data = eeprom.getPhCalib();

    if (isnan (temp_data.ph4_v)
        || isnan(temp_data.ph7_v))
    {
        temp_data = {2032.44, //buffer soln 4.0 at 25C
                     constants::ph7_volt_at_25C}; //buffer soln 7.0 at 25C
        Serial.println("saving");
        eeprom.savePhCalib(temp_data);
    }
    Serial.println("ph_data: ph4_v, ph7_v: " + String(temp_data.ph4_v) +
                   " " + String(temp_data.ph7_v));

    float m_ = 3.0 / ((temp_data.ph7_v - constants::ph7_volt_at_25C) /
                         3.0 -
                     (temp_data.ph4_v - constants::ph7_volt_at_25C) / 3.0);

    float c_ = 7.0 - m_ * (temp_data.ph7_v - constants::ph7_volt_at_25C) / 3.0;
}

float PHSensor::read()
{
    return m_ * (voltage_ - constants::ph7_volt_at_25C) / 3.0 + c_; //y = mx + c;
}

