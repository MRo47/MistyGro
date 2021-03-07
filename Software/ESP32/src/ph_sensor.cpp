#include "ph_sensor.h"

PHSensor::PHSensor(int temp_pin, int ph_pin, int power_pin)
    : temp_pin_(temp_pin), ph_pin_(ph_pin), power_pin_(power_pin),
        ph_(7.0),
        voltage_(1500.0),
        temp_(25.0),
        ph_calib_data_{2032.44, //buffer soln 4.0 at 25C
                        1500.0}{}  //buffer soln 7.0 at 25C

void PHSensor::begin()
{
    pinMode(temp_pin_, INPUT);
    pinMode(ph_pin_, INPUT);
    pinMode(power_pin_, OUTPUT);

    EEPROM.get(constants::ph_data_add, ph_calib_data_);
    Serial.println("data: " + String(ph_calib_data_.ph4_v) +
                    " " + String(ph_calib_data_.ph7_v));

    
}