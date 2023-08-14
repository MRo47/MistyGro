#ifndef _FIREBASE_LOGGER_H_
#define _FIREBASE_LOGGER_H_

#include <FirebaseESP32.h>
#include <WiFi.h>

class FireLogger
{
private:
  FirebaseAuth auth_;
  FirebaseConfig config_;
  FirebaseData fbdo_;
  String path_prefix_;

  void print_error();

  MB_String full_path(const char * path);

public:
  FireLogger();
  void begin(
    const char * fire_url, const char * fire_token, const char * email,
    const char * pass);

  void set_int(const char * path, int64_t value);

  void set_float(const char * path, double value);

  void set_string(const char * path, const char * value);

  void set_bool(const char * path, bool value);

  void push_time(const char * path, time_t timestamp);

  bool is_ready();

  bool is_keep_alive();

  bool is_connected();

  /**
 * @brief refresh token if expired
 * 
 * @return true if token refreshed
 */
  bool check_and_refresh_token();
};

#endif  // _FIREBASE_LOGGER_H_