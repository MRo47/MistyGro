#include "ph_sensor.h"

PHSensor::PHSensor(int temp_pin, int ph_pin, int power_pin)
    : temp_pin_(temp_pin), ph_pin_(ph_pin), power_pin_(power_pin),
      eeprom(CustomEEPROM::getInstance()){}

void PHSensor::begin()
{
    pinMode(temp_pin_, INPUT);
    pinMode(ph_pin_, INPUT);
    pinMode(power_pin_, OUTPUT);

    PhCalib temp_data = eeprom.getPhCalib();

    if (isnan (temp_data.acid)
        || isnan(temp_data.neutral))
    {
        temp_data = constants::default_ph_data;
        Serial.println("saving");
        eeprom.savePhCalib(temp_data);
    }
    Serial.println("ph_data: acid, neutral: " + String(temp_data.acid) +
                   " " + String(temp_data.neutral));
    ph_calib_ = temp_data;
}

float PHSensor::read_voltage()
{
    //return voltage in mv
    float v = 0.f;
    for(int i = 0; i < constants::sample_size; ++i)
        v += analogRead(ph_pin_) / constants::adc_res * constants::adc_ref_v;

    return v / constants::sample_size;
}

float PHSensor::read_ph()
{
    float v = read_voltage();
    if (v > ph_calib_.neutral) //high voltage return acid calib value
        return 7.0 - 3.0 / (ph_calib_.acid - ph_calib_.neutral) * 
                (v - ph_calib_.neutral);
    else
        return 7.0 - 3.0 / (ph_calib_.neutral - ph_calib_.base) *
                (v - ph_calib_.neutral);
}

void PHSensor::calibration()
{
    Serial.println("Entered ph calibartion mode");
    Serial.println("Dip the ph sensor in an acidic and neutral solution one at " 
                    "a time and enter the solution ph using the following "
                    "commands without <>");
    Serial.println("a - to calibrate acid solution");
    Serial.println("n - to calibrate neutral solution");
    Serial.println("b - to calibrate a basic solution");
    Serial.println("c - to confirm values");
    Serial.println("e - to abort calibration");

    PhCalib read_ph;

    long start_time = millis();

    char cmd = '@'; //init value

    while(millis() - start_time >= constants::ph_calib_timeout)
    {
        if (Serial.available() > 0)
        {
            cmd = Serial.read();

            if(cmd == 'a') //acid value
            {
                read_ph.acid = read_voltage();
                start_time = millis(); //reset timer
            }
            else if(cmd == 'n') //neutral value
            {
                read_ph.neutral = read_voltage();
                start_time = millis(); //reset timer
            }
            else if(cmd == 'b') //base value
            {
                read_ph.base = read_voltage();
                start_time = millis(); //reset timer
            }
            else if(cmd == 'c') //confirm ph values
            {
                if(read_ph.acid > constants::ph_low_limit.acid &&
                   read_ph.acid < constants::ph_high_limit.acid &&
                   read_ph.neutral > constants::ph_low_limit.neutral &&
                   read_ph.neutral < constants::ph_high_limit.neutral)
                {
                    Serial.println("Neutral voltage calibrated: ", 
                                   read_ph.neutral);
                    Serial.println("Acid volatge calibrated: ",
                                   read_ph.acid);
                    eeprom.savePhCalib(read_ph);
                    setSlopeIntercept(read_ph);
                    Serial.println("Calibration successful");
                }
                else
                    Serial.println("Failed calibration");
                break;
            }
            else if(cmd == 'e') //exit
                break;
            
        }
    }

}
