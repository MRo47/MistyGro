// Copyright 2023 Myron Rodrigues
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <Arduino.h>
#include <WiFi.h>

#include "firebase_logger.h"
#include "scheduler.h"
#include "secrets.h"

int64_t count = 0;

Scheduler scheduler;
FireLogger flog;

void set_value()
{
  count++;
  flog.set_int("test/int", count);
}

void check_wifi()
{
  if (!WiFi.isConnected()) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
  }
  Serial.printf(
    "Is firebase connected: %s\n", flog.is_connected() ? "true" : "false");
}

void check_and_refresh_firebase_token() { flog.check_and_refresh_token(); }

void setup()
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  flog.begin(
    FIREBASE_URL, FIREBASE_TOKEN, FIREBASE_USER_EMAIL, FIREBASE_USER_PASSWORD);

  scheduler.begin();
  scheduler.create_task(check_wifi, 30);
  scheduler.create_task(set_value, 5 * 60);
  scheduler.create_task(check_and_refresh_firebase_token, 60);

  Serial.println("Done setup");
}

void loop() { scheduler.run(); }
