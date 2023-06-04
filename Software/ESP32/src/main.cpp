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
RelayAH misters(pin::misters);
RelayAL light(pin::light);
RelayAH extra_relay(pin::extra_relay);
Timer timer;
FireLogger flog;
Scheduler scheduler;

String wrap_time(const char * path)
{
  auto timeinfo = timer.get_utc_time();
  auto tim = mktime(&timeinfo);
  char buf[12];
  strftime(buf, sizeof(buf), "%F", &timeinfo);
  String out(buf);
  out += "/";
  out += path;
  out += "/";
  out += tim;
  return out;
}

void toggle_misters()
{
  misters.toggle();
  // set on DB day_ts/misters/ts : value
  flog.set_bool(wrap_time("misters").c_str(), (bool)misters.get_state());
}

void check_temperature()
{
  float temp = temp_sensor.read();
  // TODO: set on DB day_ts/temperature/ts : value
  flog.set_float(wrap_time("temperature").c_str(), temp);
}

void check_and_set_light()
{
  float volt = ldr.read_voltage();
  if (volt < constants::ldr_thresh_v) {
    light.set(Switch::ON);
  } else {
    light.set(Switch::OFF);
  }
  // TODO: set on DB /day_ts/ldr/ts : value
  flog.set_float(wrap_time("ldr").c_str(), volt);
  // TODO: set on DB /day_ts/lights/ts : value
  flog.set_bool(wrap_time("lights").c_str(), (bool)light.get_state());
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
  misters.begin(Switch::OFF);
  light.begin(Switch::ON);
  extra_relay.begin(Switch::OFF);
  delay(1000);
  Serial.printf("Found temperature sensors: %d\n", temp_sensor.device_count());
  scheduler.begin();
  scheduler.create_task(toggle_misters, 15);
  scheduler.create_task(check_temperature, 10);
  // scheduler.create_task(check_and_set_light, 5 * 60);
  Serial.println("Initialisation complete");
}

int count = 0;

void loop() { scheduler.run(); }