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

#include "timer.h"

#include "esp_sntp.h"

const char * Timer::ntp_server_ = "pool.ntp.org";

void timeSyncCallback(struct timeval * tv)
{
  Serial.println("\n----Time Synced-----");
}

Timer::Timer(){};

tm Timer::get_utc_time()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return tm{};
  }
  return timeinfo;
}

time_t Timer::get_epoch_time()
{
  auto time = get_utc_time();
  return mktime(&time);
}

void Timer::print_utc_time()
{
  auto timeinfo = get_utc_time();
  auto tim = mktime(&timeinfo);
  Serial.printf("Epoch time: %ld\n", tim);
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void Timer::begin(long int sync_interval_ms)
{
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("WiFi not connected ...");
  }

  sntp_set_time_sync_notification_cb(timeSyncCallback);
  sntp_set_sync_interval(sync_interval_ms);
  configTzTime("Etc/GMT", ntp_server_);
  print_utc_time();
}
