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

  void set_int(const char * path, int value);

  void set_float(const char * path, float value);

  void set_string(const char * path, const char * value);

  void set_bool(const char * path, bool value);

  bool is_ready();
};

#endif  // _FIREBASE_LOGGER_H_