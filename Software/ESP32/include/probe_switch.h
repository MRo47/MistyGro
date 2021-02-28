#include <Arduino.h>

class ProbeSwitch
{
private:
    int pin_a_;
    int pin_b_;
    uint16_t a_on_time_;
    uint16_t b_on_time_;
    uint16_t off_time;

public:
    ProbeSwitch(int pin_a, int pin_b,
                uint16_t a_on_time, uint16_t b_on_time, uint16_t off_time)
    :   pin_a_(pin_a),
        pin_b_(pin_b),
        a_on_time_(a_on_time),
        b_on_time_(b_on_time),
        off_time(off_time){};

    

    
};