#include <Arduino.h>

#include "ph_sensor.h"
#include "utility.h"

ADC adc;

PHSensor ph_sensor(pin::ph_enable, 10, &adc);

void setup()
{
  Serial.begin(115200);
  adc.begin(constants::adc_bus_addr, pin::adc_sda, pin::adc_scl);
  ph_sensor.begin();
  Serial.println("Enter commands as below");
  Serial.println("r - to read ph");
  Serial.println("c - to calibrate ph sensor");
}

void loop()
{
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == 'r') {
      Serial.print("Reading ph: ");
      Serial.println(ph_sensor.read_ph());
    } else if (c == 'c') {
      ph_sensor.calibration();
    } else {
      Serial.println("invalid command");
    }
  }
}
