#include <WiFi.h>

#include "secrets.h"
#include "timer.h"

Timer timer;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  //connect to WiFi
  Serial.printf("Connecting to %s ", WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");

  //init and get the time
  timer.begin();
}

void loop()
{
  delay(1000);
  timer.print_utc_time();
}