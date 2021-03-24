#include <Arduino.h>
#include "ph_sensor.h"

PHSensor ph_sensor(A3, 5, 10);

void test_setup()
{
    Serial.begin(115200);
    ph_sensor.begin();
    Serial.println("Enter commands as below");
    Serial.println("r - to read ph");
    Serial.println("c - to calibrate ph sensor");
}

void test_run()
{
    if (Serial.available() > 0)
    {
        char c = Serial.read();
        if(c == 'r')
        {
            Serial.print("Reading ph: ");
            Serial.println(ph_sensor.read_ph());
        }
        else if(c == 'c')
        {
            ph_sensor.calibration();
        }
        else
        {
            Serial.println("invalid command");
        }
    }
}

