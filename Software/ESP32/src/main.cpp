#include <Arduino.h>

#include "WiFi.h"
#include "firebase_logger.h"
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
RelayAH light(pin::extra_relay);  // changed role on purpose
LightScheduler light_scheduler(
  &light, constants::light_start_hour, constants::light_start_min,
  constants::light_duration);
RelayAH extra(pin::light);
Timer timer;
FireLogger flog;
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

String wrap_date(const char * path)
{
  auto timeinfo = timer.get_utc_time();
  auto tim = mktime(&timeinfo);
  char buf[12];
  strftime(buf, sizeof(buf), "%F", &timeinfo);
  String out(buf);
  out += "/";
  out += path;
  return out;
}

void toggle_misters()
{
  misters.toggle();
  Serial.printf("Misters %s\n", (bool)misters.get_state() ? "on" : "off");
  // set on DB day_ts/misters/ts : value
  flog.set_bool(wrap_date_time("misters").c_str(), (bool)misters.get_state());
}

void check_temperature()
{
  float temp = temp_sensor.read();
  Serial.printf("Temperature %f\n", temp);
  // set on DB day_ts/temperature/ts : value
  flog.set_float(wrap_date_time("temperature").c_str(), temp);
}

void check_and_set_light()
{
  float volt = ldr.read_voltage();

  auto time_info = timer.get_utc_time();

  light_scheduler.run(&time_info, volt >= constants::ldr_thresh_v);

  // set on DB /day_ts/ldr/ts : value
  flog.set_float(wrap_date_time("ldr_volts").c_str(), volt);
  // set on DB /day_ts/lights/ts : value
  flog.set_bool(wrap_date_time("lights").c_str(), (bool)light.get_state());
}

void check_wifi()
{
  if (!WiFi.isConnected()) {
    WiFi.reconnect();
    Serial.println("Reconnecting WiFi ...");
  }
}

void check_and_refresh_firebase_token()
{
  if (flog.check_and_refresh_token()) {
    flog.push_time(
      wrap_date("token_refreshed").c_str(), timer.get_epoch_time());
  }
}

void handle_wifi_connection(WiFiEvent_t event, WiFiEventInfo_t info)
{
  if (event == WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_CONNECTED) {
    Serial.println("WiFi Connected, initialising ...");
    timer.begin();
    flog.begin(
      FIREBASE_URL, FIREBASE_TOKEN, FIREBASE_USER_EMAIL,
      FIREBASE_USER_PASSWORD);
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
  // WiFi.onEvent(handle_wifi_connection, ARDUINO_EVENT_WIFI_STA_CONNECTED); // TODO: This does not work, wifi wont connect if set
  // WiFi.setAutoReconnect(true); // TODO: This does not work, wifi wont connect if set
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (!WiFi.isConnected()) {
    Serial.println("Connecting WiFi ...");
    delay(2000);
  }
  timer.begin();  // TODO: Remove if can be set from handle wifi connection
  flog.begin(
    FIREBASE_URL, FIREBASE_TOKEN, FIREBASE_USER_EMAIL,
    FIREBASE_USER_PASSWORD);  // TODO: Remove if can be set from handle wifi connection
  temp_sensor.begin();
  delay(1000);
  Serial.printf("Found temperature sensors: %d\n", temp_sensor.device_count());
  scheduler.begin();
  scheduler.create_task(check_wifi, constants::wifi_check_time);
  scheduler.create_task(
    check_and_refresh_firebase_token, constants::check_token_refresh_time);
  scheduler.create_task(toggle_misters, constants::mister_toggle_time);
  scheduler.create_task(check_temperature, constants::temperature_check_time);
  scheduler.create_task(check_and_set_light, constants::light_check_n_set_time);
  Serial.println("Initialisation complete");
  flog.push_time(wrap_date("inits").c_str(), timer.get_epoch_time());
}

void loop() { scheduler.run(); }