#include <Arduino.h>

enum class Switch : bool
{
    ON = HIGH,
    OFF = LOW
};

class Relay
{
protected:
    int pin_;

public:
    Relay(int pin) : pin_(pin){};

    void begin()
    {
        pinMode(pin_, OUTPUT);
        digitalWrite(pin_, LOW);
    }

    virtual void set(Switch state)
    {
        digitalWrite(pin_, bool(state));
    }

    void toggle()
    {
        digitalWrite(pin_, !digitalRead(pin_)); //TODO check this
    }
};