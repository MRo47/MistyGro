#include <Arduino.h>
#include "utility.h"

class PHSensor
{
private:
    int t0_; //temperature input
    int d0_; //digital input
    int p0_; //ph input
    int power_; //ph sensor supply
    int samples_; //output is avg of samples
    int calib_m_; //calibration value
public:
    PHSensor(int t0, int d0, int p0, int power, int samples)
    : t0_(t0), d0_(d0), p0_(p0), power_(power), samples_(samples)
    {
        pinMode(t0_, INPUT);
        pinMode(d0_, INPUT);
        pinMode(p0_, INPUT);
        pinMode(power_, OUTPUT);
    }

    float read() //read pH
    {
        float sum = 0.0;
        for(int i=0; i<samples_; ++i)
        {
            sum += analogRead(p0_);
            delay(10);
        }
        return 7 + 
            ((1.65 - (3.3 * samples_ / (constants::adc_res * sum))) / 0.18);
    }

    //add calib

};