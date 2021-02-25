#include <Arduino.h>
#include "relay.h"

// Active high device
class ExtraOut : public Relay
{
public:
    void set(Switch state)
    {
        digitalWrite(pin_, bool(state));
    }
};