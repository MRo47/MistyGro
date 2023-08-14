#include <Arduino.h>

#include "WiFi.h"
#include "ldr.h"
#include "light_scheduler.h"
#include "relay.h"
#include "scheduler.h"
#include "secrets.h"
#include "temperature_sensor.h"
#include "timer.h"
#include "utility.h"

ADC adc;
LDR ldr(10, &adc);
TemperatureSensor temp_sensor(pin::temp_sensor_bus);
RelayAH misters(pin::misters);
RelayAL light(pin::extra_relay);
LightScheduler light_scheduler(
  &light, constants::light_start_hour, constants::light_start_min,
  constants::light_duration);
RelayAH extra(pin::light);
Timer timer;
Scheduler scheduler;

String wrap_date_time(const char * path)
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
  Serial.printf("Misters %s\n", (bool)misters.get_state() ? "on" : "off");
}

void check_temperature() { float temp = temp_sensor.read(); }

void check_and_set_light()
{
  float volt = ldr.read_voltage();
  Serial.printf("LDR voltage: %f\n", volt);

  auto time_info = timer.get_utc_time();

  light_scheduler.run(&time_info, volt >= constants::ldr_thresh_v);
}

void check_wifi()
{
  if (!WiFi.isConnected()) {
    WiFi.reconnect();
    Serial.println("Reconnecting WiFi ...");
  }
}

void handle_wifi_connection(WiFiEvent_t event, WiFiEventInfo_t info)
{
  if (event == WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_CONNECTED) {
    Serial.println("WiFi Connected, initialising ...");
    timer.begin();
  }
}

void setup()
{
  Serial.begin(115200);
  misters.begin(Switch::OFF);
  light.begin(Switch::OFF);
  extra.begin(Switch::OFF);
  adc.begin(constants::adc_bus_addr, pin::adc_sda, pin::adc_scl);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (!WiFi.isConnected()) {
    Serial.println("Connecting WiFi ...");
    delay(2000);
  }
  timer.begin();
  temp_sensor.begin();
  delay(2000);
  Serial.printf("Found temperature sensors: %d\n", temp_sensor.device_count());
  scheduler.begin();
  scheduler.create_task(check_wifi, constants::wifi_check_time);
  scheduler.create_task(toggle_misters, constants::mister_toggle_time);
  scheduler.create_task(check_temperature, constants::temperature_check_time);
  scheduler.create_task(check_and_set_light, constants::light_check_n_set_time);
  Serial.println("Initialisation complete");
}

int count = 0;

void loop() { scheduler.run(); }