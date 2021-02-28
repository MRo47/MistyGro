#include <Arduino.h>

enum class Switch : bool
{
    ON = HIGH,
    OFF = LOW
};

// active high
class RelayAH
{
protected:
    int pin_;

public:
    RelayAH(int pin) : pin_(pin){};

    virtual void begin(Switch sw)
    {
        pinMode(pin_, OUTPUT);
        digitalWrite(pin_, bool(sw));
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

// active low
class RelayAL : RelayAH
{
public:
    void begin(Switch sw)
    {
        pinMode(pin_, OUTPUT);
        digitalWrite(pin_, !bool(sw));
    }

    void set(Switch state)
    {
        digitalWrite(pin_, !bool(state));
    }
};