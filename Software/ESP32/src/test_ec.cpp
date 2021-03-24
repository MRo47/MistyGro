#include <Arduino.h>
#include "ec_meter.h"
#include "temperature_sensor.h"

ECMeter ec_meter(A0, 17, 10);
TemperatureSensor temp_sensor(A7);

void test_setup()
{
    Serial.begin(115200);
    ec_meter.begin();
    temp_sensor.begin();
    Serial.println("EC meter test, enter commands as below");
    Serial.println("r - to read TDS");
    Serial.println("c - to calibrate EC meter");
}

void test_run()
{
    if (Serial.available() > 0)
    {
        char c = Serial.read();
        if (c == 'r')
        {
            Serial.print("Reading TDS: ");
            Serial.println(ec_meter.read_tds(temp_sensor));
        }
        else if (c == 'c')
        {
            ec_meter.calibration(temp_sensor);
        }
        else
        {
            Serial.println("invalid command");
        }
    }
}
