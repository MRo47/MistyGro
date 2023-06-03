#include <Arduino.h>

#include "custom_eeprom.h"
#include "ec_meter.h"
#include "firebase_logger.h"
#include "ldr.h"
#include "ph_sensor.h"
#include "relay.h"
#include "scheduler.h"
#include "secrets.h"
#include "temperature_sensor.h"
#include "timer.h"
#include "utility.h"

CustomEEPROM & eeprom(CustomEEPROM::get_instance());
ADC adc;
LDR ldr(10, &adc);
TemperatureSensor temp_sensor(pin::temp_sensor_bus);
RelayAL misters(pin::misters);
RelayAL light(pin::light);
RelayAH extra_relay(pin::extra_relay);
Timer timer;
FireLogger flog;
Scheduler scheduler;

float LDR_thresh_v = 2.5;

void toggle_misters()
{
  misters.toggle();
  // TODO: set on DB /day_ts/misters/ts : value
  // flog.set_bool("/day");
}

void check_temperature()
{
  float temp = temp_sensor.read();
  // TODO: set on DB /day_ts/temperature/ts : value
}

void check_light()
{
  float volt = ldr.read_voltage();
  if (volt < LDR_thresh_v) {
    light.set(Switch::ON);
  } else {
    light.set(Switch::OFF);
  }
  // TODO: set on DB /day_ts/LDR/volts : value
  // TODO: set on DB /day_ts/LDR/volts : value
}

void setup()
{
  Serial.begin(115200);
  eeprom.begin();
  adc.begin(constants::adc_bus_addr, pin::adc_sda, pin::adc_scl);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  timer.begin();
  flog.begin(
    FIREBASE_URL, FIREBASE_TOKEN, FIREBASE_USER_EMAIL, FIREBASE_USER_PASSWORD);
  temp_sensor.begin();
  misters.begin(Switch::ON);
  misters.set(Switch::ON);
  light.begin(Switch::ON);
  extra_relay.begin(Switch::OFF);
  delay(1000);
  Serial.printf("Found temperature sensors: %d\n", temp_sensor.device_count());
  scheduler.begin();
  Serial.println("Initialisation complete");
}

int count = 0;

void loop()
{
  // count++;
  // if (flog.is_ready()) {
  //   flog.set_int("test/int", timer.get_epoch_time());
  //   delay(5000);
  // }
}