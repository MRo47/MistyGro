#ifndef _FIREBASE_LOGGER_H_
#define _FIREBASE_LOGGER_H_

#include <FirebaseESP32.h>
#include <WiFi.h>

class FireLogger
{
private:
  WiFiClass * wifi_;
  FirebaseAuth auth_;
  FirebaseConfig config_;
  FirebaseData fbdo_;
  bool signup_ok_;

  void print_error();

public:
  FireLogger(WiFiClass * wifi, const char * fire_url, const char * fire_token);
  void begin();

  void set_int(const char * path, int value);

  void set_float(const char * path, float value);

  void set_string(const char * path, const char * value);

  void set_bool(const char * path, bool value);

  bool is_ready();
};

#endif  // _FIREBASE_LOGGER_H_