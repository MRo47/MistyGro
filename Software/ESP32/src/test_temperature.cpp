#include <Arduino.h>
#include "temperature_sensor.h"

TemperatureSensor temp_sensor(A7);

void setup()
{
    Serial.begin(115200);
    temp_sensor.begin();
    Serial.println("Temperature sensor test");
}

void loop()
{
    Serial.print("Temperature: ");
    Serial.println(temp_sensor.read());
    delay(1000);
}