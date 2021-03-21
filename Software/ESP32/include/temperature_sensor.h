#include <Arduino.h>

class TemperatureSensor
{
private:
    const int pin_;
public:
    TemperatureSensor(int pin);

    float read();
};