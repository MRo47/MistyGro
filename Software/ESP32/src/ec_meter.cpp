#include "ec_meter.h"

ECMeter::ECMeter(int power_pin, int samples, ADC * adc)
: adc_(adc),
  power_pin_(power_pin),
  samples_(samples),
  eeprom_(CustomEEPROM::get_instance())
{
}

void ECMeter::begin()
{
  pinMode(power_pin_, OUTPUT);

  float temp_k = eeprom_.get_ec_calib();

  if (!eeprom_.is_ec_calibrated()) {
    temp_k = constants::default_ec_calib;
    Serial.println("Saving EC Calib");
    eeprom_.save_ec_calib(temp_k);
  }
  Serial.println("EC calib: " + String(temp_k));
  ec_calib_ = temp_k;
}

float ECMeter::read_voltage()
{
  // return voltage in v
  float v = 0.f;
  for (int i = 0; i < samples_; ++i) v += adc_->read_voltage(ADCChannel::ec);
  return v / (float)samples_;
}

float ECMeter::read_tds(TemperatureSensor & temperature_sensor)
{
  // switch on
  digitalWrite(power_pin_, HIGH);
  delay(100);
  float v = read_voltage();
  // switch off
  digitalWrite(power_pin_, LOW);

  float ec = (133.42 * v * v * v - 255.86 * v * v + 857.39 * v) * ec_calib_;

  float ec_at25 = ec / (1.0 + 0.02 * (temperature_sensor.read() - 25.0));
  return ec_at25 * constants::tds_factor;
}

float ECMeter::read_tds(float temperature_c)
{
  // switch on
  digitalWrite(power_pin_, HIGH);
  delay(200);
  float v = read_voltage();
  // switch off
  digitalWrite(power_pin_, LOW);

  float ec = (133.42 * v * v * v - 255.86 * v * v + 857.39 * v) * ec_calib_;

  float ec_at25 = ec / (1.0 + 0.02 * (temperature_c - 25.0));
  return ec_at25 * constants::tds_factor;
}

void ECMeter::calibration(TemperatureSensor & temperature_sensor)
{
  Serial.println("Entered EC Meter calibration mode");
  Serial.println(
    "Dip the sensor in a standard buffer solution: "
    "707ppm(1413us/cm)@25^c, then enter the following commands");
  Serial.println("p<ppm of solution> - to calibrate");
  Serial.println("c - to confirm values");
  Serial.println("e - to abort calibration");

  long start_time = millis();

  char cmd = '@';  // init value

  float raw_ec = 0;
  float temp_k = 0;

  while (millis() - start_time >= constants::ec_calib_timeout) {
    if (Serial.available() > 0) {
      cmd = Serial.read();

      if (cmd == 't')  // acid value
      {
        // read the ppm value(tds) and convrt to EC
        raw_ec = Serial.parseFloat() / constants::tds_factor;

        float v = read_voltage();

        // temperature compensation
        raw_ec = raw_ec * (1.0 + 0.02 * (temperature_sensor.read() - 25.0));

        temp_k = raw_ec / (133.42 * v * v * v - 255.86 * v * v + 857.39 * v);

        Serial.printf("New ec calib: %f", temp_k);
        start_time = millis();  // reset timer
      } else if (cmd == 'c')    // confirm ph values
      {
        if (raw_ec > 0 && raw_ec < 2000 && temp_k > 0.25 && temp_k < 4.0) {
          Serial.printf("EC calibrated: %f\n", temp_k);
          eeprom_.save_ec_calib(temp_k);
          ec_calib_ = temp_k;
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

  Serial.println("EC calibration timed out, internal values unchanged");
}