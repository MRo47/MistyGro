#include <Arduino.h>
#include "relay.h"

// Active low device
class Light : public Relay
{
public:
    void set(Switch state)
    {
        digitalWrite(pin_, !bool(state));
    }
};