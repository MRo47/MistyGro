#include <Arduino.h>

class ECMeter
{
private:
    int pin_;
    int power_;
    size_t samples_;

public:
    ECMeter(int pin, int power, size_t samples)
    : pin_(pin), power_(power), samples_(samples)
    {
        pinMode(pin_, INPUT);
        pinMode(power_, OUTPUT);
    };

    float read() //read EC
    {
        // power on
        digitalWrite(power_, HIGH);
        float sum = 0.0;
        for(int i=0; i<samples_; ++i)
        {
            sum += analogRead(pin_);
        }
        // power off
        digitalWrite(power_, LOW);
        return sum / samples_;
    }
};