#ifndef _TIMER_H_
#define _TIMER_H_

#include <WiFi.h>

#include "esp_sntp.h"

void timeSyncCallback(struct timeval * tv)
{
  Serial.println("\n----Time Synced-----");
}

/**
 * @brief Make sure WiFi is configured before calling begin on this
 * 
 */
class Timer
{
private:
  static const char * ntp_server_;

public:
  Timer(){};

  tm get_utc_time()
  {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
      Serial.println("Failed to obtain time");
      return tm{};
    }
    return timeinfo;
  }

  time_t get_epoch_time()
  {
    auto time = get_utc_time();
    return mktime(&time);
  }

  void print_utc_time()
  {
    auto timeinfo = get_utc_time();
    auto tim = mktime(&timeinfo);
    Serial.printf("Epoch time: %ld\n", tim);
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  }

  void begin(long int sync_interval_ms = 600000)
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
};

const char * Timer::ntp_server_ = "pool.ntp.org";

#endif