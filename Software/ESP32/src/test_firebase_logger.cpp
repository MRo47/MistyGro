#include <Arduino.h>
#include <WiFi.h>

#include "firebase_logger.h"
#include "secrets.h"

int count = 0;

FireLogger flog(&WiFi, FIREBASE_URL, FIREBASE_TOKEN);

void setup()
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  flog.begin();
}

void loop()
{
  count++;
  if (flog.is_ready()) {
    flog.set_int("test/int", count);
    delay(5000);
  }
}
