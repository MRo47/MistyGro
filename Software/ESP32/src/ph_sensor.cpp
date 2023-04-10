#include "ph_sensor.h"

PHSensor::PHSensor(int power_pin, int samples, ADC * adc)
: adc_(adc),
  power_pin_(power_pin),
  samples_(samples),
  eeprom_(CustomEEPROM::get_instance())
{
}

void PHSensor::begin()
{
  eeprom_.begin();
  pinMode(power_pin_, OUTPUT);

  PhCalib temp_data = eeprom_.get_ph_calib();

  if (!eeprom_.is_ph_calibrated()) {
    temp_data = constants::default_ph_data;
    Serial.println("Saving pH Calib");
    eeprom_.save_ph_calib(temp_data);
  }
  Serial.println(
    "ph_calib: slope, intercept: " + String(temp_data.slope) + " " +
    String(temp_data.intercept));
  ph_calib_ = temp_data;
}

float PHSensor::read_voltage()
{
  // return voltage in mv
  float v[samples_] = {0.f};
  for (int i = 0; i < samples_; ++i) {
    v[i] = adc_->read_voltage(ADCChannel::ph);
    delay(10);
  }
  return median(v, samples_);
}

float PHSensor::read_ph()
{
  // switch on
  digitalWrite(power_pin_, HIGH);
  delay(3000);

  float v = read_voltage();
  Serial.println(v, 5);
  // switch off
  digitalWrite(power_pin_, LOW);

  return ph_calib_.intercept + ph_calib_.slope * v;
}

bool calib_timed_out(uint64_t start_time)
{
  return millis() - start_time >= constants::ph_calib_timeout;
}

void print_calib_msg()
{
  Serial.println(
    "Dip the ph sensor in acid and neutral solution "
    "one at a time and enter the solution ph using the "
    "following commands without <> then press enter");
  Serial.println("a - to read acid buffer values");
  Serial.println("n - to read neutral buffer values");
  Serial.println("c - to confirm values");
  Serial.println("e - to abort calibration");
}

void PHSensor::calibration()
{
  Serial.println("Entered ph calibartion mode");
  print_calib_msg();

  PhCalib ph_calib;

  uint64_t start_time = millis();

  char cmd = '@';  // init value
  float sa_ph, sn_ph, sa_v, sn_v;

  while (!calib_timed_out(start_time)) {
    if (Serial.available()) {
      cmd = Serial.read();

      if (cmd == 'a') {
        Serial.println("Enter acid buffer ph");
        while (!Serial.available()) {
          if (calib_timed_out(start_time)) {
            Serial.println("Calibration timed out, internal values unchanged");
            return;
          }
          delay(100);
        }
        sa_ph = Serial.parseFloat();
        Serial.printf("Read acid buffer ph: %f\n", sa_ph);
        sa_v = read_voltage();
        Serial.printf("Read acid buffer voltage: %f\n", sa_v);
        print_calib_msg();
        start_time = millis();  // reset timer
      } else if (cmd == 'n') {
        Serial.println("Enter neutral buffer ph");
        while (!Serial.available()) {
          if (calib_timed_out(start_time)) {
            Serial.println("Calibration timed out, internal values unchanged");
            return;
          }
          delay(100);
        }
        sn_ph = Serial.parseFloat();
        Serial.printf("Read neutral buffer ph: %f\n", sn_ph);
        sn_v = read_voltage();
        Serial.printf("Read neutral buffer voltage: %f\n", sn_v);
        print_calib_msg();
        start_time = millis();  // reset timer
      } else if (cmd == 'c') {
        ph_calib.slope = (sn_ph - sa_ph) / (sn_v - sa_v);
        if (ph_calib.slope > 0) {
          Serial.println(
            "ph calib failed, not saving calib: Got positive slope");
          return;
        }
        ph_calib.intercept = sn_ph - ph_calib.slope * sn_v;
        eeprom_.save_ph_calib(ph_calib);
        ph_calib_ = ph_calib;  // reset local ph calib
        Serial.println("Calibration successful");
        return;
      } else if (cmd == 'e')  // exit
      {
        Serial.println("Aborted calibration");
        return;
      }
    }
    delay(100);
  }

  Serial.println("Calibration timed out, internal values unchanged");
}
