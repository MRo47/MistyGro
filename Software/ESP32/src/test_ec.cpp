#include <Arduino.h>

#include "adc.h"
#include "custom_eeprom.h"
#include "ec_meter.h"
#include "temperature_sensor.h"
#include "utility.h"

CustomEEPROM ee = CustomEEPROM::get_instance();
ADC adc;
ECMeter ec_meter(pin::ec_enable, constants::ec_samples, &adc);
// TemperatureSensor temp_sensor(A4);

void setup()
{
  Serial.begin(115200);
  ee.begin();
  adc.begin(constants::adc_bus_addr, pin::adc_sda, pin::adc_scl);
  ec_meter.begin();
  // temp_sensor.begin();
  Serial.println("EC meter test, enter commands as below");
  Serial.println("r - to read TDS");
  Serial.println("c - to calibrate EC meter");
}

void loop()
{
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == 'r') {
      Serial.print("Reading TDS: ");
      Serial.println(ec_meter.read_tds(20));
    } else if (c == 'c') {
      // ec_meter.calibration(temp_sensor);
    } else {
      Serial.println("invalid command");
    }
  }
}
