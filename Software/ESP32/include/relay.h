#include <Arduino.h>

enum class Switch : bool
{
    ON = HIGH,
    OFF = LOW
};

// active high
class RelayAH
{
private:
    int pin_;

public:
    RelayAH(int pin) : pin_(pin){};

    void begin(Switch sw)
    {
        pinMode(pin_, OUTPUT);
        digitalWrite(pin_, bool(sw));
    }

    void set(Switch state)
    {
        digitalWrite(pin_, bool(state));
    }

    void toggle()
    {
        bool state = digitalRead(pin_);
        delay(10);
        digitalWrite(pin_, !state); //TODO check this
    }
};

// active low
class RelayAL
{
private:
    int pin_;

public:
    RelayAL(int pin) : pin_(pin){};

    void begin(Switch sw)
    {
        pinMode(pin_, OUTPUT);
        digitalWrite(pin_, !bool(sw));
    }

    void set(Switch state)
    {
        digitalWrite(pin_, !bool(state));
    }

    void toggle()
    {
        bool state = digitalRead(pin_);
        delay(10);
        digitalWrite(pin_, !state); //TODO check this
    }
};