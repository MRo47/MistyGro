#include "ph_sensor.h"

PHSensor::PHSensor(int ph_pin, int power_pin, size_t samples)
: ph_pin_(ph_pin),
  power_pin_(power_pin),
  samples_(samples),
  eeprom_(CustomEEPROM::get_instance())
{
}

void PHSensor::begin()
{
  pinMode(ph_pin_, INPUT);
  pinMode(power_pin_, OUTPUT);

  PhCalib temp_data = eeprom_.get_ph_calib();

  if (isnan(temp_data.acid) || isnan(temp_data.neutral)) {
    temp_data = constants::default_ph_data;
    Serial.println("Saving pH Calib");
    eeprom_.save_ph_calib(temp_data);
  }
  Serial.println(
    "ph_data: acid, neutral: " + String(temp_data.acid) + " " +
    String(temp_data.neutral));
  ph_calib_ = temp_data;
}

float PHSensor::read_voltage()
{
  // switch on
  digitalWrite(power_pin_, HIGH);
  // return voltage in mv
  float v = 0.f;
  for (int i = 0; i < samples_; ++i)
    v += analogRead(ph_pin_) / constants::adc_res * constants::adc_ref_v;

  // switch off
  digitalWrite(power_pin_, LOW);
  return v / samples_;
}

float PHSensor::read_ph()
{
  float v = read_voltage();
  if (v > ph_calib_.neutral)  // high voltage return acid calib value
    return 7.0 -
           3.0 / (ph_calib_.acid - ph_calib_.neutral) * (v - ph_calib_.neutral);
  else
    return 7.0 -
           3.0 / (ph_calib_.neutral - ph_calib_.base) * (v - ph_calib_.neutral);
}

void PHSensor::calibration()
{
  Serial.println("Entered ph calibartion mode");
  Serial.println(
    "Dip the ph sensor in an acidic neutral and basic solution "
    "one at a time and enter the solution ph using the "
    "following commands without <> then press enter");
  Serial.println("a - to calibrate acid solution");
  Serial.println("n - to calibrate neutral solution");
  Serial.println("b - to calibrate a basic solution");
  Serial.println("c - to confirm values");
  Serial.println("e - to abort calibration");

  PhCalib read_ph;

  long start_time = millis();

  char cmd = '@';  // init value

  while (millis() - start_time >= constants::ph_calib_timeout) {
    if (Serial.available() > 0) {
      cmd = Serial.read();

      if (cmd == 'a')  // acid value
      {
        read_ph.acid = read_voltage();
        Serial.printf("Read acid voltage: %f", read_ph.acid);
        start_time = millis();  // reset timer
      } else if (cmd == 'n')    // neutral value
      {
        read_ph.neutral = read_voltage();
        Serial.printf("Read neutral voltage: %f", read_ph.neutral);
        start_time = millis();  // reset timer
      } else if (cmd == 'b')    // base value
      {
        read_ph.base = read_voltage();
        Serial.printf("Read base voltage: %f", read_ph.base);
        start_time = millis();  // reset timer
      } else if (cmd == 'c')    // confirm ph values
      {
        if (
          read_ph.acid > constants::ph_low_limit.acid &&
          read_ph.acid < constants::ph_high_limit.acid &&
          read_ph.neutral > constants::ph_low_limit.neutral &&
          read_ph.neutral < constants::ph_high_limit.neutral &&
          read_ph.base > constants::ph_low_limit.base &&
          read_ph.base < constants::ph_high_limit.base) {
          Serial.printf("Neutral voltage calibrated: %f\n", read_ph.neutral);
          Serial.printf("Acid volatge calibrated: %f\n", read_ph.acid);
          eeprom_.save_ph_calib(read_ph);
          ph_calib_ = read_ph;  // reset local ph calib
          Serial.println("Calibration successful");
          return;
        } else
          Serial.println("Failed calibration");
        return;
      } else if (cmd == 'e')  // exit
      {
        Serial.println("Aborted calibration");
        return;
      }
    }
  }

  Serial.println("Calibration timed out, internal values unchanged");
}
